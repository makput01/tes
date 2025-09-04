#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef _WIN32
#include <winsock2.h>
#define socklen_t int
#else
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif
#include <string.h>
#include <unistd.h>

#include "httpService.h"
#include "proxyStruct.h"
#include "tlse/tlse.h"
#include "utils/utils.h"

// send_pending and HTTPSClient are no longer used by the local server,
// but are kept for now as they might be used by other parts of the application
// that are not part of the current task.

int send_pending(int client_sock, struct TLSContext *context) {
  unsigned int out_buffer_len = 0;
  const unsigned char *out_buffer =
      tls_get_write_buffer(context, &out_buffer_len);
  unsigned int out_buffer_index = 0;
  int send_res = 0;
  while ((out_buffer) && (out_buffer_len > 0)) {
    int res = send(client_sock, (char *)&out_buffer[out_buffer_index],
                   out_buffer_len, 0);
    if (res <= 0) {
      send_res = res;
      break;
    }
    out_buffer_len -= res;
    out_buffer_index += res;
  }
  tls_buffer_clear(context);
  return send_res;
}

struct HTTPInfo HTTPSClient(const char *website) {
  unsigned char read_buffer[0xFFFF];
  unsigned char client_message[0xFFFF];

  int sockfd, portno = 443;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  struct HTTPInfo info;

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("[HTTPService Client] Error: opening socket\n");
    exit(0);
  }

  server = gethostbyname(website);
  if (server == NULL) {
    printf("[HTTPService Client] Error: no such host\n");
    exit(0);
  }
  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr_list[0],
         server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("[HTTPService Client] Error: connecting\n");
    exit(0);
  }

  struct TLSContext *context = tls_create_context(0, TLS_V12);

  tls_make_exportable(context, 1);
  tls_client_connect(context);
  send_pending(sockfd, context);

  int read_size;
  while ((read_size = recv(sockfd, client_message, sizeof(client_message), 0)) >
         0) {
    tls_consume_stream(context, client_message, read_size, NULL);
    send_pending(sockfd, context);
    if (tls_established(context)) {
      const char *request =
          "POST /growtopia/server_data.php HTTP/1.1\r\nUser-Agent: "
          "UbiServices_SDK_2019.Release.27_PC64_unicode_static\r\nHost: "
          "www.growtopia1.com\r\nAccept: */*\r\nConnection: "
          "close\r\ncontent-length: 0\r\n\r\n";
      if (!tls_make_ktls(context, sockfd))
        send(sockfd, request, strlen(request), 0);
      else {
        tls_write(context, (unsigned char *)request, strlen(request));
        send_pending(sockfd, context);
      }
      int tempLen = tls_read(context, read_buffer, 0xFFFF - 1);
      if (tempLen != 0)
        info.bufferLen = tempLen;
    }
  }
  read_buffer[info.bufferLen] = '\0';
  info.buffer = read_buffer;
  tls_destroy_context(context);
  return info;
}

// This function is now a plain HTTP server that will run behind an NGINX reverse proxy.
void *http_server(void *unused) {
  int socket_desc, client_sock;
  socklen_t c;
  struct sockaddr_in server, client;
  const char msg[] =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/plain\r\n"
      "Content-Length: 279\r\n"
      "Connection: close\r\n\r\n"
      "server|127.0.0.1\nport|17091\ntype|1\n#maint|"
      "maintenance\nbeta_server|beta.growtopiagame.com\nbeta_port|26999\nbeta_"
      "type|1\nbeta2_server|beta2.growtopiagame.com\nbeta2_port|26999\nbeta2_"
      "type|1\nbeta3_server|34.202.7.77\nbeta3_port|26999\nbeta3_type|1\ntype2|"
      "0\nmeta|localhost\nRTENDMARKERBS1001";

#ifdef _WIN32
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("[HTTP Server] Error: Could not create socket\n");
    exit(0);
  }

  // The server will listen on port 8081 for plain HTTP traffic from NGINX.
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8081);

  int enable = 1;
  setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("[HTTP Server] Error: bind failed on port 8081\n");
    exit(1);
  }

  listen(socket_desc, 3);
  printf("[HTTP Server] Log: HTTP Server is enabled, listening on port 8081\n");

  c = sizeof(struct sockaddr_in);

  while (1) {
    client_sock = accept(socket_desc, (struct sockaddr *)&client, &c);

    if (client_sock < 0) {
      printf("[HTTP Server] Error: Accept failed\n");
      continue;
    }

    // For this specific purpose, we don't need to read the request.
    // We just send the hardcoded response immediately.
    if (send(client_sock, msg, strlen(msg), 0) < 0) {
        printf("[HTTP Server] Error: Send failed\n");
    }

#ifdef _WIN32
    Sleep(500);
#else
    usleep(500);
#endif
#ifdef __WIN32
    shutdown(client_sock, SD_BOTH);
    closesocket(client_sock);
#else
    shutdown(client_sock, SHUT_RDWR);
    close(client_sock);
#endif
  }
}

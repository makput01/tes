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

const unsigned char *certPem =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDCTCCAfGgAwIBAgIUQFJjxh3msaOzmr2YGW/acAnPRywwDQYJKoZIhvcNAQEL\n"
    "BQAwFDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTI1MDkwNDA0NDYwN1oXDTI2MDkw\n"
    "NDA0NDYwN1owFDESMBAGA1UEAwwJbG9jYWxob3N0MIIBIjANBgkqhkiG9w0BAQEF\n"
    "AAOCAQ8AMIIBCgKCAQEA5YS+lnmTj8+DMoIhGSWhV+pG9L2i4x0ift1/Ibn9vOi6\n"
    "TGAQOp4bDFgJCCLEoKZ22NR/Y+LGhbeQDGzzaO7lhBsvWQ/pIvYTtWItkIgJBin+\n"
    "/4hf1Py8FeNNp8jtXNHnsCrXglA7BZ2QVK8Pd7JblY9RFVoBFalWQXxLDeKIPaUg\n"
    "5nxYHUb6a86iKnS2KaRSklesKAhHrb74DYCwLwt+qqwJjqWrffND2GKvurFo0lvH\n"
    "7Cb7gYgClkuJLGYrH9GA+utQh9zUWOb60TffEAs2Z1G+RDDBVHG7kqPedix/u+PX\n"
    "j6g/uLqAhZsfOY7lxuE69XmlzZltVDC2LxtpgzbLewIDAQABo1MwUTAdBgNVHQ4E\n"
    "FgQU7ymZxnzr8mnQV1W7pzaAvkdvfb8wHwYDVR0jBBgwFoAU7ymZxnzr8mnQV1W7\n"
    "pzaAvkdvfb8wDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAhGE3\n"
    "pCuVoUoqPYjwrDffYwcnG8WzZiZ3Ex+ivMbMTrE61kS/xzT+fjpqUywAXAoxtCyv\n"
    "L6HoeUyW/HsfK3ivWK62ySe4sOvtQCocdJbXFCX/WM8zVGg/K1XUbqstYv5tlNoK\n"
    "E9BqA9tgBp49/uwzHydO8LDJCtL3kId4GKQrB5LHUKuve8/e2NLZyYUUS4EWd2rs\n"
    "c6ssDDfwQdlQL0k8mwc5NODVd51xt+UYlpbW9JtC57tcNv/f/2AgxDYBgv+jiUzt\n"
    "9tnfvUL62xRrEVY6WZ+ZGMQEBVhuPbiRFWs775hjRUTV/y3A88BpzKh2aW5mBzfc\n"
    "ifKJGPH06g3uQR3Dwg==\n"
    "-----END CERTIFICATE-----";

const unsigned char *keyPem =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDlhL6WeZOPz4My\n"
    "giEZJaFX6kb0vaLjHSJ+3X8huf286LpMYBA6nhsMWAkIIsSgpnbY1H9j4saFt5AM\n"
    "bPNo7uWEGy9ZD+ki9hO1Yi2QiAkGKf7/iF/U/LwV402nyO1c0eewKteCUDsFnZBU\n"
    "rw93sluVj1EVWgEVqVZBfEsN4og9pSDmfFgdRvprzqIqdLYppFKSV6woCEetvvgN\n"
    "gLAvC36qrAmOpat980PYYq+6sWjSW8fsJvuBiAKWS4ksZisf0YD661CH3NRY5vrR\n"
    "N98QCzZnUb5EMMFUcbuSo952LH+749ePqD+4uoCFmx85juXG4Tr1eaXNmW1UMLYv\n"
    "G2mDNst7AgMBAAECggEAAglW/ZPPlN+U/O49p/D3CQYpogNKvjQkebayaZSyZSo1\n"
    "ePcDPdnoSIhBcEKKtxgzBsJ/7N12wHn7+7g9wqkX/T+WgHZNLcO8MghQei9S0Syv\n"
    "OAo4O3YQnysYpcv5GzE7mosOxXe7xlV7Ed1JyFibSmzunb9iMhSCEOuu6M0hQ1a+\n"
    "8ObbTDYdanQLp1TmkUvp/OdGe1EUNhz/Hkxg2/mecwCe+9IuJpSB3iZani0wCntV\n"

    "roOmdPDKuUX03s3T5xmRgTGuI3DAOCbIYCd2l+aEmHxTskKkA7/zejURqdvixOlJ\n"
    "XC9V9+LpIbZ4eUlfaQuK+WVsiaNJMWqShd9aRlKV9QKBgQD+1dsdu1MBBh6NgXkj\n"
    "NGGNdRgyeUvn8bS/POfmhAfaZfzletVL5isy2Et5E8wlQ/QBVX3wWbty/U9Y4s8N\n"
    "0X1JX0RqWs855tH2W72yYk7E519LM/oyWWAaBIQB0FwkrCJ0Iylseuw5AR7smwhT\n"
    "TpfyhjfqxgcwxgKZBywnbf5UXwKBgQDmkUTo6HwsNwoQF3WQq4dSgww844m74V5t\n"

    "EtrBJdnaJPS0gHszA5Io7J9Zoz03YAPE5OCG0rkeNPiafavvVSpZK7/Ysg35I/A+\n"
    "0Y76HGhb7Skt6DkUM6enNWVBtvYo9qMcxxlIP2Zf5YNhK+kZcJpHXF8JJSUhnJdb\n"
    "scjkdF++ZQKBgQDrYbEwtzQl//b8kZjIsbtho8Sj6nH4XcOr2KACxfVS/10mwdx+\n"
    "bK1+G1crEORBj5C0Irle5iNERUGjQmwpwVROD1bsPdCnFNLfEUIYoMFNEsFsfygc\n"
    "lX00yvL7ke9qWCzCxS+f6bKDvMtJlLGN8UxcUSkZC6zcmikQHBXmnayLVQKBgQDP\n"
    "IhqCErnbDucfZbPcb/x2B/zqho+qFeE6pAGaG2MHMsQTlIkZX0/jLBBL+vZ31O4N\n"
    "6IA9HvnnRTdBszzPGfedfEwxZGRhOgQOqzyDPRoT249vCnycxXsMIFADJVcnncsT\n"
    "g1oXKb3S0OGiXkxe6mXvTfCiypf9BiyD18feVR3ecQKBgQCTV+7xg/zaMJo0ACVX\n"
    "s0K3EEPpmjxdOYhhLCwKGbBaFVPQ4bx6hHMN0jes8v2ybet8byxW8uhxah8kKi/+\n"
    "0LtYDLP8MaHCtKew3BBjSJ26+cVXrN9rLBRaYpidpINi2uSD302Za9tZE60ika32\n"
    "GvXv9DsJ0ksuCfuU8C3E8JTI1w==\n"
    "-----END PRIVATE KEY-----";

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

void *HTTPSServer(void *unused) {
  int socket_desc, client_sock;
  socklen_t c;
  struct sockaddr_in server, client;
  const char msg[] =
      "HTTP/1.1 200 OK\r\nContent-length: "
      "279\r\n\r\nserver|127.0.0.1\nport|17091\ntype|1\n#maint|"
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
    printf("[HTTPService Server] Error: Could not create socket\n");
    exit(0);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(userConfig.httpsPort);

  int enable = 1;
  setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &enable, 4);

  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("[HTTPService Server] Error: bind failed! If you are not a root "
           "user, please change it to 8080\n");
    exit(1);
  }

  listen(socket_desc, 3);

  c = sizeof(struct sockaddr_in);

  struct TLSContext *server_ctx = tls_create_context(1, TLS_V12);

  if (!server_ctx) {
    printf("[HTTPService Server] Error: creating server context");
    exit(-1);
  }

  if (tls_load_certificates(server_ctx, certPem, strlen(certPem)) <= 0) {
    printf("[HTTPService Server] Error: certificate not loaded\n");
    exit(-2);
  }

  if (tls_load_private_key(server_ctx, keyPem, strlen(keyPem)) <= 0) {
    printf("[HTTPService Server] Error: private key not loaded\n");
    exit(-2);
  }

  printf("[HTTPService Server] Log: HTTPS Server is enabled\n");

  while (1) {
    client_sock = accept(socket_desc, (struct sockaddr *)&client, &c);

    if (client_sock < 0) {
      printf("[HTTPService Server] Error: Accept failed\n");
      continue;
    }

    struct TLSContext *client_ctx = tls_accept(server_ctx);
    if (!client_ctx) {
        printf("[HTTPService Server] Error: Error creating client context\n");
        close(client_sock);
        continue;
    }

    while (!tls_established(client_ctx)) {
        unsigned char buffer[4096];
        int bytes_read = recv(client_sock, (char *)buffer, sizeof(buffer), 0);

        if (bytes_read <= 0) {
            break;
        }

        if (tls_consume_stream(client_ctx, buffer, bytes_read, NULL) < 0) {
            printf("[HTTPService Server] Error: in handshake\n");
            break;
        }

        if (send_pending(client_sock, client_ctx) < 0) {
             printf("[HTTPService Server] Error: send failed during handshake\n");
             break;
        }
    }

    if (tls_established(client_ctx)) {
        tls_write(client_ctx, (unsigned char *)msg, strlen(msg));
        if (send_pending(client_sock, client_ctx) < 0) {
            printf("[HTTPService Server] Error: in SSL Write\n");
        }
    }

    tls_close_notify(client_ctx);
    send_pending(client_sock, client_ctx);

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
    tls_destroy_context(client_ctx);
  }
  tls_destroy_context(server_ctx);
}

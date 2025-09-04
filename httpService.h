#ifndef HTTPSERVICE_H_INCLUDED
#define HTTPSERVICE_H_INCLUDED

struct HTTPInfo {
    unsigned char* buffer;
    int bufferLen;
};

struct HTTPInfo HTTPSClient(const char* website);
void* http_server(void* unused);

#endif // HTTPSERVICE_H_INCLUDED

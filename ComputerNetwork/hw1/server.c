#include <stdio.h>      // gets
#include <stdlib.h>     // atoi
#include <string.h>     // memset
#include <unistd.h>     // sockaddr_in, read, write
#include <arpa/inet.h>  // htonl, htons, INADDR_ANY
#include <sys/socket.h> // socket
#define BUFSIZE 1024

void handleError(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockServer, sockClient;
    struct sockaddr_in addrServer, addrClient;
    socklen_t addrSizeClient;
    char buffer[BUFSIZE] = {0};

    // 소켓 IP와 포트 지정
    if (argc < 2 || atoi(argv[1]) == 0)
    {
        printf("Usage: ./server [port]\n");
        return 1;
    }

    // 서버 소켓 생성
    // PF_INET: IPv4, PF_INET6: IPv6
    // SOCK_STREAM: TCP, SOCK_DGRAM: UDP, SOCK_RAW: IP Layer (non tcp or udp)
    if ((sockServer = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        handleError("Socket Error");

    // 바인딩
    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[1]));
    if (bind(sockServer, (struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
        handleError("Bind Error");

    // 클라이언트 연결 설정
    if (listen(sockServer, 1) == -1)
        handleError("Listen Error");

    // 클라이언트 접속 대기
    addrSizeClient = sizeof(addrClient);
    printf("Waiting for client...\n");
    if ((sockClient = accept(sockServer, (struct sockaddr *)&addrClient, &addrSizeClient)) == -1)
        handleError("Accept Error");

    // 클라이언트 IP 가져오기
    inet_ntop(AF_INET, &addrClient.sin_addr, buffer, INET_ADDRSTRLEN);
    printf("Client %s connected!\n\n", buffer);
    memset(buffer, 0, BUFSIZE);

    // 통신
    while (1)
    {
        // 보내기
        printf("Server: ");
        fgets(buffer, BUFSIZE, stdin);
        write(sockClient, buffer, strlen(buffer));
        if (strcmp(buffer, "exit\n") == 0)
            break;
        memset(buffer, 0, BUFSIZE);

        //받기
        if (read(sockClient, buffer, BUFSIZE) <= 0 || strcmp(buffer, "exit\n") == 0)
        {
            printf("\nClient disconnected.\n");
            break;
        }
        printf("Client: %s", buffer);
        memset(buffer, 0, BUFSIZE);
    }

    close(sockClient);
    close(sockServer);
    printf("\nServer Closed.\n");
    return 0;
}
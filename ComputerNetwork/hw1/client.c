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
    int sockClient;
    struct sockaddr_in addrServer;
    char buffer[BUFSIZE] = {0};

    // 소켓 IP와 포트 지정
    if (argc < 3 || atoi(argv[2]) == 0)
    {
        printf("Usage: ./client [server-ip] [port]\n");
        return 1;
    }

    // 소켓 생성
    if ((sockClient = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        handleError("Socket Error");

    // 바인딩
    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);
    addrServer.sin_port = htons(atoi(argv[2]));

    // 서버 접속
    if (connect(sockClient, (struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
        handleError("Connect Error");
    printf("Server connected!\n\n");

    // 통신
    while (1)
    {
        // 받기
        if (read(sockClient, buffer, BUFSIZE) <= 0 || strcmp(buffer, "exit\n") == 0)
        {
            printf("\nServer disconnected.\n");
            break;
        }
        printf("Server: %s", buffer);
        memset(buffer, 0, BUFSIZE);

        // 보내기
        printf("Client: ");
        fgets(buffer, BUFSIZE, stdin);
        write(sockClient, buffer, strlen(buffer));
        if (strcmp(buffer, "exit\n") == 0)
            break;
        memset(buffer, 0, BUFSIZE);
    }

    close(sockClient);
    printf("\nConnection Closed.\n");
    return 0;
}
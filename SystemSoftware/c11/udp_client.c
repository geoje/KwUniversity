#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE sizeof (struct sockaddr_in)

int main() {
	int sockfd;
	char c;
	int server_len = SIZE;

	struct sockaddr_in client = { AF_INET, INADDR_ANY, INADDR_ANY };
	struct sockaddr_in server = { AF_INET, 7000 };
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Build transport endpoint
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return 1;
	}

	//Bind local address to endpoint
	if (bind(sockfd, (struct sockaddr *)&client, SIZE) == -1) {
		perror("bind");
		return 1;
	}

	while (read(0, &c, 1) != 0) {
		if (sendto(sockfd, &c, 1, 0, (struct sockaddr *)&server, SIZE) == -1) {
		perror("sendto");
		continue;
		}

		if (recvfrom(sockfd, &c, 1, 0, (struct sockaddr *)&server, &server_len) == -1) {
			perror("recvfrom");
			continue;
		}
		write(1, &c, 1);
	}
}

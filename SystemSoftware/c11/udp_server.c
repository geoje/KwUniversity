#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE sizeof(struct sockaddr_in)

int main() {
	int sockfd;
	char c;
	struct sockaddr_in server = {AF_INET, 7000, INADDR_ANY};
	struct sockaddr_in client;
	int client_len = SIZE;

	//Build transport end point
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return 1;
	}
	if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1) {
		perror("bind");
		return 1;
	}

	//Get message
	while(1) {
		if (recvfrom(sockfd, &c, 1, 0, (struct sockaddr *)&client, &client_len) == -1) {
			perror("recvfrom");
			return 1;
		}
		c = toupper(c);

		if(sendto(sockfd, &c, 1, 0, (struct sockaddr *)&client, client_len) == -1) {
			perror("sendto");
			continue;
		}
	}
}

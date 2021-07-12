#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFSIZE 64
#define PERM 0644
#define NOTIFY "전송할 파일 이름을 입력하세요. (bye to quit) : "

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char **argv) {
	int sock;
	struct sockaddr_in s_addr;

	int fd, len;
	char buf[BUFSIZE];

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error_handling("socket() error");

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr(argv[1]);
	s_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1)
		error_handling("connect() error");

	while (1) {
		write(1, NOTIFY, strlen(NOTIFY));
		len = read(0, buf, BUFSIZE);
		buf[len - 1] = '\0';
		if (!strcmp(buf, "bye")) {
			close(sock);
			break;
		}

		if ((fd = open(buf, O_RDONLY)) == -1) {
			printf("Cannot open file[%s]\n", buf);
			continue;
		}
		printf("file[%s]을 전송합니다.\n", buf);

		write(sock, buf, len);
		fflush(stdout);
		while ((len = read(fd, buf, BUFSIZE)) > 0)
			write(sock, buf, len);
		close(fd);
		close(sock);
	}

	return 0;
}

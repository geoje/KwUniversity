#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFSIZE 64
#define PERM 0644

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
/*int get_file_size(const char *file_name) {
	struct stat_stat_info;
	if (stat(file_name, &stat_info) != 0) {
		printf("I can't find file\n");
		return -1;
	}
	return stat_info.st_size;
}*/

int main(int argc, char **argv) {
	int s_sock, c_sock;
	struct sockaddr_in s_addr, c_addr;
	int c_addr_size;

	int fd, len;
	char buf[BUFSIZE];

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if ((s_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error_handling("socket() error");

	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(atoi(argv[1]));

	if (bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1)
		error_handling("bind() error");

	if (listen(s_sock, 5) == -1)
		error_handling("accept() error");

	while (1) {
		printf("waiting for accept\n");
		c_addr_size = sizeof(c_addr);
		if ((c_sock = accept(s_sock, (struct sockaddr *)&c_addr, &c_addr_size)) == -1)
			error_handling("accept() error");

		if ((len = read(c_sock, buf, BUFSIZE)) <= 0) {
			close(c_sock);
			continue;
		}
		printf("file[%s]을 전송받습니다.\n", buf);

		fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, PERM);
		while ((len = read(c_sock, buf, BUFSIZE)) > 0)
			write(fd, buf, len);

		close(fd);
		close(c_sock);
	}
	close(s_sock);
	return 0;
}

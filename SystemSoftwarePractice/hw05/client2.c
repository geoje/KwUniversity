#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PERMS 0664
#define MAXSIZE 64

int main() {
	int fdi = 0, fdo = 0, len;
	char buf[MAXSIZE] = { 0, };

	fdi = open("FIFO_1", O_RDONLY);
	fdo = open("FIFO_2", O_WRONLY);

	while (1) {
		//receive
		write(1, "Waiting for response\n", 22);
		len = read(fdi, buf, MAXSIZE);
		write(1, "client1 say : ", 15);
		write(1, buf, len);
		write(1, "\n", 1);
		if (!strcmp(buf, "bye"))
			break;

		//send
		write(1, "client2(input) : ", 18);
		len = read(0, buf, MAXSIZE);
		buf[len - 1] = '\0';
		write(fdo, buf, len);
		if (!strcmp(buf, "bye"))
			break;
	}

	close(fdi);
	close(fdo);
	return 0;
}

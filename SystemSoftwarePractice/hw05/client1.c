#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PERMS 0666
#define MAXSIZE 64

int main() {
	int fdi = 0, fdo = 0, len;
	char buf[MAXSIZE] = { 0, };

	mkfifo("FIFO_1", PERMS);
	mkfifo("FIFO_2", PERMS);
	fdo = open("FIFO_1", O_WRONLY);
	fdi = open("FIFO_2", O_RDONLY);

	while (1) {
		//send
		write(1, "client1(input) : ", 17);
		len = read(0, buf, MAXSIZE);
		buf[len - 1] = '\0';
		write(fdo, buf, len);
		if (!strcmp(buf, "bye"))
			break;

		//receive
		write(1, "Waiting for response\n", 21);
		len = read(fdi, buf, MAXSIZE);
		write(1, "client2 say : ", 14);
		write(1, buf, len);
		write(1, "\n", 1);
		if (!strcmp(buf, "bye"))
			break;
	}

	close(fdi);
	close(fdo);
	unlink("FIFO_1");
	unlink("FIFO_2");
	return 0;
}

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

int main() {
	const char *filename = "hw1.txt";
	int filedes;
	char buffer[1024];

	if ((filedes = open(filename, O_RDONLY)) == -1) {
		fprintf(stderr, "error %d\n", errno);
		return -1;
	}
	lseek(filedes, (off_t)16, SEEK_SET);
	read(filedes, buffer, 18);
	buffer[18] = '\0';
	printf("%s", buffer);

	lseek(filedes, (off_t)4, SEEK_CUR);
	read(filedes, buffer, 7);
	buffer[7]='\0';
	printf(" %s\n", buffer);

	close(filedes);
	return 0;
}

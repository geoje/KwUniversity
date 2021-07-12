#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PERMS 0666

int main(int argc, char const *argv[]) {
	int num = 0, fd = 0;

	if (argc != 2) {
		printf("UsageL %s [pathname]\n", argv[0]);
		return -1;
	}

	srand(time(NULL));
	fd = open(argv[1], O_WRONLY);
	dup2(fd, STDOUT_FILENO);

	while (1) {
		num = rand() % 10;
		printf("[%d] %d", getpid(), num);
		fflush(stdout);

		if (num == 5) break;
		else sleep(1);
	}
	close(fd);
	return 0;
}

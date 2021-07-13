#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MSGSIZE 20

int main(int argc, char* argv[]) {
	int fd[2], pid, pipe(), fork();
	static char msgout[MSGSIZE] = "Hello, world\n";
	static char msgin[MSGSIZE];

	if (pipe(fd) == -1) {
		perror(argv[0]);
		exit(1);
	}
	if ((pid = fork()) > 0) {
		write(fd[1], msgout, MSGSIZE);
	} else if (pid == 0) {
		read(fd[0], msgin, MSGSIZE);
		puts(msgin);
	} else {
		perror(argv[0]);
		exit(2);
	}
	exit(0);
}

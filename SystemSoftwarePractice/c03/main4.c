#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s command arg1 arg2 ...\n", argv[0]);
		return 1;
	}
	pid = fork();
	if (pid == -1) {
		perror("Failed to fork");
		return 1;
	}
	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		perror("Child failed to execvp the command");
		return 1;
	}
	if (pid != wait(NULL)) {
		perror("Parent failed to wait");
		return 1;
	}
	return 0;
}

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;

	printf("Just one process so far\n");
	printf("Calling for ...\n");

	pid = fork();
	if (pid == -1) {
		printf("Fork returned error code. no child\n");
		exit(1);
	} else if (pid == 0) {
		printf("I'm the child. I have pid %d\n", (int)getpid());
	} else {
		printf("I'm the parent. I have pid %d\n", (int)getpid());
	}

	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int signo) {
	if (signo == SIGINT) {
		printf("INT signal received\n");
		fflush(stdout);
	}
	else if (signo == SIGUSR1)
		printf("SIGUSR1 signal received\n");
	else
		printf("signal no = %d\n", signo);
	return;
}

void main() {
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGINT");
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGUSR1");
	while (1)
		pause();
}

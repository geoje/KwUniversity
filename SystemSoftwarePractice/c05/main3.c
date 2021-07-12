#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int sig_count;

void signal_int(int signo) {
	sig_count++;
	printf("Insignal handler <signal_int> : sig_count = %d \n", sig_count);
}

void sigaction_int(int signo) {
	sig_count++;
	printf("Insignal handler <sigaction_int> : sig_count = %d \n", sig_count);
}

int main() {
	struct sigaction act, oact;

	act.sa_handler = sigaction_int;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, &oact) < 0) {
		fprintf(stderr, "sigaction erorr");
		return 1;
	}

	while (sig_count < 3) ;

	if (sigaction(SIGINT, &oact, NULL) < 0) {
		fprintf(stderr, "signal erorr");
		return 1;
	}

	if (signal(SIGINT, signal_int) == SIG_ERR) {
		fprintf(stderr, "signal erorr");
		return 1;
	}

	while (1) ;
	return 0;
}

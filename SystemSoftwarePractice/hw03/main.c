#include <stdio.h>
#include <signal.h> // signal, sigaction
#include <sys/types.h> // fork
#include <unistd.h> // fork

int sig_count;

void sigaction_usr1(int signo) {
	printf("<sig_usr> : sig_count = %d\n", ++sig_count);
}
void signal_int(int signo) {
	printf("<signal_int> : sig_count = %d\n", ++sig_count);
}
void sigaction_chld(int signo, siginfo_t *siginfo, void *uarg) {
	printf("<signal_child> : sig_count = %d\n", ++sig_count);
	printf("pid of sending process = %d\n", siginfo->si_pid);
	printf("uid of sending process = %d\n", siginfo->si_uid);
}

int main() {
	struct sigaction act, oact;
	sigset_t new_mask, old_mask;
	pid_t pid;

	// Get five of signal 'SIGUSR1'
	act.sa_handler = sigaction_usr1;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, &oact) < 0) {
		fprintf(stderr, "sigaction error");
		return 1;
	}
	while (sig_count < 5);

	// Block signal 'SIGUSR1' by setting signal mask
	sigemptyset(&new_mask);
	sigaddset(&new_mask, SIGUSR1);
	if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
		fprintf(stderr, "sigprocmask error");
		return 1;
	}
	if (signal(SIGINT, signal_int) == SIG_ERR) {
		fprintf(stderr, "signal error");
		return 1;
	}
	while (sig_count < 6);

	// Make child process and get signal 'SIGCHLD' from child process
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork error");
		return 1;
	} else if (pid == 0) {
		printf("I'm child process : %d\n", getpid());
		return 0;
	}
	act.sa_sigaction = sigaction_chld;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGCHLD, &act, &oact) < 0) {
		fprintf(stderr, "sigaction error");
		return 1;
	}
	while (sig_count < 7);

	printf("Finish homework 3");
	return 0;
}

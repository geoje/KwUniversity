#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#define TIMER_MSG "Received Timer Interrupt\n"

static void Interrupt() {
	printf("%s\n", TIMER_MSG);
}

static int setInterrupt() {
	struct sigaction act;

	act.sa_flags = 0;
	act.sa_sigaction = Interrupt;
	if (sigaction(SIGALRM, &act, NULL) < 0)
		return -1;
	return 0;
}

static int setperiodic(int sec) {
	timer_t timerid;
	struct itimerspec value;

	if (timer_create(CLOCK_REALTIME, NULL, &timerid) == -1)
		return -1;

	value.it_interval.tv_sec = (long)sec;
	value.it_interval.tv_nsec = 0;

	value.it_value = value.it_interval;
	return timer_settime(timerid, 0, &value, NULL);
}

int main() {
	if (setInterrupt() == -1) {
		perror("Failed to setup SIGALRM hanlder");
		return 1;
	}
	if (setperiodic(2) == -1) {
		perror("Failed to setup periodic Interrupt");
		return 1;
	}

	while(1) pause();
	return 0;
}

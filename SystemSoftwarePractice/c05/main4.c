#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int alarm_handler() {
	printf("\n signal handled!\n");
	return 0;
}

int main() {
	signal(SIGALRM, (void*)alarm_handler);
	alarm(3);

	while (1) {
		printf("sleeping\n");
		sleep(1);
	}

	return 0;
}

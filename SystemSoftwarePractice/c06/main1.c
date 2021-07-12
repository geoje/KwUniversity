#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main() {
	int i;
	time_t thetime;

	for(i = 1; i <= 10; i++) {
		thetime = time((time_t*)0);
		printf("The time is %ld\n", thetime);
		sleep(2);
	}
	return 0;
}

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	time_t timeval;
	time(&timeval);
	printf("The date is : %s", ctime(&timeval));
	return 0;
}

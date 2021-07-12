#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char *workfile="junk";

int main() {
	int filedes;
	if ((filedes = open(workfile, O_RDWR)) == -1) {
		printf("Couldn't open %s\n", workfile);
		exit(1);
	} else {
		printf("File %s is opened! successfully\n", workfile);
	}
	return 0;
}

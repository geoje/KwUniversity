#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: mkdir dirname\n");
		return 1;
	}
	if (mkdir(argv[1], 0755)) {
		perror("mkdir error");
		return 1;
	}
	return 0;
}

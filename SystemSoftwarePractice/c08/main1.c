#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#define PERMS 0666

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("Usage %s [pathname]\n", argv[0]);
		return -1;
	}
	mkfifo(argv[1], PERMS);
	return 0;
}

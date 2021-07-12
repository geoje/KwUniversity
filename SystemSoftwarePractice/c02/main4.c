#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	char buf[255];
	printf("argc: %d, argv[0]: %s, argv[1]: %s\n", argc, argv[0], argv[1]);

	if (chdir(argv[1])) {
		perror("error");
		return 1;
	}

	getcwd(buf, 255);
	printf("pwd: %s\n", buf);
	return 0;
}

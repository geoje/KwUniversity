#include <unistd.h>
#include <stdio.h>

int rmdir(const char *pathname); //i can't understand why it exists

int main(int argc, char *argv[]) {
	if (chdir(argv[1])) {
		perror("error");
		return 1;
	}
	chdir("..");
	rmdir(argv[1]);

	return 0;
}

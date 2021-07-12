#include <stdio.h>
#include <errno.h> //perror
#include <sys/types.h> //mkdir
#include <sys/stat.h> //mkdir, stat
#include <sys/wait.h> //wait
#include <unistd.h> //rmdir, execl
#include <dirent.h> //opendir

void printMenu() {
	printf("===============================\n");
	printf("1. Make directory\n");
	printf("2. Remove directory\n");
	printf("3. Show current directory info\n");
	printf("4. Execute command\n");
	printf("5. Exit\n");
	printf("===============================\n");
	printf("Select number : ");
}

int main() {
	int index;
	char dir_name[64];
	struct dirent *direntp;
	DIR *dirp;
	pid_t pid;
	while(1) {
		printMenu();
		scanf("%d", &index);
		switch(index) {
		case 1:
			printf("Enter directory name : ");
			scanf("%s", dir_name);
			if (mkdir(dir_name, 0755)) {
				perror("mkdir error: ");
				break;
			}
			dirp = opendir(".");
			while((direntp = readdir(dirp)) != NULL)
				printf("%s\n", direntp->d_name);
			break;
		case 2:
			printf("Enter directory name : ");
			scanf("%s", dir_name);
			if(rmdir(dir_name)) {
				perror("rmdir error: ");
			}
			dirp = opendir(".");
			while((direntp = readdir(dirp)) != NULL)
				printf("%s\n", direntp->d_name);
			break;
		case 3:
			dirp = opendir(".");
			while((direntp = readdir(dirp)) != NULL)
				printf("%s %ld\n", direntp->d_name, direntp->d_ino);
			break;
		case 4:
			pid = fork();
			if (pid == -1) {
				perror("fork error: ");
				break;
			}
			if (pid == 0) {
				execl("/bin/ps", "ps", NULL);
				perror("child execl error: ");
			}
			if (pid != wait(NULL))
				perror("parent wait error: ");
			break;
		case 5:
			return 0;
		}
	}
	return 0;
}

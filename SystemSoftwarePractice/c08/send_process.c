#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PERM 0660
#define SIZE 128

int main(void) {
	int shmid;
	char *memptr;
	char my_str[SIZE];

	int key = ftok("/tmp", 'A');

	if ((shmid = shmget(key, SIZE, PERM | IPC_CREAT)) < 0) {
		perror("shmget");
		exit(1);
	}
	if ((memptr = shmat(shmid, (char*)0, 0)) == (char*)-1) {
		perror("shmat");
		exit(1);
	}

	strcpy(memptr, "Hello world");

	while(1) {
		printf("input : ");
		scanf("%s", my_str);
		strcpy(memptr, my_str);
		if (strcmp(memptr, "exit") == 0)
			break;
	}
	return 0;
}

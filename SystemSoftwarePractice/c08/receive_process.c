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

	while(1) {
		strcpy(my_str, memptr);
		printf("input data [%s]\n", my_str);
		if (strcmp(memptr, "exit") == 0)
			break;
		sleep(1);
	}
	shmdt(memptr);
	if (shmctl(shmid, IPC_RMID, (struct shmid_ds*)0) < 0) {
		perror("shmctl");
		exit(1);
	}
	return 0;
}

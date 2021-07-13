#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE 1024

typedef struct {
	long data_type;
	int data_num;
	char data_buf[BUF_SIZE];
} t_data;

int main(void) {
	int msqid;
	t_data data;

	if((msqid = msgget((key_t)1234, IPC_CREAT)) == -1) {
		perror("msgget() Failed");
		exit(1);
	}
	while (1) {
		if (msgrcv(msqid, &data, sizeof(t_data) - sizeof(long), 2, 0) == -1) {
			perror("msgcrv() Failed");
			exit(1);
		}
		printf("%d - %s\n", data.data_num, data.data_buf);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define SIZE 124
#define PRIOR 10 //maximum of priority

typedef struct {
	long type;
	char data[SIZE];
} msg_data;

int main() {
	int msqid, data_len;

	/* 1) get identifier if key '1234' is in message queue */
	if ((msqid = msgget((key_t)1234, IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}

	while(1) {
		/* 2) read message according to priority */
		msg_data msg;
		if (msgrcv(msqid, &msg, SIZE, -PRIOR, IPC_NOWAIT) == -1) {
			printf("no message\n");
			break;
		}
		printf("data : %s[%ld]\n", msg.data, msg.type);
	}
	/* 3) remove message queue msqid */
	msgctl(msqid, IPC_RMID, NULL);
	exit(0);
}

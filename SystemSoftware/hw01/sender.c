#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>

#define SIZE 124

typedef struct {
	long type;
	char data[SIZE];
} msg_data;

int main() {
	int msgqid, data_len;
	char buffer[SIZE];

	/* 1) Creat message queue with key 1234 */
	if ((msgqid = msgget((key_t)1234, IPC_CREAT | 0666)) == -1) {
		perror("msgget");
		exit(1);
	}

	while(1) {
		/* 2) Input data from standard input */
		msg_data msg;
		printf("input data => ");
		scanf("%s", msg.data);

		/* 3) If data content is 'quit', break */
		if (!strcmp(msg.data, "quit"))
			break;

		/* 4) send priority to standard input */
		printf("input priority => ");
		scanf("%ld", &msg.type);

		/* 5) send msg_data to queue msqid */
		if ((msgsnd(msgqid, &msg, SIZE, 0)) == -1) {
			perror("msgsnd");
			exit(1);
		}
	}
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
	int ndx = 0;
	t_data data;
	if ((msqid = msgget((key_t)1234, IPC_CREAT | 0666)) == -1) {
		perror("msgget() Failed");
		exit(1);
	}

	while (1) {
		data.data_type = (ndx++ % 3) + 1;
		data.data_num = ndx;
		sprintf(data.data_buf, "type=%ld, ndx=%d, http://forum.failnux.com", data.data_type, ndx);

		if (msgsnd(msqid, &data, sizeof(t_data) - sizeof(long), 0) == -1) {
			perror("msgsnd() Failed");
			exit(1);
		}
		sleep(1);
	}
}

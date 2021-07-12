#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 64
const char* ASK = "송신할 메세지를 적어주세요.(exit 입력시 종료): ";
const int MSG_TYPE = 1;

struct msgbuf {
	long type;
	char text[BUFSIZE];
};

int main() {
	struct msgbuf msgout;
	key_t key;
	int msgid, len;

	key = ftok("2017203014", 1);
	if ((msgid = msgget(key, IPC_CREAT | 0644)) == -1) {
		perror("msgget");
		exit(1);
	}
	msgout.type = MSG_TYPE;
	while (strcmp(msgout.text, "exit")) {
		write(1, ASK, strlen(ASK));
		len = read(0, msgout.text, BUFSIZE);
		msgout.text[len - 1] = '\0';
		if (msgsnd(msgid, (void*)&msgout, BUFSIZE, IPC_NOWAIT) == -1) {
			perror("msgsnd");
			exit(1);
		}
	}

	return 0;
}

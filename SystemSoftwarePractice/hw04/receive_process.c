#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 64
const char* RECEIVE1 = "메세지를 수신하였습니다. 내용은 [";
const char* RECEIVE2 = "]입니다.\n";
const char* QUIT = "종료되었습니다.\n";
const int MSG_TYPE = 1;

struct msgbuf {
	long type;
	char text[BUFSIZE];
};

int main() {
	struct msgbuf msgin;
	key_t key;
	int msgid, len;

	key = ftok("2017203014", 1);
	if ((msgid = msgget(key, IPC_CREAT | 0644)) == -1) {
		perror("msgget");
		exit(1);
	}
	while (strcmp(msgin.text, "exit")) {
		if (msgrcv(msgid, &msgin, BUFSIZE, MSG_TYPE, 0) == -1) {
			perror("msgsnd");
			exit(1);
		}
		write(1, RECEIVE1, strlen(RECEIVE1));
		write(1, msgin.text, strlen(msgin.text));
		write(1, RECEIVE2, strlen(RECEIVE2));
	}
	msgctl(msgid, IPC_RMID, NULL);
	write(1, QUIT, strlen(QUIT));

	return 0;
}

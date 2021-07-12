#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SIZE 32

int serv_sock;
struct sockaddr_in serv_addr;

typedef struct {
	int sock, win, lose, ready;
	char id[SIZE], ps[SIZE];
	struct sockaddr_in addr;
	pthread_t tid;
}Player;
Player clnt[2];

/* Handling */
void ErrorHandling(char *msg) {
	perror(msg);
	exit(1);
}
void SignalHandler(int signo) {
	for(int i = 0; i < 2; i++)
		if (clnt[i].sock) { close(clnt[i].sock); pthread_cancel(clnt[i].tid); }
	close(serv_sock);
	exit(0);
}

/* User management */
void SetUser(const char* id, const char* ps, int win, int lose) {
	int fd;
	char data[SIZE * 3];
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(id, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1) {
		chdir("..");
		return;
	}
	chdir("..");

	sprintf(data, "%s\n%d\n%d", ps, win, lose);
	write(fd, data, strlen(data));
}
void AddUser(const char* id, const char* ps) {
	SetUser(id, ps, 0, 0);
}
void DelUser(const char* id) {
	while (chdir("user")) mkdir("user", 0775);
	unlink(id);
	chdir("..");
}
int FindUser(const char* id, const char* ps) { //1: Found | 2: Not found
	int fd;
	char data[SIZE * 3];
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(id, O_RDONLY, 0664)) == -1) {
		chdir("..");
		return 2;
	}
	chdir("..");

	if (ps == NULL) {
		close(fd);
		return 1;
	}

	read(fd, data, sizeof(data));
	close(fd);
	if (strcmp(ps, strtok(data, "\n"))) {
		return 2;
	}
	return 1;
}
void GetUser(const char* id, int *win, int *lose) {
	int fd;
	char data[SIZE * 3], *token;
	if (strlen(id) <= 0) return;
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(id, O_RDONLY, 0664)) == -1) {
		chdir("..");
		return;
	}
	chdir("..");

	read(fd, data, sizeof(data));
	close(fd);

	strtok(data, "\n");
	if ((token = strtok(NULL, "\n")) == NULL)
		return;
	*win = atoi(token);
	if ((token = strtok(NULL, "\n")) == NULL)
		return;
	*lose = atoi(token);
}

/* Server Process */
void InitServer(int port) {
	if((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ErrorHandling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		ErrorHandling("bind() error");
	if(listen(serv_sock, 2) == -1)
		ErrorHandling("listen() error");

	signal(SIGINT, SignalHandler);
	signal(SIGKILL, SignalHandler);
}
void *ProcessClient(void *idx) {
	int me = *(int *)idx, ot = me == 0 ? 1 : 0;
	char data[SIZE * 3], buf[SIZE];
	printf("CONNECT: %d\n", clnt[me].sock);
	while(read(clnt[me].sock, data, sizeof(data)) > 0)
		switch(data[0]) {
		case 1:   //SIGN UP | data(all same): [index][id_len][ps_len][id][ps]
		case 2:   //SIGN IN | buf: [find][me + 1][win_len][lose_len][win][lose]
		case 3: { //WITHDRAWAL
			int bufSize = 1;
			char id[SIZE], ps[SIZE];
			memset(id, 0, SIZE);
			memset(ps, 0, SIZE);
			strncpy(id, data + 3, data[1]);
			strncpy(ps, data + 3 + data[1], data[2]);
			buf[0] = FindUser(id, data[0] == 1 ? NULL : ps);
			if (data[0] == 1) {
				if (buf[0] == 2) {
					AddUser(id, ps);
					printf("SIGN UP: %s\n", id);
				}
			}
			else if (data[0] == 2) {
				if (buf[0] == 1) {
					if (strcmp(clnt[me == 0 ? 1 : 0].id, id)) {
						printf("SIGN IN: %s\n", id);
						strcpy(clnt[me].id, id);
						strcpy(clnt[me].ps, ps);

						buf[1] = me + 1;
						GetUser(clnt[me].id,
							&clnt[me].win, &clnt[me].lose);
						buf[2] = 1;
						buf[3] = 1;
						for(int i = clnt[me].win; i >= 10; i /= 10) buf[2]++;
						for(int i = clnt[me].lose; i >= 10; i /= 10) buf[3]++;
						sprintf(buf + 4, "%d%d", clnt[me].win, clnt[me].lose);
						bufSize = 4 + buf[2] + buf[3];
					}
					else buf[0] = 3;
				}
			}
			else if (data[0] == 3) {
				if (buf[0] == 1) {
					DelUser(id);
					memset(clnt[me].id, 0, SIZE);
					printf("WITHDRAWAL: %s\n", id);
				}
			}
			write(clnt[me].sock, buf, bufSize);
			break;}

		case 4: //SIGN OUT | data: [index]
			printf("SIGN OUT: %s\n", clnt[me].id);
			memset(clnt[me].id, 0, SIZE);
			break;

		case 5: { //STATISTICS | data: [index] | buf:
				  //[o_id_len][o_win_len][o_lose_len][o_id][o_win][o_lose]
			clnt[me].ready = 1;
			if (!clnt[ot].ready) break;

			for(int p1 = me, p2 = ot, i = 0; i < 2; i++) {
				memset(data, 0, sizeof(data));
				data[0] = strlen(clnt[p2].id);
				data[1] = 1;
				data[2] = 1;
				for(int i = clnt[p2].win; i >= 10; i /= 10) data[1]++;
				for(int i = clnt[p2].lose; i >= 10; i /= 10) data[2]++;
				sprintf(data + 3, "%s%d%d", clnt[p2].id, clnt[p2].win, clnt[p2].lose);
				write(clnt[p1].sock, data, strlen(data));
				p1 = ot;
				p2 = me;
			}
			break;}

		case 6: { //GAME | data: [index][subindex][metadata]
			if (data[1] == 1) { //GAME START
				clnt[me].ready = 0;
				if (clnt[ot].ready) break;
				printf("GAME START: %s, %s\n", clnt[0].id, clnt[1].id);
				buf[0] = 1;
				write(clnt[0].sock, buf, 1);
				write(clnt[1].sock, buf, 1);
			}
			else if (data[1] == 2 || data[1] == 3) { //MOVE, SET | metadata: [row + 1][col + 1]
				write(clnt[ot].sock, data + 1, 3);
				if (data[1] == 3)
					printf("GAME: %s %d,%d\n", clnt[me].id, data[2] - 1, data[3] - 1);
			}
			else if (data[1] == 4) { //GAME END | metadata: none
				if (--data[2] == 2) printf("GAME END: DRAW\n");
				else {
					Player *winner = &clnt[data[2]];
					Player *loser = &clnt[data[2] ? 0 : 1];
					printf("GAME END: %s win\n", winner->id);
					SetUser(winner->id, winner->ps, ++(winner->win), winner->lose);
					SetUser(loser->id, loser->ps, loser->win, ++(loser->lose));
				}
			}
			else if (data[1] >= 5 || data[1] <= 7) {
				//5:NEXT TURN | metadata: none
				//6:REGAME | metadata: none
				//7:EXIT | metadata: none
				write(clnt[ot].sock, data + 1, 1);
				if (data[1] == 5) {
					buf[0] = 1;
					write(clnt[0].sock, buf, 1);
					write(clnt[1].sock, buf, 1);
				}
				else if (data[1] == 7) {
					clnt[0].ready = 0;
					clnt[1].ready = 0;
				}
			}
			break;}
		}
	close(clnt[me].sock);
	printf("DISCONNECT: %d\n", clnt[me].sock);
	memset(&clnt[me], 0, sizeof(clnt[me]));
}
void AcceptClient() {
	int clnt_sock, clnt_addr_size;
	struct sockaddr_in clnt_addr;
	char buf[1];

	if ((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size)) == -1)
		ErrorHandling("accept() error");
	int idx = !clnt[0].sock ? 0 : !clnt[1].sock ? 1 : 2;
	if (idx != 2) {
		buf[0] = 1;
		write(clnt_sock, buf, 1);
		clnt[idx].sock = clnt_sock;
		clnt[idx].addr = clnt_addr;
		if (pthread_create(&clnt[idx].tid, NULL, ProcessClient, (void *)&idx))
				ErrorHandling("pthread_create() error");
	}
	else {
		buf[0] = 2;
		write(clnt_sock, buf, 1);
		close(clnt_sock);
		printf("REFUSE: %d\n", clnt_sock);
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s [port]\n", argv[0]);
		exit(1);
	}
	InitServer(atoi(argv[1]));
	while(1) AcceptClient();
	return 0;
}

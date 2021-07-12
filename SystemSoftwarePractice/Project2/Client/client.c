#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SIZE 32

int sock;
struct sockaddr_in serv_addr;
char id[SIZE], ps[SIZE];
int sel, me, cursor, turn, winner;
char stone[6][6];

typedef enum {
	MAIN_NOLOGIN,
	MAIN_LOGIN,
	SIGNUP,
	SIGNIN,
	WITHDRAWAL,
	STATISTICS,
	GAME
} MAPNO;
MAPNO map;

typedef struct {
	char id[SIZE];
	int win, lose, count;
}Player;
Player player[2];

void ErrorHandling(char *msg) {
	perror(msg);
	exit(1);
}
void FlushInput() {
	nodelay(stdscr, TRUE);
	while (getch() != ERR) ;
	nodelay(stdscr, FALSE);
}

/* Stone checking */
int SearchStone(char search_st, char exit_st, int y, int x, int my, int mx, int c) {
	if (y < 0 || x < 0 || y >= 6 || x >= 6 || (!mx && !my)) return 0;
	return stone[y][x] == search_st ? c : stone[y][x] == exit_st ? 0 :
		SearchStone(search_st, exit_st, y + my, x + mx, my, mx, ++c);
}
int CheckTurn(int t) {
	char start;
	char my_stone = t ? 'X' : 'O';
	char ot_stone = t ? 'O' : 'X';
	int count_blk = 36 - player[0].count - player[1].count;
	if (count_blk <= (player[0].count < player[1].count ? player[0].count : player[1].count)) start = ' ';
	else if (player[t].count <= player[t ? 0 : 1].count) start = my_stone;
	else start = ot_stone;

	for (int y = 0; y < 6; y++)
	for (int x = 0; x < 6; x++)
	if (stone[y][x] == start)
		for (int my = -1; my <= 1; my++)
		for (int mx = -1; mx <= 1; mx++) {
			if (start == ' ' &&
				SearchStone(my_stone, ' ', y + my, x + mx, my, mx, 0)) return 1;
			else if (start == my_stone &&
				SearchStone(' ', my_stone, y + my, x + mx, my, mx, 0)) return 1;
			else if (start == ot_stone &&
				SearchStone(my_stone, ' ', y + my, x + mx, my, mx, 1) &&
				SearchStone(' ', my_stone, y - my, x - mx, -my, -mx, 1)) return 1;
		}
	return 0;
}

/* Stone setting */
int TurnStone(WINDOW* win, int t, int y, int x, int my, int mx, int c) {
	char my_stone = t ? 'X' : 'O';
	char ot_stone = t ? 'O' : 'X';
	if (y < 0 || x < 0 || y >= 6 || x >= 6) return 0;
	if (stone[y][x] == ot_stone) {
		if (c = TurnStone(win, t, y + my, x + mx, my, mx, ++c)) {
			stone[y][x] = my_stone;
			mvwprintw(win, 6 + y * 2, 18 + x * 4, " %c ", my_stone);
			return c;
		}
	}
	else if (stone[y][x] == my_stone) return c;
	return 0;
}
int SetStone(WINDOW* win, int t, int y, int x) {
	int turn_count = 0;
	if (stone[y][x] != ' ') return 0;

	for(int my = -1; my <= 1; my++)
		for(int mx = -1; mx <= 1; mx++)
			turn_count += TurnStone(win, t, y + my, x + mx, my, mx, 0);
	if (turn_count) {
		stone[y][x] = t ? 'X' : 'O';
		wattron(win, COLOR_PAIR(2));
		mvwprintw(win, 6 + y * 2, 18 + x * 4, " %c ", stone[y][x]);
		wattroff(win, COLOR_PAIR(2));
		player[t ? 0 : 1].count -= turn_count;
		player[t].count += turn_count + 1;
	}
	return turn_count;
}

/* Setup */
void Setup(char *ip, int port) {
	/* socket */
	char buf[1];
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ErrorHandling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		ErrorHandling("connect() error");
	if (read(sock, buf, 1) == 0) {
		printf("Server connection error\n");
		close(sock);
		exit(1);
	}
	if (buf[0] == 2) {
		printf("Server is full\n");
		close(sock);
		exit(1);
	}

	/* ncurses */
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	if (has_colors() == FALSE) {
		printf("Therminal does not support colors!\n");
		endwin();
		exit(1);
	} else {
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_WHITE);
		init_pair(2, COLOR_WHITE, COLOR_BLUE);
	}
	refresh();

	map = MAIN_NOLOGIN;
	sel = 0;
}

/* Drawing window */
void Init(WINDOW** win) {
	if (map == GAME) {
		win[0] = newwin(24, 60, 0, 0);
		win[1] = newwin(24, 20, 0, 60);
	}
	else {
		win[0] = newwin(18, 80, 0, 0);
		win[1] = newwin(6, 80, 18, 0);
	}
	wbkgd(win[0], COLOR_PAIR(1));
	wbkgd(win[1], COLOR_PAIR(2));
	wclear(win[0]);
	wclear(win[1]);
	switch(map) {
	case MAIN_NOLOGIN:
	case MAIN_LOGIN:
		if (map == MAIN_NOLOGIN) {
			mvwprintw(win[0], 5, 28, "System Software Practice");
			wattron(win[0], A_BOLD);
			mvwprintw(win[0], 7, 36, "OTHELLO");
			wattroff(win[0], A_BOLD);
			mvwprintw(win[0], 14, 68, "2017203014");
			mvwprintw(win[0], 16, 65, "Gyeongho Yang");
		}
		else {
			char text_id[SIZE + 12] = "PLAYER ID : ";
			strcat(text_id, id);
			int x = 40 - strlen(text_id) / 2;
			mvwprintw(win[0], 5, x, text_id);
		}

		if (sel != 0) mvwprintw(win[1], 3, 8, map == MAIN_NOLOGIN ? "SIGN IN" : "PLAY");
		if (sel != 1) mvwprintw(win[1], 3, 36, map == MAIN_NOLOGIN ? "SIGN UP" : "SIGN OUT");
		if (sel != 2) mvwprintw(win[1], 3, 64, map == MAIN_NOLOGIN ? "EXIT" : "WITHDRAWAL");
		wattron(win[1], COLOR_PAIR(1));
		if (sel == 0) mvwprintw(win[1], 3, 8, map == MAIN_NOLOGIN ? "SIGN IN" : "PLAY");
		else if (sel == 1) mvwprintw(win[1], 3, 36, map == MAIN_NOLOGIN ? "SIGN UP" : "SIGN OUT");
		else if (sel == 2) mvwprintw(win[1], 3, 64, map == MAIN_NOLOGIN ? "EXIT" : "WITHDRAWAL");
		wattroff(win[1], COLOR_PAIR(1));
		return;

	case SIGNUP:
	case SIGNIN:
	case WITHDRAWAL:
		curs_set(1);
		sel = map == WITHDRAWAL ? 1 : 0;
		if (sel == 0) memset(id, 0, sizeof(id));
		memset(ps, 0, sizeof(ps));

		wattron(win[0], A_BOLD);
		mvwprintw(win[0], 6, 36, map == SIGNUP ?"SIGN UP" :
			map == SIGNIN ? "SIGN IN" : "WITHDRAWAL");
		wattroff(win[0], A_BOLD);
		if (map == WITHDRAWAL)
			mvwprintw(win[0], 8, 31, "ID : %s", id);
		else
			mvwprintw(win[0], 8, 31, "ID :");
		mvwprintw(win[0], 10, 25, "PASSWORD :");

		mvwprintw(win[1], 3, 14, map == SIGNUP ? "SIGN UP" :
			map == SIGNIN ? "SIGN IN" : "WITHDRAWAL");
		mvwprintw(win[1], 3, 60, "BACK");
		return;

	case STATISTICS: {
		wattron(win[0], A_BOLD);
		mvwprintw(win[0], 7, 14, "STATISTICS");
		mvwprintw(win[0], 7, 56, "STATISTICS");
		wattroff(win[0], A_BOLD);
		mvwprintw(win[1], 3, 36, "WAITING");

		for(int idx = 0; idx < 2; idx++) {
			double avg = 0;
			int dx = 13 + idx * 42 - strlen(player[idx].id) / 2;
			if (!strlen(player[idx].id)) {
				mvwprintw(win[0], 5, dx, "PLAYER%d ID :", idx + 1);
				//mvwprintw(win[0], 9, idx ? 46 : 4, "WIN :   / LOSE :   (      %)");
				continue;
			}
			mvwprintw(win[0], 5, dx, "PLAYER%d ID : %s", idx + 1, player[idx].id);
			if ((avg = player[idx].win + player[idx].lose) > 0)
				avg = player[idx].win / avg * 100;
			mvwprintw(win[0], 9, idx ? 46 : 4, "WIN : %d / LOSE : %d (%.3f%)",
				player[idx].win, player[idx].lose, avg);
		}
		char buf[1] = { 5 };
		write(sock, buf, 1);
		return;}

	case GAME: {
		cursor = 14;
		turn = 0;
		sel = 0;
		winner = -1;
		memset(stone, ' ', sizeof(stone));
		stone[2][2] = 'X';
		stone[2][3] = 'O';
		stone[3][2] = 'O';
		stone[3][3] = 'X';

		//Test code
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 6; j++)
				stone[i][j] = (i + j) % 2 ? 'X' : 'O';

		player[0].count = 2;
		player[1].count = 2;
		mvwprintw(win[0], 5, 17, "+---+---+---+---+---+---+");
		for(int y = 6; y <= 17; y += 2) {
			mvwprintw(win[0], y, 17, "|   |   |   |   |   |   |");
			mvwprintw(win[0], y + 1, 17, "+---+---+---+---+---+---+");
		}
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				mvwprintw(win[0], 6 + i * 2, 18 + j * 4, " %c ", stone[i][j]);
		for(int i = 0; i < 2; i++)
			mvwprintw(win[1], 9 + i, 3, "%s(%c) : %d",
				player[i].id, i ? 'X' : 'O', player[i].count);
		mvwprintw(win[1], 13, 5, "NEXT TURN");
		mvwprintw(win[1], 15, 6, "REGAME");
		mvwprintw(win[1], 17, 6, "EXIT");
		wattron(win[1], A_UNDERLINE);
		mvwaddch(win[1], 13, 5, 'N');
		mvwaddch(win[1], 15, 6, 'R');
		mvwaddch(win[1], 17, 7, 'X');
		wattroff(win[1], A_UNDERLINE);

		char buf[1];
		mvwprintw(win[0], 23, 0, ">>> Waiting for another player...");
		wrefresh(win[0]);
		wrefresh(win[1]);
		read(sock, buf, 1);
		mvwprintw(win[0], 23, 0, "                                 ");
		FlushInput();

		wattron(win[0], COLOR_PAIR(2));
		mvwprintw(win[0], 10, 26, " %c ", stone[2][2]);
		wattroff(win[0], COLOR_PAIR(2));
		wattron(win[1], COLOR_PAIR(1));
		mvwprintw(win[1], 9, 3, "%s(O)", player[0].id);
		wattroff(win[1], COLOR_PAIR(1));
		return;}
	}
}
void Quit(WINDOW** win) {
	delwin(win[0]);
	delwin(win[1]);
}
void Step(WINDOW** win) {
	int key, sel_prv = sel;
	switch(map) {
	case MAIN_NOLOGIN:
	case MAIN_LOGIN:
		/* sel */
		// 0: focus sign in
		// 1: focus sign up
		// 2: focus exit
		key = getch();
		if (key == KEY_LEFT) sel--;
		else if (key == KEY_RIGHT) sel++;
		else if (key == 10) {
			Quit(win);
			if (map == MAIN_NOLOGIN)
				map = sel == 0 ? SIGNIN : sel == 1 ? SIGNUP : -1;
			else {
				map = sel == 0 ? STATISTICS : sel == 1 ? MAIN_NOLOGIN : WITHDRAWAL;
				if (sel == 1) {
					char buf[1];
					buf[0] = 4;
					write(sock, buf, 1);
				}
			}
			Init(win);
			return;
		}
		else return;
		sel += sel < 0 ? 3 : sel >= 3 ? -3 : 0;

		if (sel_prv == 0) mvwprintw(win[1], 3, 8, map == MAIN_NOLOGIN ? "SIGN IN" : "PLAY");
		if (sel_prv == 1) mvwprintw(win[1], 3, 36, map == MAIN_NOLOGIN ? "SIGN UP" : "SIGN OUT");
		if (sel_prv == 2) mvwprintw(win[1], 3, 64, map == MAIN_NOLOGIN ? "EXIT" : "WITHDRAWAL");
		wattron(win[1], COLOR_PAIR(1));
		if (sel == 0) mvwprintw(win[1], 3, 8, map == MAIN_NOLOGIN ? "SIGN IN" : "PLAY");
		else if (sel == 1) mvwprintw(win[1], 3, 36, map == MAIN_NOLOGIN ? "SIGN UP" : "SIGN OUT");
		else if (sel == 2) mvwprintw(win[1], 3, 64, map == MAIN_NOLOGIN ? "EXIT" : "WITHDRAWAL");
		wattroff(win[1], COLOR_PAIR(1));
		return;

	case SIGNUP:
	case SIGNIN:
	case WITHDRAWAL:
		/* sel */
		// 0: input id
		// 1: input password
		// 2: focus sign up, sign in, withdrawal
		// 3: focus back
		if (sel <= 1) {
			int idx = strlen(sel == 0 ? id : ps);
			move(sel == 0 ? 8 : 10, 36 + idx);
			while((key = getch()) != 10 && key != '	') {
				if (map != WITHDRAWAL && key == KEY_UP && sel == 1) { sel = 0; return; }
				if (key == KEY_DOWN) break;
				else if (key == '' || key == 263) {
					if (idx == 0) continue;
					mvwaddch(win[0], sel == 0 ? 8 : 10, 35 + idx, ' ');
					wrefresh(win[0]);
					move(sel == 0 ? 8 : 10, 35 + idx);
					if (sel == 0) id[--idx] = '\0';
					else ps[--idx] = '\0';
					continue;
				}
				else if (key < ' ' || key > '~' || idx >= SIZE) continue;
				if (sel == 0) id[idx] = key;
				else ps[idx] = key;
				mvwaddch(win[0], sel == 0 ? 8 : 10, 36 + idx, sel == 0 ? key : '*');
				wrefresh(win[0]);
				idx++;
			}
			if (sel == 0) { sel++; return; }
			else {
				sel = 3;
				key = KEY_LEFT;
				curs_set(0);
			}
		}
		else key = getch();

		if (key == KEY_UP)
		{
			if (sel == 2) mvwprintw(win[1], 3, 14,
				map == SIGNUP ? "SIGN UP" : map == SIGNIN ? "SIGN IN" : "WITHDRAWAL");
			else if (sel == 3) mvwprintw(win[1], 3, 60, "BACK");
			sel = 1;
			curs_set(1);
			return;
		}
		else if (key == KEY_LEFT || key == KEY_RIGHT) {
			if (sel == 2) mvwprintw(win[1], 3, 14,
				map == SIGNUP ? "SIGN UP" : map == SIGNIN ? "SIGN IN" : "WITHDRAWAL");
			else if (sel == 3) mvwprintw(win[1], 3, 60, "BACK");
			sel = sel == 2 ? 3 : 2;
			wattron(win[1], COLOR_PAIR(1));
			if (sel == 2) mvwprintw(win[1], 3, 14,
				map == SIGNUP ? "SIGN UP" : map == SIGNIN ? "SIGN IN" : "WITHDRAWAL");
			else if (sel == 3) mvwprintw(win[1], 3, 60, "BACK");
			wattroff(win[1], COLOR_PAIR(1));
			return;
		}
		else if (key != 10) return;

		int map_go;
		if (sel == 2) {
			char data[SIZE * 3];
			data[0] = map - 1;
			data[1] = strlen(id);
			data[2] = strlen(ps);
			if (data[1] == 0 || data[2] == 0) return;
			strcpy(data + 3, id);
			strcpy(data + 3 + data[1], ps);
			write(sock, data, 3 + data[1] + data[2]);
			read(sock, data, SIZE);
			int find = data[0];
			if (map == SIGNUP) {
				if (find == 2) {
					mvwprintw(win[1], 5, 0, ">>> Welcome to OTHELLO World! (Press any key...)");
					map_go = MAIN_NOLOGIN;
				}
				else {
					mvwprintw(win[1], 5, 0, ">>> %s has already exist in DB! (Please any key...)", id);
					map_go = map;
				}
				wrefresh(win[1]);
				getch();
			}
			else {
				if (find == 1) {
					if (map == SIGNIN) {
						map_go = MAIN_LOGIN;
						me = data[1] - 1;
						strcpy(player[me].id, id);
						char winStr[SIZE], loseStr[SIZE];
						strncpy(winStr, data + 4, data[2]);
						strncpy(loseStr, data + 4 + data[2], data[3]);
						player[me].win = atoi(winStr);
						player[me].lose = atoi(loseStr);
					}
					else {
						mvwprintw(win[1], 5, 0, ">>> User %s deleted! (Press any key...)", id);
						wrefresh(win[1]);
						map_go = MAIN_NOLOGIN;
						getch();
					}
				}
				else {
					if (find == 2)
						mvwprintw(win[1], 5, 0, ">>> Invalid %spassword! (Press any key...)",
							map == WITHDRAWAL ? "" : "id or ");
					else mvwprintw(win[1], 5, 0, ">>> User %s is already logged in! (Press any key...)", id);
					wrefresh(win[1]);
					map_go = map;
					getch();
				}
			}
			sel = 0;
		}
		else {
			map_go = map == WITHDRAWAL ? MAIN_LOGIN : MAIN_NOLOGIN;
			sel = map == SIGNUP ? 1 : 0;
		}
		Quit(win);
		map = map_go;
		Init(win);
		return;

	case STATISTICS: {
		int ot = me ? 0 : 1;
		if (!strlen(player[ot].id)) {
			double avg = 0;
			char data[SIZE];
			data[0] = 5;
			read(sock, data, SIZE);

			strncpy(player[ot].id, data + 3, data[0]);
			player[ot].id[data[0]] = '\0';
			char winStr[SIZE], loseStr[SIZE];
			strncpy(winStr, data + 3 + data[0], data[1]);
			strncpy(loseStr, data + 3 + data[0] + data[1], data[2]);
			winStr[strlen(winStr)] = '\0';
			loseStr[strlen(loseStr)] = '\0';
			player[ot].win = atoi(winStr);
			player[ot].lose = atoi(loseStr);

			mvwprintw(win[0], 5, 13 + ot * 42 - strlen(player[ot].id) / 2,
				"PLAYER%d ID : %s", ot + 1, player[ot].id);
			if ((avg = player[ot].win + player[ot].lose) > 0)
				avg = player[ot].win / avg * 100;
			mvwprintw(win[0], 9, ot ? 46 : 4, "WIN : %d / LOSE : %d (%.3f%)",
				player[ot].win, player[ot].lose, avg);
			mvwprintw(win[1], 3, 36, "       ");
			wattron(win[1], COLOR_PAIR(1));
			mvwprintw(win[1], 3, 39, "OK");
			wattroff(win[1], COLOR_PAIR(2));

			FlushInput();
			return;
		}

		if (getch() != 10) return;
		if (!strlen(player[0].id) || !strlen(player[1].id)) return;
		char buf[2] = { 6, 1 };
		write(sock, buf, 2);
		Quit(win);
		map = GAME;
		Init(win);
		return;}

	case GAME: {
		/* sel */
		// 0: playing game
		// 1: focus regame
		// 2: focus exit
		int cursor_prv = cursor, turn_prv = turn;
		int row = cursor / 6, col = cursor % 6;

		if (turn == me || winner != -1) {
			if ((key = getch()) == KEY_LEFT) cursor += cursor % 6 == 0 ? 5 : -1;
			else if (key == KEY_RIGHT) cursor += (cursor + 1) % 6 == 0 ? -5 : 1;
			else if (key == KEY_UP) {
				if (sel) { if (--sel < (winner == -1 ? 1 : 2))
					sel += winner == -1 ? 3 : 2; }
				else cursor += cursor < 6 ? 30 : -6;
			}
			else if (key == KEY_DOWN) {
				if (sel) { if (++sel > 3) sel -= winner == -1 ? 3 : 2; }
				else cursor += cursor >= 30 ? -30 : 6;
			}
			if (winner != -1) cursor = cursor_prv;
			if (!sel && cursor != cursor_prv) { //Send MOVE
				char buf[4] = { 6, 2, (cursor / 6) + 1, (cursor % 6) + 1 };
				write(sock, buf, 4);
			}
		}
		else {
			char data[SIZE];
			read(sock, data, SIZE);
			FlushInput();
			switch(data[0]) {
			case 2: //MOVE | data: [index][row + 1][col + 1]
			case 3: //SET
				sel = 0;
				cursor = (data[1] - 1) * 6 + (data[2] - 1);
				if (data[0] == 3) key = 10;
				break;
			case 5: //NEXT TURN | data: none
				sel = 0;
				turn = turn ? 0 : 1;
				key = 0;
				break;
			case 6: //REGAME
			case 7: //EXIT
				sel = data[0] - 4;
				key = 10;
				break;
			}
		}

		if (!sel && (key == ' ' || key == 10)) {
			if (!SetStone(win[0], turn, row, col)) return;
			if (turn == me) {
				char buf[4] = { 6, 3, (cursor / 6) + 1, (cursor % 6) + 1 };
				write(sock, buf, 4);
			}

			mvwprintw(win[1], 9, 12, "%d ", player[0].count);
			mvwprintw(win[1], 10, 12, "%d ", player[1].count);
			if (!CheckTurn(turn ? 0 : 1)) {
				if (CheckTurn(turn)) return;
				winner = player[0].count == player[1].count ? 2 : player[0].count > player[1].count ? 0 : 1;
				mvwprintw(win[1], 13, 5, "         ");
				if (winner == 2) mvwprintw(win[1], 13, 6, "Draw!");
				else mvwprintw(win[1], 13, 6, "%s Win!", player[winner].id);
				sel = 2;
				if (winner == me) {
					char buf[3] = { 6, 4, winner + 1 };
					write(sock, buf, 3);
					player[me].win++;
				}
				else player[me].lose++;
			}
			else {
				mvwprintw(win[1], turn ? 10 : 9, 3, "%s(%c)",
					player[turn].id, turn ? 'X' : 'O');
				turn = turn ? 0 : 1;
				wattron(win[1], COLOR_PAIR(1));
				mvwprintw(win[1], turn ? 10 : 9, 3, "%s(%c)",
					player[turn].id, turn ? 'X' : 'O');
				wattroff(win[1], COLOR_PAIR(1));
			}
		}
		else if (key >= 'a' && key <= 'z') {
			if (winner == -1) {
				if (key == 'g') sel = 0;
				else if (key == 'n') sel = 1;
				else if (key == 'r') sel = 2;
				else if (key == 'x') sel = 3;
			}
		}
		else if (key == 10 && sel) {
			if (winner == -1 && turn == me) { //Send NEXT TURN, REGAME, EXIT
				char buf[2] = { 6, sel + 4 };
				write(sock, buf, 2);
			}
			if (sel == 1) { //NEXT TURN
				turn = turn ? 0 : 1;
				sel = 0;
			}
			else if (sel == 2) { //REGAME
				cursor = 14;
				turn = 0;
				sel = 0;
				winner = -1;
				memset(stone, ' ', sizeof(stone));
				stone[2][2] = 'X';
				stone[2][3] = 'O';
				stone[3][2] = 'O';
				stone[3][3] = 'X';

				for (int i = 0; i < 6; i++)
					for (int j = 0; j < 6; j++)
						mvwprintw(win[0], 6 + i * 2, 18 + j * 4, " %c ", stone[i][j]);
				for(int i = 0; i < 2; i++) {
					player[i].count = 2;
					mvwprintw(win[1], 9 + i, 9 + strlen(player[i].id), "%d", player[i].count);
				}
			}
			else { //EXIT
				Quit(win);
				int ot = me ? 0 : 1;
				memset(player[ot].id, 0, sizeof(player[ot].id));
				map = MAIN_LOGIN;
				sel = 0;
				Init(win);
				return;
			}
		}
		if (turn != turn_prv) {
			mvwprintw(win[1], turn_prv ? 10 : 9, 3, "%s(%c)",
				player[turn_prv].id, turn_prv ? 'X' : 'O');
			wattron(win[1], COLOR_PAIR(1));
			mvwprintw(win[1], turn ? 10 : 9, 3, "%s(%c)",
				player[turn].id, turn ? 'X' : 'O');
			wattroff(win[1], COLOR_PAIR(1));
		}

		mvwprintw(win[0], 6 + row * 2, 18 + col * 4, " %c ", stone[row][col]);
		int dy, dsx, dcx;
		char ds[10], dc;
		if (sel_prv) {
			if (sel_prv == 1) { dy = 13; dsx = 5; strcpy(ds, "NEXT TURN"); dcx = 5; dc = 'N'; }
			else if (sel_prv == 2) { dy = 15; dsx = 6; strcpy(ds, "REGAME"); dcx = 6; dc = 'R'; }
			else if (sel_prv == 3) { dy = 17; dsx = 6; strcpy(ds, "EXIT"); dcx = 7; dc = 'X'; }
			mvwprintw(win[1], dy, dsx, ds);
			wattron(win[1], A_UNDERLINE);
			mvwaddch(win[1], dy, dcx, dc);
			wattroff(win[1], A_UNDERLINE);
		}
		if (sel) {
			if (sel == 1) { dy = 13; dsx = 5; strcpy(ds, "NEXT TURN"); dcx = 5; dc = 'N'; }
			else if (sel == 2) { dy = 15; dsx = 6; strcpy(ds, "REGAME"); dcx = 6; dc = 'R'; }
			else if (sel == 3) { dy = 17; dsx = 6; strcpy(ds, "EXIT"); dcx = 7; dc = 'X'; }
			wattron(win[1], COLOR_PAIR(1));
			mvwprintw(win[1], dy, dsx, ds);
			wattron(win[1], A_UNDERLINE);
			mvwaddch(win[1], dy, dcx, dc);
			wattroff(win[1], A_UNDERLINE);
			wattroff(win[1], COLOR_PAIR(1));
			return;
		}

		wattron(win[0], COLOR_PAIR(2));
		row = cursor / 6;
		col = cursor % 6;
		mvwprintw(win[0], 6 + row * 2, 18 + col * 4, " %c ", stone[row][col]);
		wattroff(win[0], COLOR_PAIR(2));
		return;}
	}
}

int main(int argc, char **argv) {
	if(argc != 3) {
		printf("Usage: %s [ip] [port]\n", argv[0]);
		exit(1);
	}
	WINDOW *win[2];
	Setup(argv[1], atoi(argv[2]));
	Init(win);
	wrefresh(win[0]);
	wrefresh(win[1]);

	while(map != -1) {
		Step(win);
		wrefresh(win[0]);
		wrefresh(win[1]);
	}

	endwin();
	return 0;
}

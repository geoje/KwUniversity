#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define SIZE 32

char id[SIZE], ps[SIZE];
int sel, winning, losing, cursor, turn, count[2];
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

/* User management */
void AddUser(const char* myid, const char* myps) {
	int fd;
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(myid, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1) {
		chdir("..");
		return;
	}
	chdir("..");

	write(fd, myps, strlen(myps));
	write(fd, "\n0\n0", 4);
}
void DelUser(const char* myid) {
	while (chdir("user")) mkdir("user", 0775);
	unlink(myid);
	chdir("..");
}
int FindUser(const char* myid, const char* myps) {
	int fd;
	char data[SIZE * 2];
	if (strlen(myid) <= 0) return -1;
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(myid, O_RDONLY, 0664)) == -1) {
		chdir("..");
		return 0;
	}
	chdir("..");

	if (myps == NULL) {
		close(fd);
		return 1;
	}

	read(fd, data, sizeof(data));
	close(fd);
	if (strcmp(myps, strtok(data, "\n"))) {
		return 0;
	}
	return 1;
}
void SetUser(const char* myid, const char* myps, int mywin, int mylose) {
}
void GetUser(const char* myid) {
	int fd;
	char data[SIZE * 2], *token;
	if (strlen(myid) <= 0) return;
	while (chdir("user")) mkdir("user", 0775);
	if ((fd = open(myid, O_RDONLY, 0664)) == -1) {
		chdir("..");
		return;
	}
	chdir("..");

	read(fd, data, sizeof(data));
	close(fd);

	strtok(data, "\n");
	if ((token = strtok(NULL, "\n")) == NULL)
		return;
	winning = atoi(token);
	if ((token = strtok(NULL, "\n")) == NULL)
		return;
	losing = atoi(token);
}

/* Stone checking */
int SearchStone(char search_st, char exit_st, int y, int x, int my, int mx, int c) {
	if (y < 0 || x < 0 || y >= 6 || x >= 6 || (!mx && !my)) return 0;
	return stone[y][x] == search_st ? c : stone[y][x] == exit_st ? 0 :
		SearchStone(search_st, exit_st, y + my, x + mx, my, mx, ++c);
}
int CheckTurn(int t) {
	char start;
	char my_stone = t == 0 ? 'O' : 'X';
	char ot_stone = t == 0 ? 'X' : 'O';
	int count_blk = 36 - count[0] - count[1];
	if (count_blk <= (count[0] < count[1] ? count[0] : count[1])) start = ' ';
	else if (count[t] <= count[t == 0 ? 1 : 0]) start = my_stone;
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
	char my_stone = t == 0 ? 'O' : 'X';
	char ot_stone = t == 0 ? 'X' : 'O';
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
		stone[y][x] = t == 0 ? 'O' : 'X';
		wattron(win, COLOR_PAIR(2));
		mvwprintw(win, 6 + y * 2, 18 + x * 4, " %c ", stone[y][x]);
		wattroff(win, COLOR_PAIR(2));
		count[t == 0 ? 1 : 0] -= turn_count;
		count[t] += turn_count + 1;
	}
	return turn_count;
}

/* Drawing window */
int Setup() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	if (has_colors() == FALSE) {
		puts("Therminal does not support colors!");
		return 1;
	} else {
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_WHITE);
		init_pair(2, COLOR_WHITE, COLOR_BLUE);
	}
	refresh();

	map = MAIN_NOLOGIN;
	sel = 0;
	return 0;
}
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
		double avg = 0;
		char text[SIZE + 12];
		strcpy(text, "PLAYER ID : ");
		strcat(text, id);
		int x = 40 - strlen(text) / 2;
		mvwprintw(win[0], 5, x, text);
		wattron(win[0], A_BOLD);
		mvwprintw(win[0], 7, 35, "STATISTICS");
		wattroff(win[0], A_BOLD);

		GetUser(id);
		if ((avg = winning + losing) > 0)
			avg = winning / avg * 100;
		mvwprintw(win[0], 9, 26, "WIN : %d / LOSE : %d (%.3f%)", winning, losing, avg);

		wattron(win[1], COLOR_PAIR(1));
		mvwprintw(win[1], 3, 39, "OK");
		wattroff(win[1], COLOR_PAIR(1));
		return;
	}

	case GAME:
		cursor = 14;
		turn = 0;
		sel = 0;
		memset(stone, ' ', sizeof(stone));
		stone[2][2] = 'X';
		stone[2][3] = 'O';
		stone[3][2] = 'O';
		stone[3][3] = 'X';
		count[0] = 2;
		count[1] = 2;
		mvwprintw(win[0], 5, 17, "+---+---+---+---+---+---+");
		for(int y = 6; y <= 17; y += 2) {
			mvwprintw(win[0], y, 17, "|   |   |   |   |   |   |");
			mvwprintw(win[0], y + 1, 17, "+---+---+---+---+---+---+");
		}
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				mvwprintw(win[0], 6 + i * 2, 18 + j * 4, " %c ", stone[i][j]);
		wattron(win[0], COLOR_PAIR(2));
		mvwprintw(win[0], 10, 26, " %c ", stone[2][2]);
		wattroff(win[0], COLOR_PAIR(2));

		wattron(win[1], COLOR_PAIR(1));
		mvwprintw(win[1], 9, 4, "1P(O)");
		wattroff(win[1], COLOR_PAIR(1));
		mvwprintw(win[1], 9, 9, " : %d", count[0]);
		mvwprintw(win[1], 10, 4, "2P(X) : %d", count[1]);
		mvwprintw(win[1], 15, 5, "REGAME");
		mvwprintw(win[1], 17, 5, "EXIT");
		wattron(win[1], A_UNDERLINE);
		mvwaddch(win[1], 15, 5, 'R');
		mvwaddch(win[1], 17, 6, 'X');
		wattroff(win[1], A_UNDERLINE);
		return;
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
			else	map = sel == 0 ? STATISTICS : sel == 1 ? MAIN_NOLOGIN : WITHDRAWAL;
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
			if (sel == 0) { sel = 1; return; }
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
			int find = FindUser(id, map == SIGNUP ? NULL : ps);
			if (map == SIGNUP) {
				if (find == -1) {
					mvwprintw(win[1], 5, 0, ">>> Invalid id or password (Press any key...)");
					map_go = map;
				}
				else if (find == 1) {
					mvwprintw(win[1], 5, 0, ">>> %s has already exist in DB! (Please any key...)", id);
					map_go = map;
				}
				else {
					AddUser(id, ps);
					mvwprintw(win[1], 5, 0, ">>> Welcome to OTHELLO World! (Press any key...)");
					map_go = MAIN_NOLOGIN;
				}
				wrefresh(win[1]);
				getch();
			}
			else {
				if (find == 1) {
					if (map == SIGNIN)
						map_go = MAIN_LOGIN;
					else {
						DelUser(id);
						mvwprintw(win[1], 5, 0, ">>> User %s deleted! (Press any key...)", id);
						wrefresh(win[1]);
						map_go = MAIN_NOLOGIN;
						getch();
					}
				}
				else {
					mvwprintw(win[1], 5, 0, ">>> Invalid %spassword (Press any key...)",
						map == WITHDRAWAL ? "" : "id or ");
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

	case STATISTICS:
		if (getch() != 10) return;
		Quit(win);
		map = GAME;
		Init(win);
		return;

	case GAME: {
		/* sel */
		// 0: playing game
		// 1: focus regame
		// 2: focus exit
		int cursor_prv = cursor;
		key = getch();
		if (key == KEY_LEFT) cursor += cursor % 6 == 0 ? 5 : -1;
		else if (key == KEY_RIGHT) cursor += (cursor + 1) % 6 == 0 ? -5 : 1;
		else if (key == KEY_UP) {
			if (sel == 0)
				cursor += cursor < 6 ? 30 : -6;
			else	sel += sel == 2 ? -1 : 1;
		}
		else if (key == KEY_DOWN) {
			if (sel == 0)
				cursor += cursor >= 30 ? -30 : 6;
			else	sel += sel == 1 ? 1 : -1;
		}
		else if (!sel && (key == ' ' || key == 10)) {
			int row = cursor_prv / 6;
			int col = cursor_prv % 6;
			if (!SetStone(win[0], turn, row, col)) return;

			mvwprintw(win[1], 9, 12, "%d ", count[0]);
			mvwprintw(win[1], 10, 12, "%d ", count[1]);
			if (!CheckTurn(turn == 0 ? 1 : 0)) {
				if (CheckTurn(turn)) return;
				int winner = count[0] == count[1] ? 0 : count[0] > count[1] ? 1 : 2;
				if (!winner) mvwprintw(win[0], 23, 0, ">>> Draw!!!! (Press any key...)");
				else mvwprintw(win[0], 23, 0, ">>> Player%d(%c) Win!!!! (Press any key...)", winner, winner == 1 ? 'O' : 'X');
				wrefresh(win[0]);
				sel = 2;
			}
			else {
				mvwprintw(win[1], turn == 0 ? 9 : 10, 4, turn == 0 ? "1P(O)" : "2P(X)");
				turn = turn == 0 ? 1 : 0;
				wattron(win[1], COLOR_PAIR(1));
				mvwprintw(win[1], turn == 0 ? 9 : 10, 4, turn == 0 ? "1P(O)" : "2P(X)");
				wattroff(win[1], COLOR_PAIR(1));
			}
		}
		else if (key == 'x') sel = 2;
		else if (key == 'g') sel = 0;
		else if (key == 10 && sel) {
			Quit(win);
			map = sel == 1 ? GAME : MAIN_LOGIN;
			sel = 0;
			Init(win);
			return;
		}
		int row = cursor_prv / 6;
		int col = cursor_prv % 6;
		mvwprintw(win[0], 6 + row * 2, 18 + col * 4, " %c ", stone[row][col]);
		if (sel || sel_prv) {
			if (sel_prv == 1) mvwprintw(win[1], 15, 5, "REGAME");
			else if (sel_prv == 2) mvwprintw(win[1], 17, 5, "EXIT");
			wattron(win[1], A_UNDERLINE);
			if (sel_prv == 1) mvwaddch(win[1], 15, 5, 'R');
			else if (sel_prv == 2) mvwaddch(win[1], 17, 6, 'X');
			wattroff(win[1], A_UNDERLINE);

			wattron(win[1], COLOR_PAIR(1));
			if (sel == 1) mvwprintw(win[1], 15, 5, "REGAME");
			else if (sel == 2) mvwprintw(win[1], 17, 5, "EXIT");
			wattron(win[1], A_UNDERLINE);
			if (sel == 1) mvwaddch(win[1], 15, 5, 'R');
			else if (sel == 2) mvwaddch(win[1], 17, 6, 'X');
			wattroff(win[1], A_UNDERLINE);
			wattroff(win[1], COLOR_PAIR(1));

			
			if (sel) return;
		}

		wattron(win[0], COLOR_PAIR(2));
		row = cursor / 6;
		col = cursor % 6;
		mvwprintw(win[0], 6 + row * 2, 18 + col * 4, " %c ", stone[row][col]);
		wattroff(win[0], COLOR_PAIR(2));
		return;
	}
	}
}

int main() {
	WINDOW *win[2];
	if (Setup()) {
		endwin();
		return 1;
	}
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

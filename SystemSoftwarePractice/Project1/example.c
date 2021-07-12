#include <ncurses.h>

int main(int agfc, char const *argv[]) {
	WINDOW *window1;
	WINDOW *window2;

	initscr();

	if (has_colors() == FALSE) {
		puts("Terminal does ont support colors!");
		endwin();
		return 1;
	} else {
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_WHITE);
		init_pair(2, COLOR_WHITE, COLOR_BLUE);
	}

	refresh();

	window1 = newwin(18, 80, 0, 0);
	window2 = newwin(6, 80, 18, 0);

	wbkgd(window1, COLOR_PAIR(1));
	wbkgd(window2, COLOR_PAIR(2));

	wprintw(window1, "Hello!");
	wprintw(window2, "Bonjour!");

	wrefresh(window1);
	wrefresh(window2);

	getch();
	endwin();
	return 0;
}

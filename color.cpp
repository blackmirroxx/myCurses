#include <ncurses.h>
#include <cstdlib> // for exit
#include <cstring>

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string);
auto main(int argc, char *argv[]) -> int
{	initscr();			/* Start curses mode 		*/
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	print_in_middle(stdscr, LINES / 2, 0, 0, "Viola !!! In color ...");
	attroff(COLOR_PAIR(1));
    	getch();
	endwin();
}
auto print_in_middle(WINDOW *win, int starty, int startx, int width, const char *string) -> void
{	int length, x, y;
	int temp;

	if(win == NULL) win = stdscr;
	getyx(win, y, x);
	if(startx != 0) x = startx;
	if(starty != 0) y = starty;
	if(width == 0) width = COLS; // terminal 80 -> can be different 

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

// compile : g++ -std=c++23 color.cpp -ltinfo -lncurses -o color
// execute : ./color

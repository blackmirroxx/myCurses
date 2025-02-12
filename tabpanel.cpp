#include <panel.h>
#include <string>
#include <cstring>
#include <ncurses.h>
#define NLINES 10
#define NCOLS 50

enum class ColorPair{
    de, red, green, blue, yellow, cyan, black // de for default because enum starst at zero
};

class Coordinates{
    private:
        int starty, startx;
    public:
        Coordinates(){};

        Coordinates(int starty, int startx){
            this->starty = starty;
            this->startx = startx;
        };

        ~Coordinates(){};

        auto getY(void) -> int
        {
            return starty;
        }

        auto getX() -> int
        {
            return startx;
        }

};

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

class View{
    public:
        View(){
            initializeColors();
        };

        ~View(){};

        // put all the windows
        auto init_wins(WINDOW **wins, int n) -> void
        {	int x, y, i;
            char label[80];

            y = 2;
            x = 10;
            for(i = 0; i < n; ++i)
            {	wins[i] = newwin(NLINES, NCOLS, y, x);
                sprintf(label, "Window Number %d", i + 1);
                win_show(wins[i], label, i + 1);
                y += 3;
                x += 7;
            }
        }

        /* Show the window with a border and a label */
        auto win_show(WINDOW *win, char *label, int label_color) -> void
        {	int startx, starty, height, width;

            getbegyx(win, starty, startx);
            getmaxyx(win, height, width);

            box(win, 0, 0);
            mvwaddch(win, 2, 0, ACS_LTEE);
            mvwhline(win, 2, 1, ACS_HLINE, width - 2);
            mvwaddch(win, 2, width - 1, ACS_RTEE);

            print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
        }

        auto print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) -> void
        {
            int length, x, y;
            float temp;

            if(win == NULL)
                win = stdscr;
            getyx(win, y, x);
            if(startx != 0)
                x = startx;
            if(starty != 0)
                y = starty;
            if(width == 0)
                width = 80;

            length = strlen(string);
            temp = (width - length)/ 2;
            x = startx + (int)temp;
            wattron(win, color);
            mvwprintw(win, y, x, "%s", string);
            wattroff(win, color);
            refresh();
        }

        auto initializeColors(void) -> void
        {

            init_pair((short)ColorPair::red, COLOR_RED, COLOR_BLACK);
            init_pair((short)ColorPair::green, COLOR_GREEN, COLOR_BLACK);
            init_pair((short)ColorPair::blue, COLOR_BLUE, COLOR_BLACK);
            init_pair((short)ColorPair::yellow, COLOR_YELLOW, COLOR_BLACK);
            init_pair((short)ColorPair::cyan, COLOR_CYAN, COLOR_BLACK);
            init_pair((short)ColorPair::black, COLOR_BLACK, COLOR_WHITE);
        }
};

class HandleBasePanel{
    private:
        WINDOW** my_wins;
        PANEL**  my_panels;
    public:
        HandleBasePanel(){};

        HandleBasePanel(WINDOW** my_wins, PANEL** my_panels){
            this->my_wins = my_wins;
            this->my_panels = my_panels;
        }

        ~HandleBasePanel(){};

        auto getMyWins() -> WINDOW**
        {
            return my_wins;
        }

        auto getMyPanels() -> PANEL**
        {
            return my_panels;
        }
};

class HandleTopPanel{
    private:
        PANEL* top;
        int input;
    public:
        HandleTopPanel(){};

        HandleTopPanel(PANEL* top, int input){
            this->top = top;
            this->input = input;
        };

        ~HandleTopPanel(){};

        auto getTop()-> PANEL*
        {
            return top;
        }

        auto setTop(PANEL* top) -> void
        {
            this->top = top;
        }

        auto getInput(void)-> int
        {
            return input;
        }

        auto setInput(int input) -> void
        {
            this->input = input;
        }


};

class NCursesSession{
    private:
        HandleBasePanel hbp;
        HandleTopPanel  htp;
        View v;
    public:
        NCursesSession(){};

        NCursesSession(HandleBasePanel hbp, HandleTopPanel htp){
            this->hbp = hbp;
            this->htp = htp;
            initializeColors();
        };

        ~NCursesSession(){};

        auto startSession() -> void
        {
            initscr();
            start_color();  // color for ncurses
            cbreak(); // ctr + c enabled
            noecho(); // you don't see what you type
            keypad(stdscr, TRUE);
        }

        auto initWins() -> void
        {
            v.init_wins(hbp.getMyWins(), (short)ColorPair::cyan);
        }

        auto initializeColors(void) -> void
        {

            init_pair((short)ColorPair::red, COLOR_RED, COLOR_BLACK);
            init_pair((short)ColorPair::green, COLOR_GREEN, COLOR_BLACK);
            init_pair((short)ColorPair::blue, COLOR_BLUE, COLOR_BLACK);
            init_pair((short)ColorPair::yellow, COLOR_YELLOW, COLOR_BLACK);
            init_pair((short)ColorPair::cyan, COLOR_CYAN, COLOR_BLACK);
            init_pair((short)ColorPair::black, COLOR_BLACK, COLOR_WHITE);
        }

        auto attachPanelsToWindows(void) -> void
        {
            hbp.getMyPanels()[0] = new_panel(hbp.getMyWins()[0]); 	/* Push 0, order: stdscr-0 */
            hbp.getMyPanels()[1] = new_panel(hbp.getMyWins()[1]); 	/* Push 1, order: stdscr-0-1 */
            hbp.getMyPanels()[2] = new_panel(hbp.getMyWins()[2]); 	/* Push 2, order: stdscr-0-1-2 */
            hbp.getMyPanels()[3] = new_panel(hbp.getMyWins()[3]);   /* Push 3, orden: stdscr-0-1-2-3 */
        }

        auto setUserPointerToNextPanel(void) -> void
        {
            set_panel_userptr(hbp.getMyPanels()[0], hbp.getMyPanels()[1]);
            set_panel_userptr(hbp.getMyPanels()[1], hbp.getMyPanels()[2]);
            set_panel_userptr(hbp.getMyPanels()[2], hbp.getMyPanels()[3]);
            set_panel_userptr(hbp.getMyPanels()[3], hbp.getMyPanels()[0]);
        }

        auto showToScreen(void) -> void
        {
            attron(COLOR_PAIR((short)ColorPair::cyan));  // activate visual attributes
            mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F5 to Exit)");
            attroff(COLOR_PAIR((short)ColorPair::yellow)); // deactivate visual attributes
            doupdate();  // do update memory in the background
        }

        auto tabThroughWindows(void) -> void
        {
        	htp.setTop(hbp.getMyPanels()[2]);
            int input;
            while( (input = getch()) != KEY_F(5)) // press F5 to close program
            {	htp.setInput(input);
                switch(htp.getInput() )
                {	case 9:
                        htp.setTop(  (PANEL *)panel_userptr(htp.getTop()) );
                        top_panel(htp.getTop());
                        break;
                }
                update_panels();
                doupdate();
            }
        }

        auto endSession(void) -> void
        {
            endwin();
        }

        auto update(void) -> void
        {
            update_panels();
        }
};

auto main(int argc, char** argv) -> int
{
    Coordinates c(0,0);

    // base panel
    WINDOW *my_wins[4];
	PANEL  *my_panels[4];
	HandleBasePanel hbp(my_wins, my_panels);

	// top panel
	PANEL  *top;
	int ch;
	HandleTopPanel htp(top,ch);

	/* Initialize curses */
    NCursesSession n(hbp, htp);
    n.startSession();

	/* Initialize all the colors */
	init_pair((short)ColorPair::red, COLOR_RED, COLOR_BLACK);
	init_pair((short)ColorPair::green, COLOR_GREEN, COLOR_BLACK);
	init_pair((short)ColorPair::blue, COLOR_BLUE, COLOR_BLACK);
	init_pair((short)ColorPair::yellow, COLOR_YELLOW, COLOR_BLACK);
	init_pair((short)ColorPair::cyan, COLOR_CYAN, COLOR_BLACK);
	init_pair((short)ColorPair::black, COLOR_BLACK, COLOR_WHITE);


	n.initWins();

	/* Attach a panel to each window */ 	/* Order is bottom up */
    n.attachPanelsToWindows();

	/* Set up the user pointers to the next panel */
    n.setUserPointerToNextPanel();

	/* Update the stacking order. 2nd panel will be on top */
	n.update();

	/* Show it on the screen */
    n.showToScreen();

    n.tabThroughWindows();

	n.endSession();
	return EXIT_SUCCESS;
}

/* Put all the windows */






// to compile do;
// g++ -std=c++17 tabpanel.cpp -ltinfo -lmenu -lncurses -lpanel -o tabpanel

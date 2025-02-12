
#include <menu.h>  // flag : -lmenu
#include <ncurses.h>
#include <stdlib.h> // alloc
#include <cstring> //exit
#include <string>
#include <cstdlib>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

std::string c1 = "Choice 1";
std::string c2 = "Choice 2";
std::string c3 = "Choice 3";
std::string c4 = "Choice 4";
std::string c5 = "Choice 5";

char* choices[] = {
                        (char*)c1.c_str(),
                        (char*)c2.c_str(),
                        (char*)c3.c_str(),
                        (char*)c4.c_str(),
                        (char*)c5.c_str(),
                        (char *)NULL,
                  };

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

class NCurseSession{
    private:
        int c, n_choices, i;
    public:
        NCurseSession(void){};

        ~NCurseSession(void){};

        auto startSession(void) -> int
        {
            initscr();
            start_color();
            cbreak();
            noecho();
            keypad(stdscr, TRUE);
            return EXIT_SUCCESS;
        }

        auto endSession(void) -> int
        {
            endwin();
            return EXIT_SUCCESS;
        }

};

class ItemGroup{
    private:
        ITEM** my_items;
        int c;
        int n_choices;
    public:
        ItemGroup(){};

        ~ItemGroup(){};

        auto getC(void)-> int
        {
            return c;
        }

        auto setC(int c)-> int
        {
            this->c = c;
            return EXIT_SUCCESS;
        }

        auto getN_Choices(void)-> int
        {
            return n_choices;
        }

        auto getMyItems(void) -> ITEM**
        {
            return my_items;
        }

        auto createItems(void) -> int
        {
            n_choices = ARRAY_SIZE(choices);
            my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
            int i;
            for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], choices[i]);

            return EXIT_SUCCESS;
        }

        auto deleteItems(void) -> int
        {
            int i;
            for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);

            return EXIT_SUCCESS;
        }


};

class Menu{
    private:
        MENU* my_menu;
        std::string myMenu;
        std::string exitButton;
        WINDOW* my_menu_win;
    public:
        Menu(void){
            myMenu = "My Menu";
            exitButton = "Press F5 button to exit";
        };

        ~Menu(void){};

        auto createMenu(ITEM** my_items)-> int
        {
            my_menu = new_menu(my_items);
            my_menu_win = newwin(10, 40, 4, 4);
            keypad(my_menu_win, TRUE);
            return EXIT_SUCCESS;
        }

        auto deleteMenu()-> int
        {
            unpost_menu(my_menu);
            free_menu(my_menu);
            return EXIT_SUCCESS;
        }

        auto setMenu(MENU* my_menu) -> int
        {
            this->my_menu = my_menu;
            return EXIT_SUCCESS;
        }

        auto getMenu(void) -> MENU*
        {
            return my_menu;
        }

        auto setWindow(WINDOW* my_menu) -> int
        {
            this->my_menu_win = my_menu_win;
            return EXIT_SUCCESS;
        }

        auto getWindow(void) -> WINDOW*
        {
            return my_menu_win;
        }

        auto setMainWindowWithSubWindow(void) -> int
        {
            set_menu_win(my_menu, my_menu_win);
            set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));
            return EXIT_SUCCESS;
        }

        auto setMarker(void) -> int
        {
            set_menu_mark(my_menu, " > ");
            return EXIT_SUCCESS;

        }

        auto drawTitleBox(void) -> int
        {
            box(my_menu_win, 0, 0);
            print_in_middle(my_menu_win, 1, 0, 40, (char *)myMenu.c_str(), COLOR_PAIR(1)); // <string>.c_str() converts string to const char pointer
            mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
            mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
            mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
            mvprintw(LINES - 2, 0, exitButton.c_str() );
            refresh();

            return EXIT_SUCCESS;
        }

        auto cycleMenu(ItemGroup ig) -> int
        {
            post_menu(my_menu);
            wrefresh(my_menu_win);
            int ch = ig.getC();
            while((ch = wgetch(my_menu_win)) != KEY_F(5))
            {
                ig.setC(ch);
                switch(ig.getC()){
                    case KEY_DOWN:
                        menu_driver(my_menu, REQ_DOWN_ITEM);
                        break;

                    case KEY_UP:
                        menu_driver(my_menu, REQ_UP_ITEM);
                        break;

                }
                wrefresh(my_menu_win);
            }
            return EXIT_SUCCESS;
        }
};

auto main(void) -> int
{
	// MENU *my_menu;
	// std::string myMenue = "My Meue";
	// std::string exitButton = "Press F5 button to exit";
    // WINDOW *my_menu_win;

	/* Initialize curses */
    NCurseSession n;
    n.startSession();

	init_pair(1, COLOR_RED, COLOR_BLACK);

	/* Create items */
    ItemGroup ig;
    ig.createItems();

	/* Crate menu */
	// my_menu = new_menu((ITEM **)ig.getMyItems());
	Menu m;
	m.createMenu((ITEM**)ig.getMyItems() );


	/* Set main window and sub window */
    m.setMainWindowWithSubWindow();

	/* Set menu mark to the string " * " */
    m.setMarker();

	/* Print a border around the main window and print a title */
    m.drawTitleBox();

	/* Post the menu */
    m.cycleMenu(ig);

	/* Unpost and free all the memory taken up */
    m.deleteMenu();

    // items
    ig.deleteItems();

	n.endSession();

	return EXIT_SUCCESS;
}

auto print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) -> void
{	int length, x, y;
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


// g++ -std=c++17 menuWindow.cpp -ltinfo -lmenu -lncurses -o menuWindow

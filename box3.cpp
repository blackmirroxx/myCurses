#include <panel.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

class NCurseSession{
    private:
        std::string s;
    public:
        // constructor
        NCurseSession(){};

        // destructor
        ~NCurseSession(){};

        auto startSession() -> int
        {
            initscr();
            // raw(); // no control c
            cbreak(); // with control c which is the default
            noecho(); // you don't see what you type
            return EXIT_SUCCESS;
        }

        auto endSession() -> int
        {
            endwin();
            return EXIT_SUCCESS;
        }

        auto refreshSession() -> int
        {
            refresh();
            return EXIT_SUCCESS;
        }

        auto getUserInput() -> std::string
        {
            s = getch();
            return s;
        }

};

class MyBox{
    private:
        int height, width, start_x, start_y;
        WINDOW* win;
    public:
        // constructor
        MyBox(){
            height = 10;
            width = 20;
            start_y = 3;
            start_x = 10;
            win = newwin(height, width, start_y, start_x);
            refresh();
            // box(win, 0, 0); // window, borderRightLeft, borderTopBottom
            // alternative box
            int left, right, top, bottom, tlc, trc, blc, brc;
            left = right = ACS_VLINE;
            top = bottom = ACS_HLINE;
            tlc = ACS_ULCORNER;
            trc = ACS_PLUS; // top right corner -> +
            blc = ACS_LLCORNER;
            brc = ACS_LRCORNER;
            wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
            mvwprintw(win,1,2, "This is my box");
            wrefresh(win);
        };

        MyBox(std::string s){
            height = 20;
            width = 40;
            start_y = 3;
            start_x = 10;
            win = newwin(height, width, start_y, start_x);
            refresh();
            box(win, 0, 0);
            mvwprintw(win,1,2, s.c_str()); // convert string to const char pointer
            wrefresh(win);
        };

        MyBox(int height, int width, int start_y, int start_x, std::string s){
            this->height = height;
            this->width = width;
            this->start_y = start_y;
            this->start_x = start_x;
            win = newwin(height, width, start_y, start_x);
            refresh();
            box(win, 0, 0);
            mvwprintw(win, 1, 2, s.c_str());  // convert string to const char pointer (again)
            wrefresh(win);
        };

        // destructor
        ~MyBox(){};
};

auto main(int argc, char** argv) -> int
{
    // create session object
    NCurseSession n;

    // ncurses starts
    n.startSession();

    // refresh
    n.refreshSession();

    // create a box
    // MyBox  b_acs;
    MyBox b(argv[1]);
    // MyBox b(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), argv[5]);

    // get user input
    std::string s = n.getUserInput();

    n.endSession();
    // ncurses ends

    return EXIT_SUCCESS;
}

// to compile do;
// g++ -std=c++23 box3.cpp -ltinfo -lmenu -lncurses -lpanel -o box3

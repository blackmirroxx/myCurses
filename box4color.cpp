#include <panel.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <algorithm>
#include <vector> // use vector to copy arguments


// for color pairs -> enum class for better encapsulation e.g. Colors::white
enum class Colors{
    white, yellow, red, blue, green, black
};

enum class ArgumentsForBox{
    boxStandard = 1,
    boxWithText = 2,
    boxWithFieldCoordinatesAndText = 6
};

class Parameter{
    private:
        int psize;
        std::vector<std::string> arguments;
    public:
        Parameter(){};

        Parameter(int psize){
            this->psize = psize;
        };

        ~Parameter(){};

        auto getSize(void) -> int
        {
            return psize;
        }

        auto setArguments(std::vector<std::string> args) -> void
        {
            arguments = args;
        }

        auto getArguments(int i) -> std::string
        {
            if(i>=psize)
            {
                i = 0; // check overflow
            }
            return arguments[i];
        }

};

class Field {
    private:
        int width, height;
    public:
        Field(int width, int height){
            this->width = width;
            this->height = height;
        };

        ~Field(){};

        auto setWidth(int width) -> int
        {
            this->width = width;
            return EXIT_SUCCESS;
        }

        auto getWidth(void) -> int
        {
            return this->width;
        }

        auto setHeight(int height) -> int
        {
            this->height = height;
            return EXIT_SUCCESS;
        }

        auto getHeight(void) -> int
        {
            return this->height;
        }
};

class Coordinate{
    private:
        int start_y, start_x;
    public:
        Coordinate(int start_y, int start_x){
            this->start_y = start_y;
            this->start_x = start_x;
        };

        ~Coordinate(){};

        auto setStartY(int start_y) -> int
        {
            this->start_y = start_y;
            return EXIT_SUCCESS;
        }

        auto getStartY(void) -> int
        {
            return this->start_y;
        }

        auto setStartX(int start_x) -> int
        {
            this->start_x = start_x;
            return EXIT_SUCCESS;
        }

        auto getStartX(void) -> int
        {
            return this->start_x;
        }
};


class NCurseSession{
    private:
        std::string s;

    public:
        // constructor
        NCurseSession(){

        };

        // destructor
        ~NCurseSession(){};

        auto startSession() -> int
        {
            initscr();
            cbreak(); // with control c which is the default
            noecho(); // you don't see what you type
            start_color(); // enable color for ncurses
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

        auto isStandardBox(int paramCount) -> bool
        {
            bool isStandard = false;
            if(paramCount == (int)ArgumentsForBox::boxStandard){
                isStandard = true;
            }
            return isStandard;
        }

        auto isBoxWithText(int paramCount) -> bool
        {
            bool isWithText = false;
            if(paramCount == (int)ArgumentsForBox::boxWithText){
                isWithText = true;
            }
            return isWithText;
        }

        auto isBoxWithFieldCoordinatesAndText(int paramCount) -> bool
        {
            bool isWithFieldCoordinates = false;
            if(paramCount == (int)ArgumentsForBox::boxWithFieldCoordinatesAndText){
                isWithFieldCoordinates = true;
            }
            return isWithFieldCoordinates;
        }
};

class MyBox{
    protected:
        int height, width, start_x, start_y;
        int left, right, top, bottom, tlc, trc, blc, brc;
        WINDOW* win;
    public:
        // constructor
        MyBox(){
            height = 10;
            width = 30;
            start_y = 3;
            start_x = 10;
            win = newwin(height, width, start_y, start_x);
            refresh();
            // box -> window, borderRightLeft, borderTopBottom
            // alternative box
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

        MyBox(Field f, Coordinate c, std::string s){
            this->height = f.getHeight();
            this->width = f.getWidth();
            this->start_y = c.getStartY();
            this->start_x = c.getStartX();
            win = newwin(this->height, this->width, this->start_y, this->start_x);
            refresh();
            box(win, 0, 0);
            mvwprintw(win, 1, 2, s.c_str());  // convert string to const char pointer (again)
            wrefresh(win);
        };

        // destructor
        ~MyBox(){};
};

class MyColoredBox: public MyBox{
    private:
        short frameColor = (short)Colors::white;
        short textColor = (short)Colors::white;
        std::string s = "This is my colored box";
    public:
        // constructor
        MyColoredBox(): MyBox(){
            // reset all colors
            clear();
            initializeColor();
            // draw frame based on inherrited box
            // attron(A_..) standard, reverse and so on
            // safeguard !has_colors()
            wattron(win,COLOR_PAIR(Colors::yellow)); // attron not supported inside a window
            wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
            wattroff(win,COLOR_PAIR(Colors::white)); // attron not supported inside a window
            // draw text based on inherrted box
            // attroff(COLOR_PAIR(white));
            if(!has_colors()){this->s = "terminal has no colors";}
            wattron(win, COLOR_PAIR(Colors::red));
            mvwprintw(win,1,2, this->s.c_str());
            wattroff(win, COLOR_PAIR(Colors::white));
            refresh();
            wrefresh(win);
            doupdate();
        };

        // 2nd constructor
        MyColoredBox(std::string s):MyBox(s){
            this->s = s;
            clear();
            initializeColor();
            // draw frame
            wattron(win, COLOR_PAIR(Colors::green));
            box(win,0,0);
            wattroff(win, COLOR_PAIR(Colors::white));
            if(!has_colors()){this->s = "terminal has no colors";}
            wattron(win, COLOR_PAIR(Colors::yellow));
            mvwprintw(win, 1, 2, this->s.c_str());
            wattroff(win, COLOR_PAIR(Colors::white));
            refresh();
            wrefresh(win);
            doupdate();
        };

        // 3d constructor
        MyColoredBox(Field f, Coordinate c, std::string s):MyBox(f, c, s){
            this->s = s;
            clear();
            initializeColor();
            // draw frame
            wattron(win, COLOR_PAIR(Colors::blue));
            box(win,0,0);
            wattroff(win,COLOR_PAIR(Colors::white));
            if(!has_colors()){this->s="terminal doesn't support colors";}
            wattron(win, COLOR_PAIR(Colors::yellow));
            mvwprintw(win, 1, 2, this->s.c_str()); // convert string to const char pointer with s.c_str()
            wattroff(win, COLOR_PAIR(Colors::white));
            refresh();
            wrefresh(win);
            doupdate();
        };

        ~MyColoredBox(){};

        // color and must be done within the same class
        auto initializeColor() -> int
        {
            init_pair((short)Colors::white, COLOR_WHITE, COLOR_BLACK);
            init_pair((short)Colors::yellow, COLOR_YELLOW, COLOR_BLACK);
            init_pair((short)Colors::red, COLOR_RED, COLOR_BLACK);
            init_pair((short)Colors::blue, COLOR_BLUE, COLOR_BLACK);
            init_pair((short)Colors::green, COLOR_GREEN, COLOR_BLACK);
            init_pair((short)Colors::black, COLOR_BLACK, COLOR_WHITE);
            return EXIT_SUCCESS;
        }
};

class View{
    private:
        Parameter p;
        NCurseSession n;
    public:
        View(){};

        View(Parameter p, NCurseSession n){
            this->p = p;
            this->n = n;
        };

        ~View(){};

        auto drawBox() -> void
        {
            if(n.isStandardBox( p.getSize() )){
                MyColoredBox mc;
            }

            if(n.isBoxWithText( p.getSize() )){
                std::string boxMessage = p.getArguments(1);
                MyColoredBox mc(boxMessage);
            }

            if(n.isBoxWithFieldCoordinatesAndText(p.getSize() )){
                Field f(std::stoi(p.getArguments(1)),std::stoi(p.getArguments(2)));
                Coordinate c(std::stoi(p.getArguments(3)),std::stoi(p.getArguments(4)));
                std::string boxMessage = p.getArguments(5);
                MyColoredBox mc(f, c, boxMessage);
            }

        }


};


auto main(int argc, char** argv) -> int
{
    // copy parameters from command line
    std::vector <std::string> args(argc);
    std::transform(argv, argv+argc, args.begin(), [&](char* arg){return std::string(arg); } );
    Parameter p(argc);
    p.setArguments(args);

    // create session object
    NCurseSession n;

    // ncurses starts
    n.startSession();

    // refresh
    n.refreshSession();

    // create a box from the command lines
    View v(p,n);
    v.drawBox();

    // get user input
    std::string s = n.getUserInput();

    n.endSession();
    // ncurses ends

    return EXIT_SUCCESS;
}

// to compile do;
// g++ -std=c++23 box4colored.cpp -ltinfo -lmenu -lncurses -lpanel -o box4colored
// execute -> $> ./box4color 30 10 3 6 "rc3 rulez"

#include <panel.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ncurses.h>
// video tutorial

auto main(int argc, char** argv) -> int
{
    // ncurses starts
    initscr();

    // pretend that the entire screen is our window
    if(argc>=2){
        move(std::stoi(argv[1]), std::stoi(argv[2]));
    }
    printw("You should try zeronet");

    // refreshes the screen
    refresh();

    // user input
    getch();

    endwin();
    // ncurses ends

    return EXIT_SUCCESS;
}


// to compile do;
// g++ -std=c++17 tabpanel.cpp -ltinfo -lmenu -lncurses -lpanel -o tabpanel

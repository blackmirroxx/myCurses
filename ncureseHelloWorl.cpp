#include <ncurses.h>

int main()
{
   initscr();                 /* Start curses mode     */
   clear();
   printw("Hello World !!!"); /* Print Hello World    */
   refresh();                 /* Print it on to the real screen */
   getch();                   /* Wait for user input */
   endwin();                  /* End curses mode    */
   return 0;
}

// to compile execute 
// g++ -std=c++17 ncureseHelloWorl.cpp -ltinfo -lncurses -o HelloWolrd 

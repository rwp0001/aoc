#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

using namespace std;

#include <signal.h>
void* resizeHandler(int);

int main()
{
    // init screen and sets up screen
    initscr();

    // print to screen
    printw("Hello World");

    // refreshes the screen
    refresh();

    // pause the screen output
    getch();

    // deallocates memory and ends ncurses
    endwin();

}


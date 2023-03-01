#include <ncurses.h>
using namespace std;

int main (int argc, char ** argv)
{
    initscr();

    // moving cursor, x = 20, y = 10
    move(10, 20);

    printw("I am here...");

    move(21, 10);
    printw("Now i am here");

    refresh();
    getch();
    endwin();
    return 0;
}
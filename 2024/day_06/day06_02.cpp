#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <list>
#include <cstdint>
#include <cstring>


/*
--- Day 6: Guard Gallivant ---
The Historians use their fancy device again, 
this time to whisk you all away to the North Pole prototype suit manufacturing lab... in the year 1518! 
It turns out that having direct access to history is very convenient for a group of historians.

You still have to be careful of time paradoxes, 
and so it will be important to avoid anyone from 1518 while The Historians search for the Chief. 
Unfortunately, a single guard is patrolling this part of the lab.

Maybe you can work out where the guard will go ahead of time so that The Historians can search safely?

You start by making a map (your puzzle input) of the situation. For example:
....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...

The map shows the current position of the guard with ^ (to indicate the guard is currently facing up from the perspective of the map). 
Any obstructions - crates, desks, alchemical reactors, etc. - are shown as #.

Lab guards in 1518 follow a very strict patrol protocol which involves repeatedly following these steps:
If there is something directly in front of you, turn right 90 degrees.
Otherwise, take a step forward.

Following the above protocol, 
the guard moves up several times until she reaches an obstacle (in this case, a pile of failed suit prototypes):
....#.....
....^....#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#...

Because there is now an obstacle in front of the guard, 
she turns right before continuing straight in her new facing direction:

....#.....
........>#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#...

Reaching another obstacle (a spool of several very long polymers), 
she turns right again and continues downward:

....#.....
.........#
..........
..#.......
.......#..
..........
.#......v.
........#.
#.........
......#...

This process continues for a while, 
but the guard eventually leaves the mapped area (after walking past a tank of universal solvent):

....#.....
.........#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#v..

By predicting the guard's route, you can determine which specific positions in the lab will be in the patrol path. 
Including the guard's starting position, 
the positions visited by the guard before leaving the area are marked with an X:
....#.....
....XXXXX#
....X...X.
..#.X...X.
..XXXXX#X.
..X.X.X.X.
.#XXXXXXX.
.XXXXXXX#.
#XXXXXXX..
......#X..

In this example, the guard will visit 41 distinct positions on your map.

Predict the path of the guard. 
How many distinct positions will the guard visit before leaving the mapped area?

To begin, get your puzzle input.
*/

//#define SAMPLE 1
#ifdef SAMPLE
    #define FILENAME "sample.txt"
    #define WIDTH 10
    #define HEIGHT 10
#else
    #define FILENAME "input.txt"
    #define WIDTH 130
    #define HEIGHT 130
#endif

char Backup[HEIGHT][WIDTH];
char Board[HEIGHT][WIDTH];


struct Point
{
    int X;
    int Y;
    int dir = 0; // 0=N, 1=E, 2=S, 3=W
} Guard;

Point StartPos;

std::list<Point> Turns;

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                int pos = 0;
                for( char c : line ) {
                    switch (c){
                        case '^':
                            StartPos.Y = pos;
                            StartPos.X = Count;
                            Board[Count][pos] = 'X';
                            break;

                        case '#':
                            Board[Count][pos] = c;
                            break;

                        default:
                            Board[Count][pos] = '.';
                            break;
                    }
                    pos++;
                }
                Count++;
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

bool OnBoard(){
    if(Guard.X<0) return false; 
    if(Guard.X>WIDTH-1) return false; 
    if(Guard.Y<0) return false; 
    if(Guard.Y>HEIGHT-1) return false; 
    return true;
}

void PrintBoard(){
    for(int x = 0; x< HEIGHT; x++) {
        for(int y = 0; y< HEIGHT; y++) {
            switch (Board[x][y])
            {
            case '#':
                std::cout << "\x1B[31m";
                break;
            case 'X':
                std::cout << "\x1B[34m";
                break;            
            default:
                std::cout << "\033[0m";
                break;
            }

            if(Guard.X == x & Guard.Y == y) {
                std::cout << 'G';
            } else {
                std::cout << Board[x][y];
            }
            
        }
        std::cout << "\033[0m" << std::endl;
    }
    for( Point p : Turns ) std::cout << "P: " << p.X << "," << p.Y << " - " << p.dir << "; ";
    std::cout << "\033[0m" << std::endl;
}

bool IsStuck(Point p){
    for( Point p2: Turns ) if( p2.X == p.X & p2.Y==p.Y & p2.dir == p.dir ) return true;
    return false;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );
    std::memcpy( &Backup, *Board, sizeof(Board) );
    int Count = 0;

    for(int x = 0; x< HEIGHT; x++) {
        for(int y = 0; y< HEIGHT; y++) {
            std::memcpy( &Board, *Backup, sizeof(Board) );
            if(Board[x][y] == '#') continue;
            Guard = StartPos;
            if(Guard.X==x & Guard.Y==y) continue;
            bool stuck = false;
            Board[x][y] = '#';
            Turns.clear();
            std::cout << "X: " << x << " Y: " << y << std::endl;

            while ( OnBoard() & !stuck )
            {
                Point t = Guard;
                Board[t.X][t.Y] = 'X';
                char c = 0;

                switch (t.dir){
                    case 0:
                        t.X -= 1;
                        break;
                    
                    case 1:
                        t.Y += 1;
                        break;

                    case 2:
                        t.X += 1;
                        break;

                    case 3:
                        t.Y -= 1;
                        break;

                    default:
                        break;
                }

                if( t.X > -1 & t.X < HEIGHT & t.Y > -1 & t.Y < WIDTH ) c = Board[t.X][t.Y];

                if( c == '#' ) {
                    t.dir++;
                    if( t.dir > 3 ) t.dir = 0;
                    stuck = IsStuck(t);
                    Turns.push_front(t);
                    if(stuck) {
                        Count++;
                        #ifdef SAMPLE
                        PrintBoard();
                        #endif
                    }                    
                }

                //if( Turns.size() > 4 ) Turns.pop_back();
                
                if( c != '#' ) Guard = t;
                
                Guard.dir = t.dir;
            }
        

        }
    }


    std::cout << "Count: " << Count << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    #ifdef SAMPLE
    if( Count != 6 ) throw new std::exception();
    #endif
    return 0;
}

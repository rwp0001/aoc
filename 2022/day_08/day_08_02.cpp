/*
--- Day 8: Treetop Tree House ---

The expedition comes across a peculiar patch of tall trees all planted carefully in a grid. 
The Elves explain that a previous expedition planted these trees as a reforestation effort. 
Now, they're curious if this would be a good location for a tree house.

First, determine whether there is enough tree cover here to keep a tree house hidden. 
To do this, you need to count the number of trees that are visible from outside the grid when looking directly along a row or column.

The Elves have already launched a quadcopter to generate a map with the height of each tree (your puzzle input). 

For example:

30373
25512
65332
33549
35390

Each tree is represented as a single digit whose value is its height, where 0 is the shortest and 9 is the tallest.

A tree is visible if all of the other trees between it and an edge of the grid are shorter than it. 
Only consider trees in the same row or column; that is, only look up, down, left, or right from any given tree.

All of the trees around the edge of the grid are visible - since they are already on the edge, there are no trees to block the view. 

In this example, that only leaves the interior nine trees to consider:

The top-left 5 is visible from the left and top. (It isn't visible from the right or bottom since other trees of height 5 are in the way.)
The top-middle 5 is visible from the top and right.
The top-right 1 is not visible from any direction; for it to be visible, there would need to only be trees of height 0 between it and an edge.
The left-middle 5 is visible, but only from the right.
The center 3 is not visible from any direction; for it to be visible, there would need to be only trees of at most height 2 between it and an edge.
The right-middle 3 is visible from the right.
In the bottom row, the middle 5 is visible, but the 3 and 4 are not.

With 16 trees visible on the edge and another 5 visible in the interior, a total of 21 trees are visible in this arrangement.

Consider your map; how many trees are visible from outside the grid?
*/

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <chrono>

//#define SAMPLE 1

#ifdef SAMPLE
#define FILENAME "sample.txt"
#define MAX_X 5
#define MAX_Y 5
#else
#define FILENAME "input.txt"
#define MAX_X 99
#define MAX_Y 99
#endif

int Data[MAX_X][MAX_Y];
int Vis[MAX_X][MAX_Y][10];


void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile;
    myfile.open(filename);
    int Row = 0;

    try {
        if (myfile.is_open()){
            while (getline(myfile, line)) {
                for( int Col = 0; Col < MAX_Y; Col++ ) Data[ Row ][ Col ] = line.c_str()[ Col ] - '0';
                Row++;
            }
        } else throw(std::exception());
        myfile.close();
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
}

void test1(int x, int y){
    for( int h = 0; h < 10; h++ ) if( Data[x][y] >= h ) {
        Vis[x][y][h] = ( x * MAX_X ) + y + 1;
    } else {
        Vis[x][y][h] = -1;
    } 
}

void PrintLayers(){
    for( int d = 0; d < 10; d++ ) {
        for( int x = 0; x < MAX_X; x++ ) {
            for( int y = 0; y < MAX_Y; y++ ) {
                std::cout << std::fixed;
                std::cout << std::setw(4);
                if( Vis[x][y][d] != -1 ){
                    std::cout << Vis[x][y][d];
                } else {
                    std::cout << " ";
                }
                
            }
            //if( d != 9 ) std::cout << "  | ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintData(){
    for( int x = 0; x < MAX_X; x++ ) {
        for( int y = 0; y < MAX_Y; y++ ) {
            std::cout << std::fixed;
            std::cout << std::setw(2);
            std::cout << Data[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Print(){
    int c = -1;

    // north
    for( int h = 9; h > -1; h-- ) { 
        std::cout << "Layer ";
        std::cout << std::fixed;
        std::cout << std::setw(2);
        std::cout << h;
        std::cout << " - ";

        for( int y = 0; y < MAX_Y; y++ ) {
            c = -1;
            for( int x = 0; x < MAX_X; x++ ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    break;
                }
            }
            std::cout << std::fixed;
            std::cout << std::setw(5);
            if( c != -1 ) std::cout << c;
            if( c == -1 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // south
    for( int h = 9; h > -1; h-- ) { 
        std::cout << "Layer ";
        std::cout << std::fixed;
        std::cout << std::setw(2);
        std::cout << h;
        std::cout << " - ";

        for( int y = MAX_Y - 1; y > -1; y-- ) {
            c = 32;
            for( int x = MAX_Y - 1; x > -1; x-- ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    break;
                }
            }
            std::cout << std::fixed;
            std::cout << std::setw(5);
            if( c != -1 ) std::cout << c;
            if( c == -1 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // west
    for( int h = 9; h > -1; h-- ) { // Layers
        std::cout << "Layer ";
        std::cout << std::fixed;
        std::cout << std::setw(2);
        std::cout << h;
        std::cout << " - ";

        for( int x = 0; x < MAX_X; x++ ) {
            c = 32;
            for( int y = 0; y < MAX_Y; y++ ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    break;
                }
            }
            std::cout << std::fixed;
            std::cout << std::setw(5);
            if( c != -1 ) std::cout << c;
            if( c == -1 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // east
    for( int h = 9; h > -1; h-- ) { 
        std::cout << "Layer ";
        std::cout << std::fixed;
        std::cout << std::setw(2);
        std::cout << h;
        std::cout << " - ";

        for( int x = MAX_X - 1; x > -1; x-- ) {
            c = 32;
            for( int y = MAX_Y - 1; y > -1; y-- ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    break;
                }
            }
            std::cout << std::fixed;
            std::cout << std::setw(5);
            if( c != -1 ) std::cout << c;
            if( c == -1 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



void PrintScore(){
    int Score = 0;
    for( int x = 0; x < MAX_X; x++ ) for( int y = 0; y < MAX_Y; y++ ) if ( Vis[x][y] != 0 ) Score += 1;
    std::cout << "Score: " << Score << std::endl;
    std::cout << std::endl;
}



void Calc(){
    int c = -1;
    std::list<int> Trees;

    for( int x = 0; x < MAX_X; x++ ) for( int y = 0; y < MAX_Y; y++ )  test1(x,y);

    for( int h = 9; h > -1; h-- ) { 
        // north
        for( int y = 0; y < MAX_Y; y++ ) {
            c = -1;
            for( int x = 0; x < MAX_X; x++ ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    Trees.push_front(c);
                    break;
                }
            }
        }

        // south
        for( int y = MAX_Y - 1; y > -1; y-- ) {
            c = -1;
            for( int x = MAX_Y - 1; x > -1; x-- ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    Trees.push_front(c);
                    break;
                }
            }
        }

        // west
        for( int x = 0; x < MAX_X; x++ ) {
            c = -1;
            for( int y = 0; y < MAX_Y; y++ ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    Trees.push_front(c);
                    break;
                }
            }
        }

        // east
        for( int x = MAX_X - 1; x > -1; x-- ) {
            c = -1;
            for( int y = MAX_Y - 1; y > -1; y-- ) {
                if( Vis[x][y][h] != -1 ) {
                    c = Vis[x][y][h];
                    Trees.push_front(c);
                    break;
                }
            }
        }
    }

    Trees.sort();
    Trees.unique();

    int Count = 0;
    std::cout << "Trees: ";
    for( int c : Trees ) if( c != -1 ) {
        std::cout << std::fixed;
        std::cout << std::setw(3);
        std::cout << c;
        Count++;
    }
    std::cout << std::endl;
    std::cout << "Count: " << Count << std::endl;

}



int main( int argc, char *argv[] ){
    auto start = std::chrono::high_resolution_clock::now();
    ReadFile( FILENAME );
    //PrintData();
    Calc();
    //PrintLayers();
    
    
    
    //Print();


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by program: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
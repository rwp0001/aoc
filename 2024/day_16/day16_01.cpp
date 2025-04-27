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
#include <iomanip>
#include <limits>

/*
--- Day 16: Reindeer Maze ---
It's time again for the Reindeer Olympics! 
This year, the big event is the Reindeer Maze, where the Reindeer compete for the lowest score.

You and The Historians arrive to search for the Chief right as the event is about to start. 
It wouldn't hurt to watch a little, right?

The Reindeer start on the Start Tile (marked S) facing East and need to reach the End Tile (marked E). 
They can move forward one tile at a time (increasing their score by 1 point), but never into a wall (#). 
They can also rotate clockwise or counterclockwise 90 degrees at a time (increasing their score by 1000 points).

To figure out the best place to sit, you start by grabbing a map (your puzzle input) from a nearby kiosk. 

For example:
###############
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############

There are many paths through this maze, but taking any of the best paths would incur a score of only 7036. 
This can be achieved by taking a total of 36 steps forward and turning 90 degrees a total of 7 times:


###############
#.......#....E#
#.#.###.#.###^#
#.....#.#...#^#
#.###.#####.#^#
#.#.#.......#^#
#.#.#####.###^#
#..>>>>>>>>v#^#
###^#.#####v#^#
#>>^#.....#v#^#
#^#.#.###.#v#^#
#^....#...#v#^#
#^###.#.#.#v#^#
#S..#.....#>>^#
###############

Here's a second example:
#################
#...#...#...#..E#
#.#.#.#.#.#.#.#.#
#.#.#.#...#...#.#
#.#.#.#.###.#.#.#
#...#.#.#.....#.#
#.#.#.#.#.#####.#
#.#...#.#.#.....#
#.#.#####.#.###.#
#.#.#.......#...#
#.#.###.#####.###
#.#.#...#.....#.#
#.#.#.#####.###.#
#.#.#.........#.#
#.#.#.#########.#
#S#.............#
#################

In this maze, the best paths cost 11048 points; following one such path would look like this:
#################
#...#...#...#..E#
#.#.#.#.#.#.#.#^#
#.#.#.#...#...#^#
#.#.#.#.###.#.#^#
#>>v#.#.#.....#^#
#^#v#.#.#.#####^#
#^#v..#.#.#>>>>^#
#^#v#####.#^###.#
#^#v#..>>>>^#...#
#^#v###^#####.###
#^#v#>>^#.....#.#
#^#v#^#####.###.#
#^#v#^........#.#
#^#v#^#########.#
#S#>>^..........#
#################

Note that the path shown above includes one 90 degree turn as the very first move, 
rotating the Reindeer from facing East to facing North.

Analyze your map carefully. What is the lowest score a Reindeer could possibly get?
*/

#define SAMPLE 1
#ifdef SAMPLE
    #define FILENAME "sample2.txt"
    #define TEST_ANSWER 11048
#else
    #define FILENAME "input.txt"
#endif

struct point {
    int X;
    int Y;
    int Dir;
    int Depth;
    bool Done;
};


std::vector<std::string> DataSet;
int BestFound = INT_MAX;
std::list<point> Turns;

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    
    try
    {
        myfile.open( filename );
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) DataSet.push_back(line);
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}


void PrintBoard(point P){
    for(int x = 0; x< DataSet.size(); x++) {
        for(int y = 0; y< DataSet[0].size(); y++) {
            switch (DataSet[x][y])
            {
            case '#':
                std::cout << "\x1B[31m";
                break;
            // case 'X':
            //     std::cout << "\x1B[34m";
            //     break;            
            default:
                std::cout << "\033[0m";
                break;
            }

            if(P.X == x & P.Y == y) {
                switch (P.Dir)
                {
                case 0:
                    std::cout << '>';
                    break;

                case 1:
                    std::cout << 'v';
                    break;

                case 2:
                    std::cout << '<';
                    break;

                case 3:
                    std::cout << '^';
                    break;
                
                default:
                    std::cout << 'X';
                    break;
                }

            } else {
                std::cout << DataSet[x][y];
            }
            
        }
        std::cout << "\033[0m" << std::endl;
    }
    std::cout << "\033[0m" << std::endl;
}

bool Exist(point P){
    for( point t : Turns ) if( P.X == t.X & P.Y == t.Y &  P.Dir == t.Dir ) return true;
    return false;
}

bool AllDone(){
    for( point t : Turns ) if( !t.Done ) return false;
    return true;
}

int search(point &P){
    //std::cout << "Search:   " << std::setw(3) << P.X << "," << std::setw(3) << P.Y << " - " << P.Dir << " D: " << P.Depth << std::endl;
    if( P.Depth > BestFound ) {
        //std::cout << "Loser:    " << std::setw(3) << P.X << "," << std::setw(3) << P.Y << std::endl;
        return INT_MAX;  // Not better.
    }

    int nx[3] = {P.X,P.X,P.X};
    int ny[3] = {P.Y,P.Y,P.Y};
    char c[3];

    switch (P.Dir){
        case 0: // E
            ny[0]++;
            nx[1]--;
            nx[2]++;
            break;

        case 1: // S
            nx[0]++;
            ny[1]++;
            ny[2]--;
            break;

        case 2: // W
            ny[0]--;
            nx[1]++;
            nx[2]--;
            break;

        case 3: // N
            nx[0]--;
            ny[1]--;
            ny[2]++;
            break;

    default:
        break;
    }
    
    c[0] = DataSet[nx[0]][ny[0]];
    c[1] = DataSet[nx[1]][ny[1]];
    c[2] = DataSet[nx[2]][ny[2]];

    if( c[0] == '#' & c[1] == '#' & c[2] == '#' ) { // Dead End
        //std::cout << "Dead End: " << std::setw(3) << P.X << "," << std::setw(3) << P.Y << std::endl;
        DataSet[P.X][P.Y] = 'd';
        P.Done == true;
        return INT_MAX; 
    }

    if( c[0] == 'E' || c[1] == 'E' || c[2] == 'E' ) { // Found
        if(P.Depth < BestFound) BestFound = P.Depth;
        std::cout << "Found:    " << std::setw(3) << P.X << "," << std::setw(3) << P.Y << " - " << P.Dir << " D: " << P.Depth << std::endl;
        P.Done = true;
        return P.Depth + 1;
    }

    int nd = P.Dir;

    if( c[0] == '.' ) {
        point NP;
        NP.X = nx[0];
        NP.Y = ny[0];
        NP.Dir = nd;
        NP.Depth = P.Depth + 1;
        search(NP);
        //if( !Exist(NP) ) 
        //Turns.push_back(NP);
        DataSet[P.X][P.Y] = ' ';
    }



    if( c[1] == '.' ) {
        nd = P.Dir;
        nd--;
        if(nd < 0) nd = 3;
        point NP;
        NP.X = nx[1];
        NP.Y = ny[1];
        NP.Dir = nd;
        NP.Depth = P.Depth + 1001;
        if( !Exist(NP) ) {
            std::cout << "Turn:     " << std::setw(3) << NP.X << "," << std::setw(3) << NP.Y << " - " << NP.Dir << " D: " << NP.Depth << std::endl;
            DataSet[P.X][P.Y] = 't';
            Turns.push_back(NP);
        }
    }



    if( c[2] == '.' ) {
        nd = P.Dir;
        nd++;
        if(nd > 3) nd = 0;
        point NP;
        NP.X = nx[2];
        NP.Y = ny[2];
        NP.Dir = nd;
        NP.Depth = P.Depth + 1001;
        if( !Exist(NP) ) {
            std::cout << "Turn:     " << std::setw(3) << NP.X << "," << std::setw(3) << NP.Y << " - " << NP.Dir << " D: " << NP.Depth << std::endl;
            Turns.push_back(NP);
        }
    }

    P.Done = true;
    return P.Depth;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );
    int Count = 0;

    for(int x = 1; x < DataSet.size(); x++) for(int y = 1; y < DataSet[x].size(); y++) {
        if(DataSet[x][y] == 'S' ) {
            point P;
            P.X = x;
            P.Y = y;
            P.Dir = 0;
            P.Depth = 1;
            Turns.push_back(P);
            break;
        }
    }

    while( Turns.size() != 0 ){
        auto P = Turns.begin();
        //std::cout << "Turns: " << Turns.size() << std::endl;
        int d = search(*P);
        //std::cout << "Score: " << d << std::endl;
        PrintBoard(*P);
        Turns.pop_front();
        //std::cout << "Press Enter to Continue";
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    std::cout << "Count: " << BestFound << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

#ifdef SAMPLE
    if( BestFound != TEST_ANSWER ) throw new std::exception();
#endif
    return 0;
}

// 98440 is too high
// 98420 is too high


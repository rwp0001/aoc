/*

--- Day 14: Restroom Redoubt ---
One of The Historians needs to use the bathroom; fortunately, you know there's a bathroom near an unvisited location on their list, and so you're all quickly teleported directly to the lobby of Easter Bunny Headquarters.

Unfortunately, EBHQ seems to have "improved" bathroom security again after your last visit. The area outside the bathroom is swarming with robots!

To get The Historian safely to the bathroom, you'll need a way to predict where the robots will be in the future. Fortunately, they all seem to be moving on the tile floor in predictable straight lines.

You make a list (your puzzle input) of all of the robots' current positions (p) and velocities (v), one robot per line. For example:

p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3
Each robot's position is given as p=x,y where x represents the number of tiles the robot is from the left wall and y represents the number of tiles from the top wall (when viewed from above). So, a position of p=0,0 means the robot is all the way in the top-left corner.

Each robot's velocity is given as v=x,y where x and y are given in tiles per second. Positive x means the robot is moving to the right, and positive y means the robot is moving down. So, a velocity of v=1,-2 means that each second, the robot moves 1 tile to the right and 2 tiles up.

The robots outside the actual bathroom are in a space which is 101 tiles wide and 103 tiles tall (when viewed from above). However, in this example, the robots are in a space which is only 11 tiles wide and 7 tiles tall.

The robots are good at navigating over/under each other (due to a combination of springs, extendable legs, and quadcopters), so they can share the same tile and don't interact with each other. Visually, the number of robots on each tile in this example looks like this:

1.12.......
...........
...........
......11.11
1.1........
.........1.
.......1...
These robots have a unique feature for maximum bathroom security: they can teleport. When a robot would run into an edge of the space they're in, they instead teleport to the other side, effectively wrapping around the edges. Here is what robot p=2,4 v=2,-3 does for the first few seconds:

Initial state:
...........
...........
...........
...........
..1........
...........
...........

After 1 second:
...........
....1......
...........
...........
...........
...........
...........

After 2 seconds:
...........
...........
...........
...........
...........
......1....
...........

After 3 seconds:
...........
...........
........1..
...........
...........
...........
...........

After 4 seconds:
...........
...........
...........
...........
...........
...........
..........1

After 5 seconds:
...........
...........
...........
.1.........
...........
...........
...........
The Historian can't wait much longer, so you don't have to simulate the robots for very long. Where will the robots be after 100 seconds?

In the above example, the number of robots on each tile after 100 seconds has elapsed looks like this:

......2..1.
...........
1..........
.11........
.....1.....
...12......
.1....1....
To determine the safest area, count the number of robots in each quadrant after 100 seconds. Robots that are exactly in the middle (horizontally or vertically) don't count as being in any quadrant, so the only relevant robots are:

..... 2..1.
..... .....
1.... .....
           
..... .....
...12 .....
.1... 1....
In this example, the quadrants contain 1, 3, 4, and 1 robot. Multiplying these together gives a total safety factor of 12.

Predict the motion of the robots in your list within a space which is 101 tiles wide and 103 tiles tall. What will the safety factor be after exactly 100 seconds have elapsed?

226115604 is low.
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <list>
#include <array>


//#define SAMPLE 1
#ifdef SAMPLE
    #define FILENAME "sample.txt"
    #define ANSWER 12
    #define GRID_SIZE_X 11
    #define GRID_SIZE_Y 7
    #define TICKS 100
#else
    #define FILENAME "input.txt"
    #define GRID_SIZE_X 101
    #define GRID_SIZE_Y 103
    #define TICKS 100
#endif

class Robot {
    public:
    int X;
    int Y;
    int XV;
    int YV;

    Robot( std::string Input ){
        int pos,end;
        pos = Input.find_first_of('=')+1;
        end = Input.find(',',pos);
        X = std::stoi(Input.substr(pos,end-pos));
        pos = end + 1;
        end = Input.find_first_of(' ');
        Y = std::stoi(Input.substr(pos,end-pos));
        pos = end + 3;
        end = Input.find(',',pos);
        XV = std::stoi(Input.substr(pos,end-pos));
        pos = end + 1;
        end = Input.length();
        YV = std::stoi(Input.substr(pos,end-pos));
    }

    void Move(){
        X+=XV;
        Y+=YV;
        RangeCheck:
        if( X > GRID_SIZE_X - 1 ) X -= GRID_SIZE_X;
        if( X < 0 ) X += GRID_SIZE_X;
        if( Y > GRID_SIZE_Y - 1 ) Y -= GRID_SIZE_Y;
        if( Y < 0 ) Y += GRID_SIZE_Y;
        if( X < 0 || X > GRID_SIZE_X - 1 || Y < 0 || Y > GRID_SIZE_Y - 1 ) {
            std::cout << "Range check "<< this << "/n";
            goto RangeCheck;
        }
    }

    int Quadrant() {

        // not in any
        if( X == CX || Y == CY ) return 0; 

        // northwest
        if( X < CX & Y < CY ) return 1; 
        
        // northeast
        if( X > CX & Y < CY ) return 2; 
        
        // southwest
        if( X < CX & Y > CY ) return 3; 
        
        // southeast
        if( X > CX & Y > CY ) return 4; 

        // WTF
        return -1;
    }

    friend std::ostream& operator << (std::ostream &s, const Robot &r){
        s << "X: ";     
        s << std::fixed;
        s << std::setw(5);
        s << r.X;
        s << ", Y: ";
        s << std::fixed;
        s << std::setw(5);
        s << r.Y;
        return s; 
    }

    static void PrintBoard(std::list<Robot> DS){
        for( int y = 0; y < GRID_SIZE_Y; y++ ) {
            for( int x = 0; x < GRID_SIZE_X; x++ ) {
                int c = 0;
                for( Robot r : DS ) if( r.X == x & r.Y == y ) c++;
    
                if( c!=0 ){
                    std::cout << "\x1B[31m";
                    std::cout << " " << c;
                } else {
                    std::cout << "\x1B[34m";
                    std::cout << " .";
                }  
            }
            std::cout << "\033[0m\n";
        }
    }
    
    static void PrintFinal(std::list<Robot> DS){
        for( int y = 0; y < GRID_SIZE_Y; y++ ) {
            for( int x = 0; x < GRID_SIZE_X; x++ ) {
                if( x == CX || y == CY ) {
                    std::cout << "  ";
                    continue;
                }

                int c = 0;
                for( Robot r : DS ) if( r.X == x & r.Y == y ) c++;
    
                if( c!=0 ){
                    std::cout << "\x1B[31m";
                    std::cout << " " << c;
                } else {
                    std::cout << "\x1B[34m";
                    std::cout << " .";
                }  
            }
            std::cout << "\033[0m\n";
        }
    }


    private:
    static constexpr int CX = GRID_SIZE_X / 2;
    static constexpr int CY = GRID_SIZE_Y / 2;

};

std::list<Robot> DataSet;



void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) )  DataSet.push_back(Robot(line));
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );

    int Count = 0;
    std::cout << "Initial State:\n";
    Robot::PrintBoard(DataSet);

    for( int i = 1; i < TICKS + 1; i++ ) {
        for( Robot &R : DataSet ) R.Move();
        #ifdef SAMPLE
        std::cout << "Secs: " << i << "\n";
        Robot::PrintBoard(DataSet);
        std::cout << "\n";
        #endif
    }

    std::array< int, 5 > Quads = {0,0,0,0,0};
    for( Robot &R : DataSet ) Quads[R.Quadrant()]++;

    std::cout << "Final State:\n";
    Robot::PrintFinal(DataSet);

    Count = Quads[1] * Quads[2] * Quads[3] * Quads[4];

    std::cout << "Count: " << Count << "\n";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds\n";

    #ifdef SAMPLE
    if( Count != ANSWER ) throw new std::exception();
    #endif
    return 0;
}
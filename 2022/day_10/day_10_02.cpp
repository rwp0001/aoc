/*

--- Part Two ---

It seems like the X register controls the horizontal position of a sprite. 
Specifically, the sprite is 3 pixels wide, 
and the X register sets the horizontal position of the middle of that sprite. 
(In this system, there is no such thing as "vertical position": 
if the sprite's horizontal position puts its pixels where the CRT is currently drawing, 
then those pixels will be drawn.)

You count the pixels on the CRT: 40 wide and 6 high. 
This CRT screen draws the top row of pixels left-to-right, 
then the row below that, and so on. 
The left-most pixel in each row is in position 0, 
and the right-most pixel in each row is in position 39.

Like the CPU, the CRT is tied closely to the clock circuit: 
the CRT draws a single pixel during each cycle. 

Representing each pixel of the screen as a #, 
here are the cycles during which the first and last pixel in each row are drawn:

Cycle   1 -> ######################################## <- Cycle  40
Cycle  41 -> ######################################## <- Cycle  80
Cycle  81 -> ######################################## <- Cycle 120
Cycle 121 -> ######################################## <- Cycle 160
Cycle 161 -> ######################################## <- Cycle 200
Cycle 201 -> ######################################## <- Cycle 240

So, by carefully timing the CPU instructions and the CRT drawing operations, 
you should be able to determine whether the sprite is visible the instant each pixel is drawn. 

If the sprite is positioned such that one of its three pixels is the pixel currently being drawn, 
the screen produces a lit pixel (#); otherwise, the screen leaves the pixel dark (.).

The first few pixels from the larger example above are drawn as follows:

Sprite position: ###.....................................

Start cycle   1: begin executing addx 15
During cycle  1: CRT draws pixel in position 0
Current CRT row: #

During cycle  2: CRT draws pixel in position 1
Current CRT row: ##
End of cycle  2: finish executing addx 15 (Register X is now 16)
Sprite position: ...............###......................

Start cycle   3: begin executing addx -11
During cycle  3: CRT draws pixel in position 2
Current CRT row: ##.

During cycle  4: CRT draws pixel in position 3
Current CRT row: ##..
End of cycle  4: finish executing addx -11 (Register X is now 5)
Sprite position: ....###.................................

Start cycle   5: begin executing addx 6
During cycle  5: CRT draws pixel in position 4
Current CRT row: ##..#

During cycle  6: CRT draws pixel in position 5
Current CRT row: ##..##
End of cycle  6: finish executing addx 6 (Register X is now 11)
Sprite position: ..........###...........................

Start cycle   7: begin executing addx -3
During cycle  7: CRT draws pixel in position 6
Current CRT row: ##..##.

During cycle  8: CRT draws pixel in position 7
Current CRT row: ##..##..
End of cycle  8: finish executing addx -3 (Register X is now 8)
Sprite position: .......###..............................

Start cycle   9: begin executing addx 5
During cycle  9: CRT draws pixel in position 8
Current CRT row: ##..##..#

During cycle 10: CRT draws pixel in position 9
Current CRT row: ##..##..##
End of cycle 10: finish executing addx 5 (Register X is now 13)
Sprite position: ............###.........................

Start cycle  11: begin executing addx -1
During cycle 11: CRT draws pixel in position 10
Current CRT row: ##..##..##.

During cycle 12: CRT draws pixel in position 11
Current CRT row: ##..##..##..
End of cycle 12: finish executing addx -1 (Register X is now 12)
Sprite position: ...........###..........................

Start cycle  13: begin executing addx -8
During cycle 13: CRT draws pixel in position 12
Current CRT row: ##..##..##..#

During cycle 14: CRT draws pixel in position 13
Current CRT row: ##..##..##..##
End of cycle 14: finish executing addx -8 (Register X is now 4)
Sprite position: ...###..................................

Start cycle  15: begin executing addx 13
During cycle 15: CRT draws pixel in position 14
Current CRT row: ##..##..##..##.

During cycle 16: CRT draws pixel in position 15
Current CRT row: ##..##..##..##..
End of cycle 16: finish executing addx 13 (Register X is now 17)
Sprite position: ................###.....................

Start cycle  17: begin executing addx 4
During cycle 17: CRT draws pixel in position 16
Current CRT row: ##..##..##..##..#

During cycle 18: CRT draws pixel in position 17
Current CRT row: ##..##..##..##..##
End of cycle 18: finish executing addx 4 (Register X is now 21)
Sprite position: ....................###.................

Start cycle  19: begin executing noop
During cycle 19: CRT draws pixel in position 18
Current CRT row: ##..##..##..##..##.
End of cycle 19: finish executing noop

Start cycle  20: begin executing addx -1
During cycle 20: CRT draws pixel in position 19
Current CRT row: ##..##..##..##..##..

During cycle 21: CRT draws pixel in position 20
Current CRT row: ##..##..##..##..##..#
End of cycle 21: finish executing addx -1 (Register X is now 20)
Sprite position: ...................###..................
Allowing the program to run to completion causes the CRT to produce the following image:

##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....

Render the image given by your program. What eight capital letters appear on your CRT?
*/

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <array>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <chrono>

#define SAMPLE 1

#ifdef SAMPLE
#define FILENAME "sample.txt"
#else
#define FILENAME "input.txt"
#endif

int pc = 0;
int x = 1;
int Score = 0;
int y = 1;
char pixels[40][6];
//std::list<int> tests = { 20, 60, 100, 140, 180, 220 };

int signal(){ return pc * x; }

void print(){ 
    std::cout << "Row: " << y << " | ";
    for( int i = 0; i < 40; i++ ) std::cout << pixels[i][y];
    std::cout << std::endl;
}

void test_pc(){
    int xmin = x-1;
    int xmax = x+1;
    if( xmin < 0 ) xmin = 0;
    if( xmax > 39 ) xmax = 39;
    
    if( pc >= xmin & pc <= xmax ) pixels[x][y] = '#';

    if( pc % 40 == 0 ){
        print();
        y++;
        //x = 0;
    }
}

void addx(int V){
    pc++;
    test_pc();
    pc++;
    test_pc();
    x+=V;
    
}

void noop(){ 
    pc++; 
    test_pc();
}

void process( std::string Input ){
    switch( Input[0] ){
        case 'n':
            noop();
            break;
        
        case 'a':
            int V = std::stoi( Input.substr( 5 ) );
            addx( V );    
            break;
    } 
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile;
    myfile.open(filename);
    try {
        if (myfile.is_open()){
            while (getline(myfile, line)) {
                process(line);
            }
        } else throw(std::exception());
        myfile.close();
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }

    //std::cout << "Score: " << Score << std::endl;
}

int main( int argc, char *argv[] ){
    auto start = std::chrono::high_resolution_clock::now();
    for( int ix = 0; ix < 40; ix++ ) for( int iy = 0; iy < 6; iy++ ) pixels[ix][iy] = '.';
    ReadFile( FILENAME );
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by program: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
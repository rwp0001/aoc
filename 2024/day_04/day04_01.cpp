#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>

/*
--- Day 4: Ceres Search ---
"Looks like the Chief's not here. 
Next!" One of The Historians pulls out a device and pushes the only button on it. 
After a brief flash, you recognize the interior of the Ceres monitoring station!

As the search for the Chief continues, a small Elf who lives on the station tugs on your shirt; 
she'd like to know if you could help her with her word search (your puzzle input). 
She only has to find one word: XMAS.

This word search allows words to be horizontal, vertical, diagonal, written backwards, or even overlapping other words. 
It's a little unusual, though, as you don't merely need to find one instance of XMAS - you need to find all of them. 
Here are a few ways XMAS might appear, where irrelevant characters have been replaced with .:


..X...
.SAMX.
.A..A.
XMAS.S
.X....

The actual word search will be full of letters instead. For example:
MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX

In this word search, XMAS occurs a total of 18 times; 
here's the same word search again, 
but where letters not involved in any XMAS have been replaced with .:

....xxMAS.
.SAMxMS...
...S..A...
..A.A.MS.x
xMASAMx.MM
x.....xA.A
S.S.S.S.SS
.A.A.A.A.A
..M.M.M.MM
.x.x.xMASx

Take a look at the little Elf's word search. 
How many times does XMAS appear?

To begin, get your puzzle input.

NOT 2385

*/

//#define SAMPLE 1

#ifdef SAMPLE
    #define FILENAME "sample.txt"
    #define WIDTH 10
    #define HEIGHT 10
#else
    #define FILENAME "input.txt"
    #define WIDTH 140
    #define HEIGHT 140
#endif

//std::vector<std::string> DataSet;
char Board[HEIGHT][WIDTH];
char used[HEIGHT][WIDTH];


const char Target[4] = {'X','M','A','S'};

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::vector<std::string> ExplodeString(std::string input, std::string delimiter = " " ) {
    std::vector<std::string> List;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        List.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    List.push_back(input); // Add the last token
    return List;
}

int Find(int x,int y){
    if(Board[x][y] != Target[0] ) return 0;
    //std::cout << "X: " << x << " Y: " << y << " " << Board[x][y] <<"\n";

    int count = 0;

    if( y < WIDTH - 2 ) {
        if( Board[x][y+1] == Target[1] & Board[x][y+2] == Target[2] & Board[x][y+3] == Target[3] ) 
        {
            count++;    // E    3
            used[x][y] = true;
            // used[x][y+1] = true;
            // used[x][y+2] = true;
            // used[x][y+3] = true;
        }
    }

    if( y > 3 ) {
        if( Board[x][y-1] == Target[1] & Board[x][y-2] == Target[2] & Board[x][y-3] == Target[3] ){
            count++;    // W    2
            used[x][y] = true;
            // used[x][y-1] = true;
            // used[x][y-2] = true;
            // used[x][y-3] = true;
        }
    }

    if( x < HEIGHT - 2 ) {
        if( Board[x+1][y] == Target[1] & Board[x+2][y] == Target[2] & Board[x+3][y] == Target[3] ) {
            count++;    // S    1
            used[x][y] = true;
            // used[x+1][y] = true;
            // used[x+2][y] = true;
            // used[x+3][y] = true;
        }
    }

    if( x > 3 ) {
        if( Board[x-1][y] == Target[1] & Board[x-2][y] == Target[2] & Board[x-3][y] == Target[3] ) {
            count++;    // N    2
            used[x][y] = true;
            // used[x-1][y] = true;
            // used[x-2][y] = true;
            // used[x-3][y] = true;
        }
    }

    if( x > 1 & y > 1 ) {
        if( Board[x-1][y-1] == Target[1] & Board[x-2][y-2] == Target[2] & Board[x-3][y-3] == Target[3] ) {
            count++;    // NW 
            used[x][y] = true;
            // used[x-1][y-1] = true;
            // used[x-2][y-2] = true;
            // used[x-3][y-3] = true;
        }
    }

    if( x > 2 & y < WIDTH - 3 ) {
        if( Board[x-1][y+1] == Target[1] & Board[x-2][y+2] == Target[2] & Board[x-3][y+3] == Target[3] ) {
            count++;    // NE   1
            used[x][y] = true;
            // used[x-1][y+1] = true;
            // used[x-2][y+2] = true;
            // used[x-3][y+3] = true;
        }
    }

    if( x < HEIGHT - 3 & y < WIDTH - 3 ) {
        if( Board[x+1][y+1] == Target[1] & Board[x+2][y+2] == Target[2] & Board[x+3][y+3] == Target[3] ) {
            count++;    // SE
            used[x][y] = true;
            // used[x+1][y+1] = true;
            // used[x+2][y+2] = true;
            // used[x+3][y+3] = true;
        }
    }

    if( x < HEIGHT - 3 & y > 2 ) {
        if( Board[x+1][y-1] == Target[1] & Board[x+2][y-2] == Target[2] & Board[x+3][y-3] == Target[3] ) {
            count++;    // SW
            used[x][y] = true;
            // used[x+1][y-1] = true;
            // used[x+2][y-2] = true;
            // used[x+3][y-3] = true;
        }
    }

    //if(count !=0) std::cout << "X: " << x << " Y: " << y << " " << " Count: " << count <<"\n";
    return count;
}

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
                    Board[Count][pos++] = c;
                    }
                Count++;
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );
    int count = 0;
    //for(int x = 0; x< HEIGHT; x++) for(int y = 0; y< HEIGHT; y++) used[x][y] = false;
    for(int x = 0; x< HEIGHT; x++) for(int y = 0; y< HEIGHT; y++) count += Find(x,y);

    for(int x = 0; x< HEIGHT; x++) {
        for(int y = 0; y< HEIGHT; y++) {
            if( used[x][y]){
                std::cout << "\x1B[31m";
                std::cout << Board[x][y];
            }
            if( !used[x][y] ) {
                std::cout << "\x1B[34m";
                std::cout << Board[x][y];
                //std::cout << ".";
            }  
        }

        std::cout << "\033[0m";
        std::cout << std::endl;
    }
    
    std::cout << "Count: " << count << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}

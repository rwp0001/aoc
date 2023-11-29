/*
--- Day 4: Camp Cleanup ---

Space needs to be cleared before the last supplies can be unloaded from the ships, 
and so several Elves have been assigned the job of cleaning up sections of the camp. 
Every section has a unique ID number, and each Elf is assigned a range of section IDs.

However, as some of the Elves compare their section assignments with each other, 
they've noticed that many of the assignments overlap. To try to quickly find overlaps and reduce duplicated effort, 
the Elves pair up and make a big list of the section assignments for each pair (your puzzle input).

For example, consider the following list of section assignment pairs:

2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8

For the first few pairs, this list means:

Within the first pair of Elves, 
the first Elf was assigned sections 2-4 (sections 2, 3, and 4), 
while the second Elf was assigned sections 6-8 (sections 6, 7, 8).
The Elves in the second pair were each assigned two sections.

The Elves in the third pair were each assigned three sections: 
one got sections 5, 6, and 7, 
while the other also got 7, plus 8 and 9.

This example list uses single-digit section IDs to make it easier to draw; 
your actual list might contain larger numbers. 
Visually, these pairs of section assignments look like this:

.234.....  2-4
.....678.  6-8

.23......  2-3
...45....  4-5

....567..  5-7
......789  7-9

.2345678.  2-8
..34567..  3-7

.....6...  6-6
...456...  4-6

.23456...  2-6
...45678.  4-8

Some of the pairs have noticed that one of their assignments fully contains the other. 
For example, 
2-8 fully contains 3-7, and 
6-6 is fully contained by 4-6. 

In pairs where one assignment fully contains the other, 
one Elf in the pair would be exclusively cleaning sections 
their partner will already be cleaning, 
so these seem like the most in need of reconsideration. 

In this example, there are 2 such pairs.

In how many assignment pairs does one range fully contain the other?

*/

#define COLOR_TERM 0

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

int ProcessData( std::string Line ) {
    int r = 0;
    std::string S1,S2;

    S1 = Line.substr(0,Line.find(','));
    S2 = Line.substr(Line.find(',')+1);
    int s1s = std::stoi(S1.substr(0,S1.find('-'))); 
    int s1e = std::stoi(S1.substr(S1.find('-')+1)); 
    int s2s = std::stoi(S2.substr(0,S2.find('-'))); 
    int s2e = std::stoi(S2.substr(S2.find('-')+1)); 

    if( s1s >= s2s & s2e >= s1e ) r++;
    if( s2s >= s1s & s1e >= s2e ) r++;

    // print out
    std::cout.width(15);
    std::cout << Line;
    std::cout.width();
    std::cout << " | ";
    std::cout.width(2);
    std::cout << s1s;
    std::cout.width();
    std::cout << ",";
    std::cout.width(2);
    std::cout << s1e;
    std::cout.width();
    std::cout << " - ";
    std::cout.width(2);
    std::cout << s2s;
    std::cout.width();
    std::cout << ",";
    std::cout.width(2);
    std::cout << s2e;
    std::cout.width();
    if( COLOR_TERM ) if(r == 0) { std::cout << "\x1B[31m"; } else { std::cout << "\x1B[34m"; }
    std::cout << " R: " << r;
    if( COLOR_TERM ) std::cout << "\033[0m";
    std::cout << "\n";
    return r > 0 ? 1 : 0;

}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Score = 0;
    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) Score += ProcessData( line );
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }

    std::cout <<  "Total Score: " << Score  << "\n";
}

int main()
{
    //ReadFile( "sample.txt" );
    //ReadFile( "sample2.txt" );
    ReadFile( "input.txt" );
}

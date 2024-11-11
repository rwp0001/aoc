/*
--- Day 1: Report Repair ---
After saving Christmas five years in a row, you've decided to take a vacation at a nice resort on a tropical island. Surely, Christmas will go on without you.

The tropical island has its own currency and is entirely cash-only. The gold coins used there have a little picture of a starfish; the locals just call them stars. None of the currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of these coins by the time you arrive so you can pay the deposit on your room.

To save your vacation, you need to get all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

Before you leave, the Elves in accounting just need you to fix your expense report (your puzzle input); apparently, something isn't quite adding up.

Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.

For example, suppose your expense report contained the following:
1721
979
366
299
675
1456

In this list, the two entries that sum to 2020 are 1721 and 299. 
Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.

Of course, your expense report is much larger. 
Find the two entries that sum to 2020; 
what do you get if you multiply them together?
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>
#include <chrono>

std::list<int> DataSet;

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;

    try
    {
        myfile.open( filename );

        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                DataSet.push_front(std::stoi(line));
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
    int z,s;

    for( int x : DataSet ) {
        for(int y : DataSet) {
            if( x==y) continue;
            z = x+y;
            if( z == 2020 ) {
                s = x*y;
                std::cout << "X: " << x << " Y: " << y << " Z:" << z << " S: " << s << std::endl;
                break;
            }
        }
        if( z == 2020 ) break;
    }


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
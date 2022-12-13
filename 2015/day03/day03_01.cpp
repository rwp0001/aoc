/*
--- Day 3: Perfectly Spherical Houses in a Vacuum ---

Santa is delivering presents to an infinite two-dimensional grid of houses.

He begins by delivering a present to the house at his starting location, 
and then an elf at the North Pole calls him via radio and tells him where to move next. 
Moves are always exactly one house to the north (^), south (v), east (>), or west (<). 
After each move, he delivers another present to the house at his new location.

However, the elf back at the north pole has had a little too much eggnog, 
and so his directions are a little off, and Santa ends up visiting some houses more than once. 
How many houses receive at least one present?

For example:

> delivers presents to 2 houses: one at the starting location, and one to the east.
^>v< delivers presents to 4 houses in a square, including twice to the house at his starting/ending location.
^v^v^v^v^v delivers a bunch of presents to some very lucky children at only 2 houses.

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

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int x,y,min_x,min_y,max_x,max_y,v[200][200],Count;
    for(x=0; x<199; x++) for(y=0; y<199; y++) v[x][y] = 0; 
    x=0;
    y=0;
    v[x+100][y+100]++;
    
    try
    {
        if (myfile.is_open()){
            char c;
            while ( getline( myfile, line ) ) {
                for( int i = 0; i < line.length(); i++ ) {
                    c = line[i];
                    if( c == '>' ) x++;
                    if( c == '<' ) x--;
                    if( c == '^' ) y++;
                    if( c == 'v' ) y--;
                    v[x+100][y+100]++;

                    //if( x < min_x ) min_x = x;
                    //if( y < min_y ) min_y = y;
                    //if( x > max_x ) max_x = x;
                    //if( y > max_y ) max_y = y;
                    //std::cout << "I: " << i << " C: " << c << " X: " << x << " Y: " << y << " Count: " << v[x+100][y+100] <<"\n\n";
                }
            }
            //std::cout << "Count: " << Count << "\n";
        } else throw( std::exception() );
        myfile.close();

        for(x=0; x<199; x++) {
            for(y=0; y<199; y++) {
                //std::cout << " X: " << x << " Y: " << y << " Count: " << v[x][y] <<"\n";
                if( v[x][y] != 0 ) Count++;
            }
        }
        std::cout << "Count: " << Count << "\n";

    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }

}

int main()
{
    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
}

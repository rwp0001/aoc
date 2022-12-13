/*
--- Day 2: I Was Told There Would Be No Math ---

The elves are running low on wrapping paper, and so they need to submit an order for more. 
They have a list of the dimensions (length l, width w, and height h) of each present, 
and only want to order exactly as much as they need.

Fortunately, every present is a box (a perfect right rectangular prism), 
which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, 
which is 2*l*w + 2*w*h + 2*h*l. 
The elves also need a little extra paper for each present: the area of the smallest side.

For example:

A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, 
for a total of 58 square feet.
A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, 
for a total of 43 square feet.
All numbers in the elves' list are in feet. 
How many total square feet of wrapping paper should they order?

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

int CalcArea( std::string Input ) {    
    int l,w,h,x1,x2,s;
    std::string str = Input;
    
    // get first number.
    x1 = str.find( 'x', 0 );
    x2 = str.rfind( 'x', std::string::npos );

    l = std::stoi( str.substr( 0, x1 ) );
    w = std::stoi( str.substr( x1+1, x2-x1) );
    h = std::stoi( str.substr( x2+1, str.length() - x2 ) );
    s = l * w;
    if( l * h < s ) s = l * h;
    if( w * h < s ) s = w * h;
    std::cout << "L: " << l << " W: " << w << " H: " << h << " S: " << s << "\n";  
    return ( 2 * l * w ) + ( 2 * w * h ) + ( 2 * h * l ) + s;
}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Area = 0;

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) Area += CalcArea(line);
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
    std::cout << "Total Area: " << Area << "\n";
}

int main()
{
    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
}

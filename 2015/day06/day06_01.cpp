/*
--- Day 6: Probably a Fire Hazard ---

Because your neighbors keep defeating you in the holiday house decorating contest year after year, 
you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, 
Santa has mailed you instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; 
the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. 
The instructions include whether to turn on, turn off, 
or toggle various inclusive ranges given as coordinate pairs. 
Each coordinate pair represents opposite corners of a rectangle, 
inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. 
The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions 
Santa sent you in order.

For example:

turn on 0,0 through 999,999 would turn on (or leave on) every light.
toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, 
and turning on the ones that were off.
turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.
After following the instructions, how many lights are lit?


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
#include <cmath>
#include <cstdint>

float Lights[1000][1000];

void ClearLights(){
    for( int x = 0; x < 999; x++ ) for( int y = 0; y < 999; y++ ) Lights[x][y] = 0;
}

int CountLights(){
    int Count;
    for( int x = 0; x < 1000; x++ ) for( int y = 0; y < 1000; y++ ) if( Lights[x][y] != 0 ) Count++;
    return Count;
}

void TurnOn( int x1, int y1, int x2, int y2 ){
    for( int x = x1; x < x2; x++ ) for( int y = y1; y < y2; y++ ) Lights[x][y] = 255;
}

void TurnOff( int x1, int y1, int x2, int y2 ){
    for( int x = x1; x < x2; x++ ) for( int y = y1; y < y2; y++ ) Lights[x][y] = 0;
}

void Toggle( int x1, int y1, int x2, int y2 ){
    for( int x = x1; x < x2; x++ ) for( int y = y1; y < y2; y++ ) {
        if( Lights[x][y] != 0 ) {
            Lights[x][y] = 0; 
        } else {
            Lights[x][y] = 255; 
        }
    }
}

void DoAction( std::string Input ){
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    std::string c1,c2;
    
    if( Input.find("turn on ",0) != std::string::npos ){
        Input = Input.substr( 8, Input.length() - 8 );
        c1 = Input.substr( 0, Input.find(" through ", 0 ) );
        c2 = Input.substr( Input.find(" through ",0 ) + 9, Input.length() - 9 );
        x1 = std::stoi( c1.substr( 0, c1.find( ",", 0 ) ) );
        y1 = std::stoi( c1.substr( c1.find( ",", 0 ) + 1, c1.length() - c1.find( ",", 0 ) ) );
        x2 = std::stoi( c2.substr( 0, c2.find( ",", 0 ) ) );
        y2 = std::stoi( c2.substr( c2.find( ",", 0 ) + 1, c2.length() - c2.find( ",", 0 ) ) );
        TurnOn( x1, y1, x2, y2 );
    }

    if( Input.find("turn off ",0) != std::string::npos ){
        Input = Input.substr( 9, Input.length() - 9 );
        c1 = Input.substr( 0, Input.find(" through ", 0 ) );
        c2 = Input.substr( Input.find(" through ",0 ) + 9, Input.length() - 9 );
        x1 = std::stoi( c1.substr( 0, c1.find( ",", 0 ) ) );
        y1 = std::stoi( c1.substr( c1.find( ",", 0 ) + 1, c1.length() - c1.find( ",", 0 ) ) );
        x2 = std::stoi( c2.substr( 0, c2.find( ",", 0 ) ) );
        y2 = std::stoi( c2.substr( c2.find( ",", 0 ) + 1, c2.length() - c2.find( ",", 0 ) ) );
        TurnOff( x1, y1, x2, y2 );
    }

    if( Input.find("toggle ",0) != std::string::npos ){
        Input = Input.substr( 7, Input.length() - 7 );
        c1 = Input.substr( 0, Input.find(" through ", 0 ) );
        c2 = Input.substr( Input.find(" through ",0 ) + 9, Input.length() - 9 );
        x1 = std::stoi( c1.substr( 0, c1.find( ",", 0 ) ) );
        y1 = std::stoi( c1.substr( c1.find( ",", 0 ) + 1, c1.length() - c1.find( ",", 0 ) ) );
        x2 = std::stoi( c2.substr( 0, c2.find( ",", 0 ) ) );
        y2 = std::stoi( c2.substr( c2.find( ",", 0 ) + 1, c2.length() - c2.find( ",", 0 ) ) );
        Toggle( x1, y1, x2, y2 );
    }

}

void save_image(const ::std::string &name, float img_vals[][1000])
{
   using ::std::string;
   using ::std::ios;
   using ::std::ofstream;
   typedef unsigned char pixval_t;
   auto float_to_pixval = [](float img_val) -> pixval_t {
      int tmpval = static_cast<int>(::std::floor(256 * img_val));
      if (tmpval < 0) {
         return 0u;
      } else if (tmpval > 255) {
         return 255u;
      } else {
         return tmpval & 0xffu;
      }
   };
   auto as_pgm = [](const string &name) -> string {
      if (! ((name.length() >= 4)
             && (name.substr(name.length() - 4, 4) == ".pgm")))
      {
         return name + ".pgm";
      } else {
         return name;
      }
   };

   ofstream out(as_pgm(name), ios::binary | ios::out | ios::trunc);

   out << "P5\n1000 1000\n255\n";
      for (int x = 0; x < 1000; ++x) {
      for (int y = 0; y < 1000; ++y) {
         const pixval_t pixval = float_to_pixval(img_vals[x][y]);
         const char outpv = static_cast<const char>(pixval);
         out.write(&outpv, 1);
      }
   }
}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Count = 0;
    std::string ImageName;

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                DoAction(line);
                ImageName = "Frame_" + std::to_string( Count );
                save_image(ImageName,Lights);
                Count++;
            }
        } else throw( std::exception() );
        myfile.close();

    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }

}


int main()
{
    ClearLights();
    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
    std::cout << "Count: " << CountLights() <<"\n";

}

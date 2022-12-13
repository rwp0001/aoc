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

#define X_ARRAY_SIZE 11
#define Y_ARRAY_SIZE 15

#define FILENAME "sample.txt"
//#define FILENAME "input.txt"

struct Command
{
    int Axis;
    int Pos;
};
std::array<std::array<char,Y_ARRAY_SIZE>,X_ARRAY_SIZE> Data;
std::list<Command> CommandList;

void Fold( Command C ) {
    
}


void Print(){
  std::cout << "\n  ";
    for(int x=0; x<X_ARRAY_SIZE; x++) {
        std::cout.width(2);
        std::cout << x;
    }
    std::cout << "\n";

    for(int y = 0; y < Y_ARRAY_SIZE; y++ ) {
        std::cout.width(2);
        std::cout << y;
        for(int x = 0; x < X_ARRAY_SIZE; x++ ) {
            std::cout.width(2);
            std::cout << Data[x][y];
        }
        std::cout << "\n";
    }
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    int Count = 0;

    try
    {
        for( int x = 0; x < X_ARRAY_SIZE; x++ ) for( int y = 0; y < Y_ARRAY_SIZE; y++ ) Data[x][y] = '.';
        if (myfile.is_open()){
            while (getline(myfile, line)){
                if( line.length() == 0) continue; // Blank line

                if( line.substr(0,1) == "f" ){ // fold Command
                    int c;
                    Command NewCommand;
                    c=line.find_first_of('=');
                    NewCommand.Pos = std::stoi( line.substr(c+1, line.length()-c));
                    if( line.substr(c-1,1) == "x" ) NewCommand.Axis = 1;
                    if( line.substr(c-1,1) == "y" ) NewCommand.Axis = 2;
                    CommandList.push_back(NewCommand);
                    std::cout << "Added Command " << NewCommand.Axis << " Pos: " << NewCommand.Pos << "\n";
                    continue;
                }

                // dots
                int x,y,c;
                c=line.find_first_of(',');
                x=std::stoi( line.substr(0,c) );
                y=std::stoi( line.substr(c+1, line.length()-c));
                Data[x][y] = '#';
                std::cout << "Marked " <<x << "," << y << "\n";
            }
        } else throw(std::exception());
        myfile.close();
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
}

int main(){
    ReadFile( FILENAME );
    Print();
    std::cout <<  "\n";
    return 0;
}
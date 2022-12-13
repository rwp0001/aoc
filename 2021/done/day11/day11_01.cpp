#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

#define X_MAX 10
#define Y_MAX 10
#define STEPS 100
#define COL_WIDTH 3

int octopuses[X_MAX][Y_MAX];
bool  flashed[X_MAX][Y_MAX];
int FlashCount = 0;

void print(){
    std::cout.width(COL_WIDTH);
    std::cout << " ";
    for(int x=0; x<Y_MAX; x++) {
        std::cout.width(COL_WIDTH);
        std::cout << x;
    }
    std::cout << "\n";

    for(int x=0; x<X_MAX; x++){
        std::cout.width(COL_WIDTH);
        std::cout << x;
        for(int y=0; y<Y_MAX; y++){

            std::string s = std::to_string( octopuses[x][y] );

            if( octopuses[x][y] == 0 ){
                std::cout << "\x1B[31m";
            }

            if( octopuses[x][y] != 0 ) {
                std::cout << "\x1B[34m";
            }  
            std::cout.width(COL_WIDTH);  
            std::cout << s;
            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
    std::cout << "Flashes: " << FlashCount << "\n\n";
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile;
    myfile.open(filename);
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            std::string c;
            while (getline(myfile, line)){
                for(int i = 0; i<line.length();i++){
                    c = line[i];
                    octopuses[Count][i] = std::stoi(c);
                    flashed[Count][i] = false;
                }
                Count++;
            }
            //std::cout << "Count: " << Count << "\n";
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
}

void Step_03_IncrementNeighbors(int x, int y){
    if( x != 0 & y != 0 )              if( !flashed[x-1][y-1] ) octopuses[x-1][y-1]++; // NW
    if( x != 0 )                       if( !flashed[x-1][ y ] ) octopuses[x-1][ y ]++; // N
    if( x != 0 & y != Y_MAX-1 )        if( !flashed[x-1][y+1] ) octopuses[x-1][y+1]++; // NE
    if( y != 0 )                       if( !flashed[ x ][y-1] ) octopuses[ x ][y-1]++; // W
    if( y != Y_MAX-1 )                 if( !flashed[ x ][y+1] ) octopuses[ x ][y+1]++; // E
    if( x != X_MAX-1  & y != 0 )       if( !flashed[x+1][y-1] ) octopuses[x+1][y-1]++; // SW
    if( x != X_MAX-1  )                if( !flashed[x+1][ y ] ) octopuses[x+1][ y ]++; // S
    if( x != X_MAX-1  & y != Y_MAX-1 ) if( !flashed[x+1][y+1] ) octopuses[x+1][y+1]++; // SE
}


void Step_02_Flash(){
    for( int x = 0; x < X_MAX; x++ ) {
        for( int y = 0; y < Y_MAX; y++ ){
            if( octopuses[x][y] > 9 ) {
                flashed[x][y] = true;
                octopuses[x][y] = 0;
                FlashCount++;
                Step_03_IncrementNeighbors(x,y);
                x = 0;
                y = 0;
            }
        }
    } 
}

void Step_01_IncrementAll(){
    for( int x = 0; x < X_MAX; x++ ){
        for( int y = 0; y < Y_MAX; y++ ){
            octopuses[x][y]++;
        }
    }
}

void ClearFlashes(){
    for( int x = 0; x < X_MAX; x++ ) for( int y = 0; y < Y_MAX; y++ ) flashed[x][y] = false;
}

bool AllFlashed(){
    for( int x = 0; x < X_MAX; x++ ) for( int y = 0; y < Y_MAX; y++ ) if ( !flashed[x][y] ) return false;
    return true;
}

int main(){
    ReadFile("input.txt");
    print();
    int i = 1;
    for(; ; i++ ){
        Step_01_IncrementAll();
        Step_02_Flash();
        Step_02_Flash();
        Step_02_Flash();
        if(AllFlashed()) break;    
        ClearFlashes();
    }

    std::cout << "Step: " << i << "\n";
    print();
    std::cout << "\n";
    return 0;
}
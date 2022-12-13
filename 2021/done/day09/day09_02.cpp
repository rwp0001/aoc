#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

#define X_MAX 100
#define Y_MAX 100

struct Point
{
    int X = 0;
    int Y = 0;
    int ID = 0;
};

int Data[X_MAX][Y_MAX][3];
std::list<Point> LowPoints;

void scan(int x, int y, int id){
    int neighbors[4] = {9,9,9,9}; // up, down, left, right
    Data[x][y][2] = id;
    if( x != 0 )       neighbors[0] = Data[x-1][y][1];
    if( x != X_MAX-1 ) neighbors[1] = Data[x+1][y][1]; 
    if( y != 0 )       neighbors[2] = Data[x][y-1][1];
    if( y != Y_MAX-1 ) neighbors[3] = Data[x][y+1][1];   
    if( neighbors[0] < 9 & Data[x-1][y][2] == 0 ) scan( x-1, y, id );     
    if( neighbors[1] < 9 & Data[x+1][y][2] == 0 ) scan( x+1, y, id );
    if( neighbors[2] < 9 & Data[x][y-1][2] == 0 ) scan( x, y-1, id );
    if( neighbors[3] < 9 & Data[x][y+1][2] == 0 ) scan( x, y+1, id );
}

int BasinArea(int id){
    int returnValue = 0;
    for(int x = 0; x<X_MAX;x++){
        for(int y = 0; y<Y_MAX;y++){
            if(id == Data[x][y][2]) returnValue++;
        }
    }
    return returnValue;
}

void RunScan(){
    int Count=10;
    std::list<int> Sizes;

    for( auto it = LowPoints.begin(); it != LowPoints.end(); it++ ){
        Point p = *it;
        scan(p.X,p.Y, Count);
        int c = BasinArea(Count);
        Sizes.push_back(c);
        std::cout << "Id: " << Count << " Size: " << c << "\n";

        Count++;
    }
    Sizes.sort();

    auto it = Sizes.end();
    it--;
    int i = *it;
    it--;
    i *= *it;
    it--;
    i *= *it;

    std::cout << "Answer:" <<i;
}

void find_depths(){
    int Count = 1;
    int Sum = 0;
    for(int x = 0; x<X_MAX;x++){
        for(int y = 0; y<Y_MAX;y++){
            int v = Data[x][y][1];
            /*
            std::cout << "\nX: ";
            std::cout.width(3);
            std::cout << x;
            std::cout << ", Y: ";
            std::cout.width(3);
            std::cout << y;
            std::cout << " | V: ";
            std::cout.width(2);
            std::cout << v;
            */

            int up = 0,down = 0,right = 0,left = 0; 

            if( x != 0 ) {
                up = Data[x-1][y][1];
                //std::cout << " | U: ";
                //std::cout.width(2);
                //std::cout << up;
            }

            if( x != X_MAX-1 ) {
                down = Data[x+1][y][1];
                //std::cout << " | D: ";
                //std::cout.width(2);
                //std::cout  << down;

            }

            if( y != 0 ) {
                left = Data[x][y-1][1];
                //std::cout << " | L: ";
                //std::cout.width(2);
                //std::cout  << left;

            }

            if( y != Y_MAX-1 ){
                right = Data[x][y+1][1];
                //std::cout << " | R: ";
                //std::cout.width(2);
                //std::cout  << right;

            }

            if( x != 0 & v >= up ) continue;
            if( x != X_MAX-1 & v >= down ) continue;
            if( y != 0 & v >= left ) continue;
            if( y != Y_MAX-1 & v >= right ) continue;

            //std::cout << " - Risk: " << Data[x][y][1]+1;
            Data[x][y][2] = 1;
            //creatPoint(x,y);

            Point p;
            p.X = x;
            p.Y = y;
            p.ID = Count;
            LowPoints.push_back(p);
            Sum += Data[x][y][1]+1;
            Count++;
        }
        //std::cout << "\n";
    }
    std::cout << "\nCount: " << Count << " Sum: " << Sum << "\n";
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            std::string c;
            while (getline(myfile, line)){
                for(int i = 0; i<line.length();i++){
                    c = line[i];
                    Data[Count][i][1] = std::stoi(c);
                    if(Data[Count][i][1] == 9) {
                        Data[Count][i][0] = 0;
                    } else {
                        Data[Count][i][0] = 1;
                    }
                    Data[Count][i][2] = 0;
                }
                Count++;
            }
            std::cout << "Count: " << Count << "\n";
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
}

void print_depths(){
    std::cout << "\n  ";
    for(int x=0; x<Y_MAX; x++) {
        std::cout.width(3);
        std::cout << x;
    }
    std::cout << "\n";

    for(int x=0; x<X_MAX; x++){
        std::cout.width(2);
        std::cout << x;
        for(int y=0; y<Y_MAX; y++){

            std::string s = "@";

            if( Data[x][y][2] != 0 ){
                s = std::to_string( Data[x][y][2] );
                //s = "X";
                std::cout << "\x1B[31m";
            }

            if( Data[x][y][0] != 0 ) {
                s = std::to_string( Data[x][y][2] );
                //s = "*";   //"\u2588";
                std::cout << "\x1B[34m";
            }  
            std::cout.width(3);  
            std::cout << s;
            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
}

int main(){
    ReadFile("input.txt");
    find_depths();
    RunScan();
    print_depths();



    std::cout << "\n";
    return 0;
}
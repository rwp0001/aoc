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

int Data[X_MAX][Y_MAX];

struct Point
{
    int x = 0;
    int y = 0;
    int Risk = 0;
};

std::list<Point> RiskPoints;

void creatPoint(int x,int y) {
    Point p;
    p.Risk = Data[x][y]+1;
    p.x = x;
    p.y = y;
    RiskPoints.push_back(p);
    std::cout << "X: " << p.x << " Y: " << p.y << " Risk: " << p.Risk << "\n";
}

void scan(){
    int Count = 0;
    int Sum = 0;
    for(int x = 0; x<X_MAX;x++){
        for(int y = 0; y<Y_MAX;y++){
            int v = Data[x][y];
            std::cout << "\nX: ";
            std::cout.width(3);
            std::cout << x;
            std::cout << ", Y: ";
            std::cout.width(3);
            std::cout << y;
            std::cout << " | V: ";
            std::cout.width(2);
            std::cout << v;


            int up = 0,down = 0,right = 0,left = 0; 

            if( x != 0 ) {
                up = Data[x-1][y];
                std::cout << " | U: ";
                std::cout.width(2);
                std::cout << up;
            }

            if( x != X_MAX-1 ) {
                down = Data[x+1][y];
                std::cout << " | D: ";
                std::cout.width(2);
                std::cout  << down;

            }

            if( y != 0 ) {
                left = Data[x][y-1];
                std::cout << " | L: ";
                std::cout.width(2);
                std::cout  << left;

            }

            if( y != Y_MAX-1 ){
                right = Data[x][y+1];
                std::cout << " | R: ";
                std::cout.width(2);
                std::cout  << right;

            }

            if( x != 0 & v >= up ) continue;
            if( x != X_MAX-1 & v >= down ) continue;
            if( y != 0 & v >= left ) continue;
            if( y != Y_MAX-1 & v >= right ) continue;

            std::cout << " - Risk: " << Data[x][y]+1;

            //creatPoint(x,y);
            Sum += Data[x][y]+1;
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
                    Data[Count][i] = std::stoi(c);
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

void print(){
    std::cout << "\n  ";
    for(int x=0; x<Y_MAX; x++) {
        std::cout.width(2);
        std::cout << x;
    }
    std::cout << "\n";

    for(int x=0; x<X_MAX; x++){
        std::cout.width(2);
        std::cout << x;
        for(int y=0; y<Y_MAX; y++){
            std::cout.width(2);
            std::cout << Data[x][y];
        }
        std::cout << "\n";
    }
}



int main(){
    ReadFile("input.txt");
    print();
    scan();
    std::cout << "\n";
    return 0;
}
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <exception>

int Points[1000][1000];

void Line(int x1,int y1,int x2,int y2){
    int x = x1;
    int y = y1;
    int ix = 0;
    int iy = 0;
    if( x1 < x2 ) ix = 1; else if( x1 > x2 ) ix = -1;
    if( y1 < y2 ) iy = 1; else if( y1 > y2 ) iy = -1;
    while(x != x2+ix | y != y2+iy){
        Points[x][y]++;
        x += ix;
        y += iy;
    }
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);

    try
    {
        if (myfile.is_open()){
            int Index = 0;
            while (getline(myfile, line)){
                //std::cout << line << "\n";
                int x1,x2,y1,y2,c1,c2;
                c1=line.find_first_of(',');
                c2=line.find_first_of(' ');
                x1=std::stoi( line.substr(0,c1) );
                y1=std::stoi( line.substr(c1+1, c2-c1));
                c1=line.find_first_of('>');
                line = line.substr(c1+1,std::string::npos);
                c1=line.find_first_of(',');
                x2=std::stoi( line.substr(0,c1) );
                y2=std::stoi( line.substr(c1+1,std::string::npos));
                Line(x1,y1,x2,y2);
                std::cout << "Line " << Index << " from point 1: (" << x1 << "," << y1 << ") to point 2: (" << x2 << "," << y2 << ")\n";
                Index++;
            }
        } else throw(std::exception());
        myfile.close();       
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }  
};

void print(){
    int Count = 0;

    std::cout << "\n  ";
    for(int x=0; x<10; x++) {
        std::cout.width(2);
        std::cout << x;
    }
    std::cout << "\n";

    for(int x=0; x<10; x++){
        std::cout.width(2);
        std::cout << x;
        for(int y=0; y<10; y++){
            if(Points[x][y] == 0) {
                std::cout.width(2);
                std::cout << ".";
            } else {
                std::cout.width(2);
                std::cout << Points[x][y];
            }
            if(Points[x][y]>1) Count++;
        }
        std::cout << "\n";
    }
    std::cout << "Count: " << Count << "\n";
}

void Calculate(){
    int Count = 0;
    for(int x=0; x<1000; x++) for(int y=0; y<1000; y++) if(Points[x][y]>1) Count++;
    std::cout << "Count: " << Count << "\n";
}

int main(){
    ReadFile("sample.txt");
    print();
    //Calculate();
}
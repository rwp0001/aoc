#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <exception>

uint64_t Fish[9] = {0,0,0,0,0,0,0,0,0};
int day = 0;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);

    try
    {
        if (myfile.is_open()){
            getline(myfile, line);
            std::stringstream          lineStream(line);
            std::string                age;
            while(std::getline(lineStream,age, ',')) Fish[std::stoi(age)]++;
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
};

void print(){
    uint64_t  Count = 0;
    std::cout << "Day: ";
    std::cout.width(3);
    std::cout <<  day;
    std::cout <<" Fish Ages:";
    for(int x=0; x<9; x++) {
        std::cout << "  [" << x << "]: ";
        std::cout.width(5);
        std::cout << Fish[x];
        Count += Fish[x];
    }
    std::cout << "  - Count: ";
    std::cout.width(8);
    std::cout << Count;
    std::cout << "\n";
}

void tick(){
    uint64_t tmp = Fish[0];
    Fish[0] = Fish[1];
    Fish[1] = Fish[2];
    Fish[2] = Fish[3];
    Fish[3] = Fish[4];
    Fish[4] = Fish[5];
    Fish[5] = Fish[6];
    Fish[6] = Fish[7];
    Fish[7] = Fish[8];
    Fish[8] = tmp;
    Fish[6] += tmp;
    if(day>250||day%10==0)print();
    day++;
}

int main(){
    ReadFile("input.txt");
    for(int i = 0; i<256; i++) tick();
}
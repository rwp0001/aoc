#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

std::list<int> Crabs;

int minPos(){
    Crabs.sort();
    auto i = Crabs.begin();
    return *i;
}

int maxPos(){
    Crabs.sort();
    auto i = Crabs.end();
    i--;
    return *i;
}

int range(){
    return maxPos() - minPos();
}

int sum(){
    int returnValue = 0;
    for (auto it = Crabs.begin() ; it !=  Crabs.end(); it++) returnValue += *it;
    return returnValue;
}

int avg(){
    return sum() / Crabs.size();
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);

    try
    {
        if (myfile.is_open()){
            getline(myfile, line);
            std::stringstream          lineStream(line);
            std::string                pos;
            while(std::getline(lineStream,pos, ',')) Crabs.push_back(std::stoi(pos));
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
};

int fuelcost(int Pos){
    int returnValue = 0;
    for (auto it = Crabs.begin() ; it !=  Crabs.end(); it++){
        int Distance = std::abs(*it-Pos);
        for(int i = 1; i < Distance+1; i++){
            returnValue += i;
        }
    }     
    return returnValue;
}

int main(){
    ReadFile("input.txt");
    Crabs.sort();
    unsigned int fuel = 0;
    fuel--;
    int Position = 0;

    for(int i = minPos(); i < maxPos(); i++){
        int f = fuelcost(i);
        if( f < fuel ) {
             fuel = f;
             Position = i;
        }
    }

    std::cout << "Pos: " << Position << " Fuel Cost: " << fuelcost( Position ) << "\n";

    return 0;
}
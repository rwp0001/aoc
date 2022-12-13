#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

#define FILENAME "sample.txt"

class Cave {
    bool _Entered = false;

    public:
    std::list<std::string> Connections;
    std::string Name;
    
    Cave(std::string name){
        Name = name;
        if( Name[0] <= 'A' & Name[0] >= 'Z' ) Small = false;
    }

    Cave(){}

    void AddConnection(std::string Connection){
        Connections.push_back(Connection);
    }

    bool Small = true;

    bool CanBeEntered(){
        if( Small & _Entered ) return false;
        return true;
    } 

    int NumberOfConnections(){
        return Connections.size();
    }   
};

std::list<Cave> AllCaves = std::list<Cave>();

Cave FindByName(std::string name){
    Cave returnValue;
    for(auto it = AllCaves.begin(); it != AllCaves.end(); it++){
        if( it->Name == name ) return *it;
    }
    return returnValue;
}



std::list<Cave> Caves;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);

    try
    {
        if (myfile.is_open()){
            std::string c;
            while (getline(myfile, line)){
                std::stringstream          lineStream(line);
                std::string                item;
                Cave a,b;
                int Count = 0;
                std::string Connection[2];
                while(std::getline(lineStream,item, '-')){
                    Connection[Count] = item;
                    Count++;
                }
                if( FindByName(Connection[0]) != NULL ) a = Cave(item);
                if( FindByName(Connection[1]) != NULL ) b = Cave(item);
                a.AddConnection(b.Name);
                b.AddConnection(a.Name);


            }
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
}



int main(){
    ReadFile( FILENAME );
    
    std::cout << "\n";
    return 0;
}
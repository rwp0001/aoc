#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while (getline(myfile, line)){
                int c = line.find_first_of("|");
                std::string str_value = line.substr(c+1,std::string::npos);
                std::stringstream lineStream(str_value);
                std::string s;            
                while(std::getline(lineStream,s, ' ')) {
                    int l = s.length();
                    switch (l)
                    {
                    case 2:
                        [[fallthrough]];
                    case 3:
                        [[fallthrough]];
                    case 4:
                        [[fallthrough]];
                    case 7:
                        [[fallthrough]];
                    case 8:
                        Count++;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
            
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "Count: " << Count << "\n";
};

int main(){
    ReadFile("input.txt");
    return 0;
}
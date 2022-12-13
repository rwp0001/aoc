#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <array>

int main()
{
    std::string line;
    std::ifstream myfile("input.txt");
    std::string space_delimiter = " ";
    int O2 =0;
    int CO2 =0;
    std::list<std::string> O2_Data;
    std::list<std::string> CO2_Data;
    std::string O2_str;
    std::string CO2_str;



    // ---------- Input File Processing ---------
    if (myfile.is_open())
    {
        int Index = 0;
        while (getline(myfile, line))
        {
            O2_Data.push_back(line);
            CO2_Data.push_back(line);
            //std::cout << Index << ": "  << line << "\n";
            Index++;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file";
        return 1;
    }

    // ------- Data Processing Below ---------
    // oxygen generator rating
    // To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, 
    // and keep only numbers with that bit in that position. 
    // If 0 and 1 are equally common, keep values with a 1 in the position being considered.


    for(int i = 0; i<12;i++){
        if(O2_Data.size() == 1) break;
        int Zero = 0;
        int One = 0;
        for (auto it = O2_Data.begin() ; it != O2_Data.end(); it++) {
            line = *it;
            switch (line[i])
            {
            case '0':
                Zero++;
                break;
            case '1':
                One++;
            default:
                break;
            }
        }

        std::cout << "Bit: " << i << " Ones: " << One << " Zeros: " << Zero << " Count: " << O2_Data.size()<<"\n";

        char Test_str = '1';
        if( One >= Zero ) Test_str = '0'; else Test_str = '1';
        std::cout << "Bit: " << i << " Filtering: " << Test_str << "\n";
        
        auto it = O2_Data.begin();
        while(it != O2_Data.end())
        {
            std::string Data = *it;
            if( Data[i] == Test_str ){
                //std::cout << " Removing. " << Data << "\n";
                O2_Data.erase(it);
                it=O2_Data.begin();
            } else { 
                //std::cout << "Keeping: " << Data << "\n"; 
                it++; 
            }
        }
    }

    auto it = O2_Data.begin();
    O2_str = *it;

    // CO2 scrubber rating
    // To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, 
    // and keep only numbers with that bit in that position. 
    // If 0 and 1 are equally common, keep values with a 0 in the position being considered.

    for(int i = 0; i<12;i++){
        if(CO2_Data.size() == 1) break;
        int Zero = 0;
        int One = 0;
        for (auto it = CO2_Data.begin() ; it != CO2_Data.end(); it++) {
            line = *it;
            switch (line[i])
            {
            case '0':
                Zero++;
                break;
            case '1':
                One++;
            default:
                break;
            }
        }

        std::cout << "Bit: " << i << " Ones: " << One << " Zeros: " << Zero << " Count: " << CO2_Data.size()<<"\n";
        
        char Test_str = '0';
        if( Zero > One ) Test_str = '0'; else Test_str = '1';
        std::cout << "Bit: " << i << " Filtering: " << Test_str << "\n";
        
        auto it = CO2_Data.begin();
        while(it != CO2_Data.end())
        {
            std::string Data = *it;
            if( Data[i] == Test_str ){
                //std::cout << " Removing. " << Data << "\n";
                CO2_Data.erase(it);
                it=CO2_Data.begin();
            } else it++;
        }
    }

    auto it2 = CO2_Data.begin();
    CO2_str = *it2;

// ------- Answer Reporting Below ---------
    O2 = std::stoi(O2_str, 0, 2);
    CO2 = std::stoi(CO2_str, 0, 2);
    std::cout << "O2: " << O2_str << " CO2: " << CO2_str << "\n";
    std::cout << "O2: " << O2 << " CO2: " << CO2 << "\n";
    std::cout << "Answer: " << O2 * CO2 << "\n";
    return 0;   

}



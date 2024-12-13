#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>

/*
--- Day 2: Red-Nosed Reports ---
Fortunately, the first location The Historians want to search isn't a long walk from the Chief Historian's office.

While the Red-Nosed Reindeer nuclear fusion/fission plant appears to contain no sign of the Chief Historian, the engineers there run up to you as soon as they see you. Apparently, they still talk about the time Rudolph was saved through molecular synthesis from a single electron.

They're quick to add that - since you're already here - they'd really appreciate your help analyzing some unusual data from the Red-Nosed reactor. You turn to check if The Historians are waiting for you, but they seem to have already divided into groups that are currently searching every corner of the facility. You offer to help with the unusual data.

The unusual data (your puzzle input) consists of many reports, one report per line. Each report is a list of numbers called levels that are separated by spaces. For example:

7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9

This example data contains six reports each containing five levels.

The engineers are trying to figure out which reports are safe. The Red-Nosed reactor safety systems can only tolerate levels that are either gradually increasing or gradually decreasing. So, a report only counts as safe if both of the following are true:

The levels are either all increasing or all decreasing.
Any two adjacent levels differ by at least one and at most three.
In the example above, the reports can be found safe or unsafe by checking those rules:

7 6 4 2 1: Safe because the levels are all decreasing by 1 or 2.
1 2 7 8 9: Unsafe because 2 7 is an increase of 5.
9 7 6 2 1: Unsafe because 6 2 is a decrease of 4.
1 3 2 4 5: Unsafe because 1 3 is increasing but 3 2 is decreasing.
8 6 4 4 1: Unsafe because 4 4 is neither an increase or a decrease.
1 3 6 7 9: Safe because the levels are all increasing by 1, 2, or 3.
So, in this example, 2 reports are safe.

Analyze the unusual data from the engineers. How many reports are safe?
*/

std::vector<std::vector<int>> DataSet;

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::vector<std::string> ExplodeString(std::string input){
    std::vector<std::string> List;
    char delimiter = ' '; // Split by space
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        List.push_back(token);
        input.erase(0, pos + 1);
    }
    List.push_back(input); // Add the last token
    return List;
}

std::vector<int> ProcessLine(std::string &input){
    std::vector<int> List;
    std::vector<std::string> s_list = ExplodeString(input);
    for(auto s = s_list.begin(); s != s_list.end(); s++) List.push_back( stoi(*s) );
    return List; 
}

void PrintVectors( std::vector<int> input ){        
    for( auto i = input.begin(); i != input.end(); i++ ) std::cout << *i << " ";
}

bool Safe(std::vector<int> input){
    PrintVectors(input);
    std::cout << " | ";

    bool Dir = false;
    auto Left = input.begin();
    auto Right = input.begin()+1;
    int c;
    
    if( *Right > *Left ) Dir = true;

    while( Right != input.end() ){

        if( ( *Right > *Left ) != Dir ) {
            std::cout << "Unsafe Dir Change.\n";   
            return false;
        }

        c = abs( *Right - *Left );
        //std::cout << c << " "; 


        if( c == 0 ) {
            std::cout << "Unsafe no change.\n";   
            return false;
        }

        if( c > 3 ) {
            std::cout << "Unsafe change.\n";   
            return false;
        }

        Left++;
        Right++; 
    }

    std::cout << "Safe\n";   
    return true;
}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                DataSet.push_back(ProcessLine(line));
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
    int count = 0;

    for( auto a = DataSet.begin(); a != DataSet.end(); a++ ){
        if(Safe(*a)) count++;
    }
    

    std::cout << "Count: " << count << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}

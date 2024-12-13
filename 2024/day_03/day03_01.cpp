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
--- Day 3: Mull It Over ---
"Our computers are having issues, so I have no idea if we have any Chief Historians in stock! 
You're welcome to check the warehouse, though," 
says the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop. 
The Historians head out to take a look.

The shopkeeper turns to you. 
"Any chance you can see why our computers are having issues again?"

The computer appears to be trying to run a program, 
but its memory (your puzzle input) is corrupted. 
All of the instructions have been jumbled up!

It seems like the goal of the program is just to multiply some numbers. 
It does that with instructions like mul(X,Y), 
where X and Y are each 1-3 digit numbers. 
For instance, mul(44,46) multiplies 44 by 46 to get a result of 2024. 
Similarly, mul(123,4) would multiply 123 by 4.

However, because the program's memory has been corrupted, 
there are also many invalid characters that should be ignored, 
even if they look like part of a mul instruction. 
Sequences like mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 ) do nothing.

For example, consider the following section of corrupted memory:
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

Only the four highlighted sections are real mul instructions. 
Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).

Scan the corrupted memory for uncorrupted mul instructions. 
What do you get if you add up all of the results of the multiplications?
*/

std::vector<std::string> DataSet;

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

std::vector<std::string> ExplodeString(std::string input, std::string delimiter = " " ) {
    std::vector<std::string> List;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        List.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    List.push_back(input); // Add the last token
    return List;
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
                DataSet.push_back(line);
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

    for( std::string s1 : DataSet ){
        std::vector<std::string> s2 = ExplodeString(s1,"mul(");
        for( std::string s3 : s2 ){
            int c_pos = s3.find_first_of(',');
            int p_pos = s3.find_first_of(')');
            if(c_pos == std::string::npos | p_pos == std::string::npos ) continue;
            std::string sA = s3.substr(0,c_pos);
            std::string sB = s3.substr(c_pos+1,p_pos-(c_pos+1));
            if( sA.length()>3 | sB.length()>3 ) continue;
            int iA = stoi(sA);
            int iB = stoi(sB);
            int iM = iA * iB;
            count += iM;
            std::cout << "A: " << iA << ", B: " << iB << " M:" << iM << "\n";
        }
    } 
    

    std::cout << "Count: " << count << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}

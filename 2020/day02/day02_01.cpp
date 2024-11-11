/*
--- Day 2: Password Philosophy ---
Your flight departs in a few days from the coastal airport; the easiest way down to the coast from here is via toboggan.

The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; we can't log in!" You ask if you can take a look.

Their password database seems to be a little corrupted: some of the passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.

To try to debug the problem, they have created a list (your puzzle input) of passwords (according to the corrupted database) and the corporate policy when that password was set.

For example, suppose you have the following list:

1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc

Each line gives the password policy and then the password. 
The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. 
For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.

In the above example, 2 passwords are valid. The middle password, cdefg, is not; it contains no instances of b, but needs at least 1. The first and third passwords are valid: they contain one a or nine c, both within the limits of their respective policies.

How many passwords are valid according to their policies?
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>
#include <chrono>
#include <ranges>
#include <vector>

class Password{
    
    public: 
    Password( std::string input ) {
        int c1,c2,c3;
        c1=input.find_first_of('-');
        c2=input.find_first_of(':');
        c3=input.find_first_of(' ');
        min=std::stoi( input.substr(0,c1) );
        max=std::stoi( input.substr(c1+1, c3-c1+1 ) );
        c = input[c2-1];
        data = input.substr(c2+2,std::string::npos);
    }

    int min=0;
    int max=0;
    char c;
    std::string data;

    bool valid(){
        int count = CharCount( c , data );
        if( count < min ) return false;
        if( count > max ) return false;
        return true;
    }
    
    private:
    int CharCount(char c,std::string input){
        int count = 0;
        for( char c2 : input ) if( c== c2) count++;
        return count;
    }

};


std::list<Password> DataSet;

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;

    try
    {
        myfile.open( filename );

        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                DataSet.push_front(Password(line));
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
    int count;

    for( Password x : DataSet ) {
        if(x.valid()) count++;
    }

    std::cout << "Count: " << count << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
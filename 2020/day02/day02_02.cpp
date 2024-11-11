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

--- Part Two ---
While it appears you validated the passwords correctly, 
they don't seem to be what the Official Toboggan Corporate Authentication System is expecting.

The shopkeeper suddenly realizes that he just accidentally explained the password policy rules from his old job at the sled rental place down the street! 
The Official Toboggan Corporate Policy actually works a little differently.

Each policy actually describes two positions in the password, where 1 means the first character, 
2 means the second character, and so on. 
(Be careful; Toboggan Corporate Policies have no concept of "index zero"!) 
Exactly one of these positions must contain the given letter. 
Other occurrences of the letter are irrelevant for the purposes of policy enforcement.

Given the same example list from above:
1-3 a: abcde is valid: position 1 contains a and position 3 does not.
1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.

How many passwords are valid according to the new interpretation of the policies?
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
        int x,y,z;
        x=input.find_first_of('-');
        y=input.find_first_of(':');
        z=input.find_first_of(' ');
        p1=std::stoi( input.substr(0,x) );
        p2=std::stoi( input.substr(x+1, z-x+1 ) );
        c = input[y-1];
        data = input.substr(y+1,std::string::npos);
        c1 = data[p1];
        c2 = data[p2];
    }

    int p1;
    int p2;
    char c, c1, c2;
    std::string data;

    bool valid(){
        if( c1 != c & c2 != c ) return false;
        if( c1 == c & c2 == c ) return false; 
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
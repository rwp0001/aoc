/*
--- Day 5: Doesn't He Have Intern-Elves For This? ---

Santa needs help figuring out which strings in his text file are naughty or nice.

A nice string is one with all of the following properties:

It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
It contains at least one letter that appears twice in a row, like xx, abcdde (dd), 
or aabbccdd (aa, bb, cc, or dd).
It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
For example:

ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), and none of the disallowed substrings.
aaa is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
jchzalrnumimnmhp is naughty because it has no double letter.
haegwjzuvuyypxyu is naughty because it contains the string xy.
dvszwmarrgswjxmb is naughty because it contains only one vowel.
How many strings are nice?
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

int CountVowels( std::string Input ){
    int Count;
    for(int i = 0; i<Input.length(); i++){
        switch(Input[i]){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                Count++;
                break;
            default:
                break;
        }
    }
    return Count;
}

int CountRepeated( std::string Input ){
    int Count = 0;
    for(int i = 0; i < Input.length()-1; i++){
        if( Input[i] == '\0' ) continue;
        if( Input[i] == Input[i+1] ) Count++;
    }
    return Count;
}

bool CalculateNice( std::string Input ){
    std::cout << "Testing: " << Input;

    // It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
    if( CountVowels(Input) <= 3 ) {
        std::cout << " - Failed vowel count.\n";    
        return false;
    }
    
    //It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
    if( CountRepeated(Input) == 0 ) {
        std::cout << " - Failed repeat count.\n";    
        return false;
    }

    // It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
    if( Input.find("ab",0) !=std::string::npos ) {
        std::cout << " - Contains ab.\n";    
        return false;
    }
    if( Input.find("cd",0) !=std::string::npos ) {
        std::cout << " - Contains cd.\n";    
        return false;
    }
    if( Input.find("pq",0) !=std::string::npos ) {
        std::cout << " - Contains pq.\n";    
        return false;
    }
    if( Input.find("xy",0) !=std::string::npos ) {
        std::cout << " - Contains xy.\n";    
        return false;
    }

    std::cout << " is Nice.\n";    
    return true;
}


void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Count;
    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                if( CalculateNice(line) ) Count++;
                //std::cout << "Count: " << Count << "\n";
            }
        } else throw( std::exception() );
        myfile.close();
        std::cout << "Count: " << Count << "\n";

    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }

}

int main()
{
    //ReadFile( "sample.txt" );
    ReadFile( "input2.txt" );
}

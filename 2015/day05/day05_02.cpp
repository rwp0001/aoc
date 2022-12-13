/*
--- Day 5: Doesn't He Have Intern-Elves For This? ---

Santa needs help figuring out which strings in his text file are naughty or nice.

A nice string is one with all of the following properties:

It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
It contains at least one letter that appears twice in a row, like xx, abcdde (dd), 
or aabbccdd (aa, bb, cc, or dd).
It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.
For example:

ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), 
and none of the disallowed substrings.
aaa is nice because it has at least three vowels and a double letter, 
even though the letters used by different rules overlap.
jchzalrnumimnmhp is naughty because it has no double letter.
haegwjzuvuyypxyu is naughty because it contains the string xy.
dvszwmarrgswjxmb is naughty because it contains only one vowel.
How many strings are nice?

--- Part Two ---

Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. 
None of the old rules apply, as they are all clearly ridiculous.

Now, a nice string is one with all of the following properties:

It contains a pair of any two letters that appears at least twice in the string without overlapping, 
like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
It contains at least one letter which repeats with exactly one letter between them, 
like xyx, abcdefeghi (efe), or even aaa.
For example:

qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly one letter between them (zxz).
xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, 
even though the letters used by each rule overlap.
uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.
How many strings are nice under these new rules?

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

int Pattern1( std::string Input ){
    // It contains a pair of any two letters that appears at least twice in the string without overlapping, 
    // like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
    int Count = 0;
    std::string tmpstr1;
    int pos;
    
    for( int i = 0; i < Input.length(); i++ ) {
        if( Input[i] == '\0' ) continue;
        tmpstr1 = Input.substr( i, 2 );
        //std::cout << tmpstr1 << " ";
        pos = Input.find( tmpstr1, i+2 );
        if( pos != std::string::npos ) Count++;
    }
    //std::cout << " Count: " << Count << " ";
    return Count;
}

int Pattern2( std::string Input ){
    // It contains at least one letter which repeats with exactly one letter between them, 
    // like xyx, abcdefeghi (efe), or even aaa.
    int Count = 0;
    for(int i = 0; i < Input.length()-2; i++){
        if( Input[i] == '\0' ) continue;
        if( Input[i] == Input[i+2] ) Count++;
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
    if( Input.find("ab",0) != std::string::npos ) {
        std::cout << " - Contains ab.\n";    
        return false;
    }
    if( Input.find("cd",0) != std::string::npos ) {
        std::cout << " - Contains cd.\n";    
        return false;
    }
    if( Input.find("pq",0) != std::string::npos ) {
        std::cout << " - Contains pq.\n";    
        return false;
    }
    if( Input.find("xy",0) != std::string::npos ) {
        std::cout << " - Contains xy.\n";    
        return false;
    }

    std::cout << " is Nice.\n";    
    return true;
}

bool CalculateNice2( std::string Input ){
    std::cout << "Testing: " << Input;
    // It contains a pair of any two letters that appears at least twice in the string without overlapping, 
    // like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
    if( Pattern1(Input) == 0 ) {
        std::cout << " - Failed Pattern 1 count.\n";    
        return false;
    }

    if( Pattern2(Input) == 0 ) {
        std::cout << " - Failed Pattern 2 count.\n";    
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
                if( CalculateNice2(line) ) Count++;
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
    //ReadFile( "sample2.txt" );
    ReadFile( "input.txt" );
}

/*
--- Day 3: Rucksack Reorganization ---

One Elf has the important job of loading all of the rucksacks with supplies for the jungle journey. 
Unfortunately, that Elf didn't quite follow the packing instructions, 
and so a few items now need to be rearranged.

Each rucksack has two large compartments. 
All items of a given type are meant to go into exactly one of the two compartments. 
The Elf that did the packing failed to follow this rule for exactly one item type per rucksack.

The Elves have made a list of all of the items currently in each rucksack (your puzzle input), 
but they need your help finding the errors. 

Every item type is identified by a single lowercase or uppercase letter 
(that is, a and A refer to different types of items).

The list of items for each rucksack is given as characters all on a single line. 
A given rucksack always has the same number of items in each of its two compartments, 
so the first half of the characters represent items in the first compartment, 
while the second half of the characters represent items in the second compartment.

For example, suppose you have the following list of contents from six rucksacks:

vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw

The first rucksack contains the items vJrwpWtwJgWrhcsFMMfFFhFp, 
which means its first compartment contains the items vJrwpWtwJgWr, 
while the second compartment contains the items hcsFMMfFFhFp. 
The only item type that appears in both compartments is lowercase p.

The second rucksack's compartments contain jqHRNqRjqzjGDLGL and rsFMfFZSrLrFZsSL. 
The only item type that appears in both compartments is uppercase L.

The third rucksack's compartments contain PmmdzqPrV and vPwwTWBwg; 
the only common item type is uppercase P.

The fourth rucksack's compartments only share item type v.

The fifth rucksack's compartments only share item type t.

The sixth rucksack's compartments only share item type s.

To help prioritize item rearrangement, every item type can be converted to a priority:

Lowercase item types a through z have priorities 1 through 26.
Uppercase item types A through Z have priorities 27 through 52.

In the above example, 
the priority of the item type that appears in both compartments of each rucksack is 
16 (p), 
38 (L), 
42 (P), 
22 (v), 
20 (t), and 
19 (s); 
the sum of these is 157.

Find the item type that appears in both compartments of each rucksack. 
What is the sum of the priorities of those item types?
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




char FindCommon( std::string S1, std::string S2 ){
    for(int i = 0; i< S1.length(); i++ ){
       if( S2.find( S1[i] ) != std::string::npos ) return S1[i];
    }
    return '\0';
}

int CalcPriority( char C ) {
    if ( C >= 'a' & C <= 'z' ) return C - 96;
    if ( C >= 'A' & C <= 'Z' ) return C - 38;
    return 0;
}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Score = 0;
    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                int l = line.length()/2;
                std::string S1 = line.substr(0,l);
                std::string S2 = line.substr(l);
                char c = FindCommon(S1,S2);
                if(c=='\0') std::cout << "Not Found. " << line << "\n";

                int p = CalcPriority(c);
                Score += p;
                std::cout <<  
                "Line: " << line << 
                " S1: " << S1 << 
                " S2: " << S2 << 
                " C: " << c <<
                " P: " << p << "\n";
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }

    //Data.sort();
    std::cout <<  "Total Score: " << Score  << "\n";
}


int main()
{
    //ReadFile( "sample.txt" );
    ReadFile( "input.txt" );
}

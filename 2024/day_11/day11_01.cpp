#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <list>

/*
--- Day 11: Plutonian Pebbles ---
The ancient civilization on Pluto was known for its ability to manipulate spacetime, 
and while the Historians explore their infinite corridors, 
you've noticed a strange set of physics-defying stones.

At first glance, 
they seem like normal stones: they're arranged in a perfectly straight line, 
and each stone has a number engraved on it.

The strange part is that every time you blink, the stones change.

Sometimes, the number engraved on a stone changes. 
Other times, a stone might split in two, 
causing all the other stones to shift over a bit to make room in their perfectly straight line.

As you observe them for a while, 
you find that the stones have a consistent behavior. 
Every time you blink, 
the stones each simultaneously change according to the first applicable rule in this list:

If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. 
The left half of the digits are engraved on the new left stone, 
and the right half of the digits are engraved on the new right stone. 
(The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
If none of the other rules apply, 
the stone is replaced by a new stone; 
the old stone's number multiplied by 2024 is engraved on the new stone.
No matter how the stones change, 
their order is preserved, 
and they stay on their perfectly straight line.

How will the stones evolve if you keep blinking at them? 
You take a note of the number engraved on each stone in the line (your puzzle input).

If you have an arrangement of five stones engraved with the numbers 0 1 10 99 999 and you blink once, 
the stones transform as follows:

The first stone, 0, becomes a stone marked 1.
The second stone, 1, is multiplied by 2024 to become 2024.
The third stone, 10, is split into a stone marked 1 followed by a stone marked 0.
The fourth stone, 99, is split into two stones marked 9.
The fifth stone, 999, is replaced by a stone marked 2021976.

So, after blinking once, 
your five stones would become an arrangement of seven stones engraved with the numbers 1 2024 1 0 9 9 2021976.

Here is a longer example:

Initial arrangement:
125 17

After 1 blink:
253000 1 7

After 2 blinks:
253 0 2024 14168

After 3 blinks:
512072 1 20 24 28676032

After 4 blinks:
512 72 2024 2 0 2 4 2867 6032

After 5 blinks:
1036288 7 2 20 24 4048 1 4048 8096 28 67 60 32

After 6 blinks:
2097446912 14168 4048 2 0 2 4 40 48 2024 40 48 80 96 2 8 6 7 6 0 3 2

In this example, after blinking six times, you would have 22 stones. 
After blinking 25 times, you would have 55312 stones!

Consider the arrangement of stones in front of you. 
How many stones will you have after blinking 25 times?
*/

//#define SAMPLE 1
#ifdef SAMPLE
    #define FILENAME "sample.txt"
#else
    #define FILENAME "input.txt"
#endif


std::list<uint_fast32_t> Stones;

std::list<uint_fast32_t> Blink(){

    std::list<uint_fast32_t> NewStones;
    for( uint_fast32_t i : Stones ){

        // If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
        if( i == 0 ) { 
            NewStones.push_back(1);
            continue;
        }

        //If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. 
        std::string s = std::to_string(i);
        int l = s.length();
        if( l % 2 == 0 ) {
            // The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. 
            // (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
            int m = s.length()/2;
            int n1 = stoi(s.substr(0,m));
            int n2 = stoi(s.substr(m,std::string::npos));
            NewStones.push_back(n1);
            NewStones.push_back(n2);
            continue;
        }

        // If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
        uint_fast32_t n = i * 2024;
        NewStones.push_back( n );

    }

    return NewStones;

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

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                std::vector<std::string> s1 = ExplodeString( line );
                for( std::string s2: s1 ) Stones.push_back(stol(s2));
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );

    for(int i = 1; i < 76; i++ ) {
        Stones = Blink();
        std::cout << i << " Stones: " << Stones.size() << " | ";
        if( i < 10 ) for(uint_fast32_t x : Stones) std::cout << x << " ";
        std::cout << std::endl;
    }

    int Count = Stones.size();
    
    std::cout << "Count: " << Count << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    #ifdef SAMPLE
    if( Count != 55312 ) throw new std::exception();
    #endif
    return 0;
}

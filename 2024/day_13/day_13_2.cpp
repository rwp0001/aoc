/*

--- Day 13: Claw Contraption ---
Next up: the lobby of a resort on a tropical island. 
The Historians take a moment to admire the hexagonal floor tiles before spreading out.

Fortunately, it looks like the resort has a new arcade! 
Maybe you can win some prizes from the claw machines?

The claw machines here are a little unusual. 
Instead of a joystick or directional buttons to control the claw, 
these machines have two buttons labeled A and B. 
Worse, you can't just put in a token and play; 
it costs 3 tokens to push the A button and 1 token to push the B button.

With a little experimentation, 
you figure out that each machine's buttons are configured to move the claw a specific amount to the right (along the X axis) 
and a specific amount forward (along the Y axis) each time that button is pressed.

Each machine contains one prize; to win the prize, 
the claw must be positioned exactly above the prize on both the X and Y axes.

You wonder: 
what is the smallest number of tokens you would have to spend to win as many prizes as possible? 
You assemble a list of every machine's button behavior and prize location (your puzzle input). 

For example:
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279

This list describes the button configuration and prize location of four different claw machines.

For now, consider just the first claw machine in the list:

Pushing the machine's A button would move the claw 94 units along the X axis and 34 units along the Y axis.
Pushing the B button would move the claw 22 units along the X axis and 67 units along the Y axis.
The prize is located at X=8400, Y=5400; 
this means that from the claw's initial position, 
it would need to move exactly 8400 units along the X axis 
and exactly 5400 units along the Y axis to be perfectly aligned with the prize in this machine.
The cheapest way to win the prize is by pushing the A button 80 times and the B button 40 times. 
This would line up the claw along the X axis (because 80*94 + 40*22 = 8400) 
and along the Y axis (because 80*34 + 40*67 = 5400). 
Doing this would cost 80*3 tokens for the A presses and 40*1 for the B presses, a total of 280 tokens.

For the second and fourth claw machines, 
there is no combination of A and B presses that will ever win a prize.

For the third claw machine, 
the cheapest way to win the prize is by pushing the A button 38 times and the B button 86 times. 
Doing this would cost a total of 200 tokens.

So, the most prizes you could possibly win is two; 
the minimum tokens you would have to spend to win all (two) prizes is 480.

You estimate that each button would need to be pressed no more than 100 times to win a prize. 
How else would someone be expected to play?

Figure out how to win as many prizes as possible. 
What is the fewest tokens you would have to spend to win all possible prizes?

To begin, get your puzzle input.

--- Part Two ---
As you go to win the first prize, you discover that the claw is nowhere near where you expected it would be. 
Due to a unit conversion error in your measurements, 
the position of every prize is actually 10000000000000 higher on both the X and Y axis!

Add 10000000000000 to the X and Y position of every prize. After making this change, the example above would now look like this:
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=10000000008400, Y=10000000005400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=10000000012748, Y=10000000012176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=10000000007870, Y=10000000006450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=10000000018641, Y=10000000010279

Now, it is only possible to win a prize on the second and fourth claw machines. 
Unfortunately, it will take many more than 100 presses to do so.

Using the corrected prize coordinates, figure out how to win as many prizes as possible. 
What is the fewest tokens you would have to spend to win all possible prizes?

*/

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

#define SAMPLE 1
#ifdef SAMPLE
    #define FILENAME "sample.txt"
    #define ANSWER 480
#else
    #define FILENAME "input.txt"
#endif

class Game {
    public:
    int Number;
    int AX;
    int AY;
    int BX;
    int BY;
    int PX,px;
    int PY,py;
    int CA = 3;
    int CB = 1;

    int Cost(){
        /*
        Pushing the machine's A button would move the claw 94 units along the X axis and 34 units along the Y axis.
        Pushing the B button would move the claw 22 units along the X axis and 67 units along the Y axis.
        
        The prize is located at X=8400, Y=5400; 
        this means that from the claw's initial position, it would need to move exactly 8400 units along the X axis 
        and exactly 5400 units along the Y axis to be perfectly aligned with the prize in this machine.
        
        The cheapest way to win the prize is by pushing the A button 80 times and the B button 40 times. 
        This would line up the claw along the X axis (because 80*94 + 40*22 = 8400) and along the Y axis (because 80*34 + 40*67 = 5400). 
        
        Doing this would cost 80*3 tokens for the A presses and 40*1 for the B presses, a total of 280 tokens.
        */
       std::cout << "Starting Game " << Number << "\n";

        int returnValue = INT_MAX;
        int ai = 0, bi = 0, ax,ay,bx,by,c,x,y;
        px = PX+10000000000000;
        py = PY+10000000000000;

        for( ; ; ai++ ) {
            bi = (BY/by) - 100;
            ax = ai * AX;
            ay = ai * AY;
            if( ax > px ) break;
            if( ai%10000000==0) std::cout << "ai: " << ai << "\n";
            for( ; ; bi++ ) {
                bx = bi*BX;
                by = bi*BY;
                x = ax + bx;
                y = ay + by;
                if( x>px || y>py ) {
                    std::cout << "Stopping ai: " << ai << " bi: " << bi << "\n";
                    break;
                }
                //if( bi%1000000==0) std::cout << "bi: " << bi << "\n";
                if( x!=px || y!=py ) continue;
                c = (ai*CA)+(bi*CB);
                std::cout << "Found at A: " << ai << " B: " << bi << " Cost: " << c << "\n"; 
                if( c < returnValue ) returnValue = c;
            }
        }

        if(returnValue == INT_MAX) {
            std::cout << "Game " << Number << " Failed.\n";
            return 0;
        }
        std::cout << "Game " << Number << " Score: " << returnValue << "\n";
        return returnValue;

    }

    bool InRange(int a,int b){
        int x = (a*AX)+(b*BX);
        int y = (a*AY)+(b*BY);
        if(x>px) return false;
        if(y>py) return false;
        return true;
    }

};

std::list<Game> DataSet;

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                int pos = 0,end = 0,i = 1;
                Game NewGame;
                NewGame.Number = i++;
                pos = line.find_first_of('X')+2;
                end = line.find(',',pos);
                NewGame.AX = std::stoi(line.substr(pos,end-pos));
                pos = line.find_first_of('Y')+2;
                end = line.length();
                NewGame.AY = std::stoi(line.substr(pos,end-pos));
                getline( myfile, line );
                pos = line.find_first_of('X')+2;
                end = line.find(',',pos);
                NewGame.BX = std::stoi(line.substr(pos,end-pos));
                pos = line.find_first_of('Y')+2;
                end = line.length();
                NewGame.BY = std::stoi(line.substr(pos,end-pos));
                getline( myfile, line );
                pos = line.find_first_of('X')+2;
                end = line.find(',',pos);
                NewGame.PX = std::stoi(line.substr(pos,end-pos));
                pos = line.find_first_of('Y')+2;
                end = line.length();
                NewGame.PY = std::stoi(line.substr(pos,end-pos));
                getline( myfile, line );
                DataSet.push_back(NewGame);
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

    int Count = 0;

    for ( Game game : DataSet ) Count += game.Cost();
    
    std::cout << "Count: " << Count << "\n";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds\n";

    #ifdef SAMPLE
    if( Count != ANSWER ) throw new std::exception();
    #endif
    return 0;
}
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <exception>

/* --- Day 4: Giant Squid ---
You're already almost 1.5km (almost a mile) below the surface of the ocean, 
already so deep that you can't see any sunlight. What you can see, however, 
is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. 
Numbers are chosen at random, and the chosen number is marked on all boards 
on which it appears. (Numbers may not appear on all boards.) If all numbers 
in any row or any column of a board are marked, that board wins. (Diagonals 
don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and 
the giant squid) pass the time. It automatically generates a random order
in which to draw numbers and a random set of boards (your puzzle input).

--- Part Two ---
On the other hand, it might be wise to try a different strategy: let the giant squid win.

You aren't sure how many bingo boards a giant squid could play at once, 
so rather than waste time counting its arms, the safe thing to do is to figure out 
which board will win last and choose that one. That way, no matter which boards 
it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after 13 
is eventually called and its middle column is completely marked. If you were to 
keep playing until this point, the second board would have a sum of unmarked numbers 
equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?
*/

class Board{
    public:
    std::array<std::array<int,5>,5> Data;
    static std::list<int> CalledNumbers;

    static bool NumberCalled(int Number){
        for (auto it = Board::CalledNumbers.begin() ; it !=  Board::CalledNumbers.end(); it++) if(Number == *it) return true;
        return false;
    }

    Board(std::list<int> Numbers){
        if(Numbers.size() != 25) throw(std::exception());
        auto it = Numbers.begin();
        int x = 0;
        int y = 0;

        while(it != Numbers.end()){
            Data[x][y] = *it;
            y++;
            if(y>4){
                y=0;
                x++;
            }
            it++;
        }
    }
    Board(){}

    static void Call(int Number){
         Board::CalledNumbers.push_back(Number);
    }
    

    bool Winner(){
        bool value = false;
        // test rows
        for(int x = 0; x < 5; x++){
            value =  NumberCalled(Data[x][0]) & NumberCalled(Data[x][1]) & NumberCalled(Data[x][2]) & NumberCalled(Data[x][3]) & NumberCalled(Data[x][4]);
            if(value) return true;
            value =  NumberCalled(Data[0][x]) & NumberCalled(Data[1][x]) & NumberCalled(Data[2][x]) & NumberCalled(Data[3][x]) & NumberCalled(Data[4][x]);
            if(value) return true;
        }
        return false;
    }

    int Sum(){
        int returnValue;
        for(int x = 0; x<5; x++){
            for(int y = 0; y<5; y++){
                if(!NumberCalled(Data[x][y])) returnValue += Data[x][y]; 
            }
        }
        return returnValue;
    }

    void Print(){
        // cout << "\033[1;31mbold red text\033[0m\n";
        /*          foreground background
        black        30         40
        red          31         41
        green        32         42
        yellow       33         43
        blue         34         44
        magenta      35         45
        cyan         36         46
        white        37         47

        reset             0  (everything back to normal)
        bold/bright       1  (often a brighter shade of the same colour)
        underline         4
        inverse           7  (swap foreground and background colours)
        bold/bright off  21
        underline off    24
        inverse off      27
        */


        for(int x = 0; x<5; x++){
            for(int y = 0; y<5; y++){
                //if(NumberCalled(Data[x][y])) std::cout << "\033[1;7";
                std::cout.width(3);
                std::cout << Data[x][y];
                //std::cout << "\033[1;0";
            }
            std::cout << "\n";
        }
    }
};

std::list<int> ReadDraws(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    std::list<int> ReturnValue;

    try
    {
        if (myfile.is_open()){
            // get the draw order.
            getline(myfile, line);    
        } else throw(std::exception());
        myfile.close();

        std::stringstream          lineStream(line);
        std::string                draw;

        while(std::getline(lineStream,draw, ',')) ReturnValue.push_back(std::stoi(draw));
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return ReturnValue;
  
};

std::list<Board> ReadCards(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    std::list<Board> ReturnValue;

    try
    {
        if (myfile.is_open()){
            // skip the draw order. 
            getline(myfile, line);
       
            while(!myfile.eof()){
                std::list<int> Numbers;
                getline(myfile, line); // blank line.
                
                for(int r =0; r<5; r++){
                    getline(myfile, line);
                    for(int c = 0; c<5; c++){
                        std::string str = line.substr(c*3,2);
                        int value = std::stoi(str);
                        Numbers.push_back(value);
                    }    
                } 
                ReturnValue.push_back(Board(Numbers));
            }

        } else throw(std::exception());
        myfile.close();

        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return ReturnValue;
  
};

std::list<int> Board::CalledNumbers =  std::list<int>();
    

int main()
{
    std::string fileName = "input.txt";
    std::list<Board> Cards = ReadCards(fileName);
    std::list<int> Draws = ReadDraws(fileName); 
    Board Winner;
    int LastCall;
    bool WinnerFound = false;

    for (auto it = Draws.begin() ; it != Draws.end(); it++) {
        Board::Call(*it);
        for (auto card = Cards.begin() ; card != Cards.end(); card++) {
            Board thiscard = *card;
            if(thiscard.Winner()){
                Winner = *card;
                if(Cards.size() > 1){
                    Cards.erase(card);
                    card = Cards.begin();
                } else if( Cards.size() == 1 ) {
                    LastCall = *it;
                    WinnerFound = true;
                    break;
                } 
            }
        }
        if(WinnerFound) break;
    }

    Winner.Print();

    std::cout << "Last Draw: " << LastCall << " Sum: " << Winner.Sum() << "\n";
    std::cout << "Answer: " << LastCall * Winner.Sum() << "\n";

    return 0;

}








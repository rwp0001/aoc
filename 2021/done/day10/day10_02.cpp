/*
--- Part Two ---

Now, discard the corrupted lines. The remaining lines are incomplete.

Incomplete lines don't have any incorrect characters - instead, they're missing some closing characters at the end of the line. To repair the navigation subsystem, you just need to figure out the sequence of closing characters that complete all open chunks in the line.

You can only use closing characters (), ], }, or >), and you must add them in the correct order so that only legal pairs are formed and all chunks end up closed.

In the example above, there are five incomplete lines:

[({(<(())[]>[[{[]{<()<>> - Complete by adding }}]])})].
[(()[<>])]({[<{<<[]>>( - Complete by adding )}>]}).
(((({<>}<{<{<>}{[]{[]{} - Complete by adding }}>}>)))).
{<[[]]>}<{[{[{[]{()[[[] - Complete by adding ]]}}]}]}>.
<{([{{}}[<[[[<>{}]]]>[]] - Complete by adding ])}>.
Did you know that autocomplete tools also have contests? It's true! The score is determined by considering the completion string character-by-character. Start with a total score of 0. Then, for each character, multiply the total score by 5 and then increase the total score by the point value given for the character in the following table:

): 1 point.
]: 2 points.
}: 3 points.
>: 4 points.
So, the last completion string above - ])}> - would be scored as follows:

Start with a total score of 0.
Multiply the total score by 5 to get 0, then add the value of ] (2) to get a new total score of 2.
Multiply the total score by 5 to get 10, then add the value of ) (1) to get a new total score of 11.
Multiply the total score by 5 to get 55, then add the value of } (3) to get a new total score of 58.
Multiply the total score by 5 to get 290, then add the value of > (4) to get a new total score of 294.
The five lines' completion strings have total scores as follows:

}}]])})] - 288957 total points.
)}>]}) - 5566 total points.
}}>}>)))) - 1480781 total points.
]]}}]}]}> - 995444 total points.
])}> - 294 total points.
Autocomplete tools are an odd bunch: the winner is found by sorting all of the scores and then taking the middle score. (There will always be an odd number of scores to consider.) In this example, the middle score is 288957 because there are the same number of scores smaller and larger than it.

Find the completion string for each incomplete line, score the completion strings, and sort the scores. What is the middle score?

Your puzzle answer was 3662008566.
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

std::list<std::string> Data;

bool Validate(std::string Input){
    std::string Open =  "([{<";
    std::string Close = ")]}>";
    std::list<char> Stack;
    char error = '!';

    for(int i = 0; i < Input.length(); i++ ){
        if( Open.find(Input[i]) != std::string::npos ) { // Handle open chars
            Stack.push_back(Input[i]);
            continue;
        }

        switch (Input[i])
        {
        case ')':
            if( Stack.back() == '(' ){
                Stack.pop_back();
                continue;
            } else {
                error = Input[i];  
            }
            break;
        case ']':
            if( Stack.back() == '[' ) {
                Stack.pop_back();
                continue;
            } else {
                    error = Input[i];  
            }
            break;
        case '}':
            if( Stack.back() == '{' ) {
                Stack.pop_back();
                continue;
            } else {
                error = Input[i];  
            }
            break;
        case '>':
            if( Stack.back() == '<' ) {
                Stack.pop_back();
            continue;
            } else {
                error = Input[i];  
            }
            break;        
        default:
            error = Input[i];
            break;
        }
        if( error != '!' ) break;
    }

    switch (error)
    {
    case '!':
        return false;
        break;
    case ')':
    case ']':
    case '}':
    case '>':
        return true;
        break;
    default:
        throw(std::exception());
        break;
    }
}

std::string Correction(std::string Input){
    std::string Open =  "([{<";
    std::string Close = ")]}>";
    std::list<char> Stack;
    char error = '!';

    for(int i = 0; i < Input.length(); i++ ){
        if( Open.find(Input[i]) != std::string::npos ) { // Handle open chars
            Stack.push_back(Input[i]);
            continue;
        }

        switch (Input[i])
        {
        case ')':
            if( Stack.back() == '(' ){
                Stack.pop_back();
                continue;
            } else {
                error = Input[i];  
            }
            break;
        case ']':
            if( Stack.back() == '[' ) {
                Stack.pop_back();
                continue;
            } else {
                    error = Input[i];  
            }
            break;
        case '}':
            if( Stack.back() == '{' ) {
                Stack.pop_back();
                continue;
            } else {
                error = Input[i];  
            }
            break;
        case '>':
            if( Stack.back() == '<' ) {
                Stack.pop_back();
            continue;
            } else {
                error = Input[i];  
            }
            break;        
        default:
            error = Input[i];
            break;
        }
        if( error != '!' ) throw(std::exception());
    }

    std::string returnValue;
    Stack.reverse();

    for( auto it = Stack.begin(); it != Stack.end(); it++ ){
        switch (*it)
        {
        case '(':
            returnValue += ')';
            break;
        case '[':
            returnValue += ']';
            break;
        case '{':
            returnValue += '}';
            break;
        case '<':
            returnValue += '>';
            break;
        default:
            break;
        }
    }

    return returnValue;
   
}

unsigned long long int ScoreLine( std::string Input ){
    unsigned long long int returnValue = 0;
    for(int i = 0; i < Input.length(); i++ ){
        
        returnValue *= 5;
        
        switch (Input[i])
        {
        case ')':
            returnValue += 1;
            break;
        case ']':
            returnValue += 2;
            break;
        case '}':
            returnValue += 3;
            break;
        case '>':
            returnValue += 4;
            break;
        default:
            break;
        }
    
    }
    return returnValue;
}

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    int Count = 0;
    int Score = 0;
    try
    {
        if (myfile.is_open()){
            std::string c;
            while (getline(myfile, line)){
                if( Validate(line) ) continue;
                Data.push_back(line);
                Count++;
            }
            std::cout << "Count: " << Count << " Score: " << Score << "\n";
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
}

int main(){
    ReadFile("input.txt");
    std::string Value;
    int Score = 0;
    std::list<unsigned long long int> Scores;

    for( auto it = Data.begin(); it != Data.end(); it++ ){
        Value = Correction(*it);
        unsigned long long int ThisScore = ScoreLine(Value); 
        std::cout << "Line: "<< *it << " -- " << Value << " Score: " << ThisScore << "\n";
        Scores.push_back(ThisScore);
    }

    Scores.sort();
    int a = Scores.size()/2;
    auto it = Scores.begin();
    for( int i = 0; i < a; i++) it++;
    std::cout << "Score: " << *it << "\n";
    return 0;
}
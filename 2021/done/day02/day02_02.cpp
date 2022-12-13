// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include <vector>   //for std::vector
using namespace std;

int main()
{
    string line;
    ifstream myfile("input.txt");
    string space_delimiter = " ";
    
    int Data[1000];
    char Direction[1000];

    if (myfile.is_open())
    {
        int Index = 0;
        while (getline(myfile, line))
        {
            Direction[Index] = line[0];
            std::size_t found = line.rfind(space_delimiter);
            Data[Index] = stoi(line.substr(found,string::npos));
            cout << Index << ": " << Direction[Index] << " " << Data[Index] << "\n";
            Index++;
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file";
        return 1;
    }

    int horizontal =0;
    int depth =0;
    int aim = 0;

    for(int i=0; i<1000; i++){
        switch ( Direction[i] )
        {
        case 'f':
            horizontal += Data[i];
            depth += aim * Data[i];
            break;
        
        case 'u':
            aim -= Data[i];
            break;

        case 'd':
            aim += Data[i];
            break;

        default:
            break;
        }

        cout << i << ": Horz: " << horizontal << " Depth: " << depth << " Aim: " << aim << '\n';
    }

    cout << "Answer: " << horizontal * depth << "\n";
    return 0;   
}

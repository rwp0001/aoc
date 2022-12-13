// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string line;
    ifstream myfile("day01_01_input.txt");

    bool firstlinedone = false;
    int increments = 0;
    int CurrentNumber = 0;
    int LastNumber = 0;
    
    int Data[2000];

    if (myfile.is_open())
    {
        int Index = 0;
        while (getline(myfile, line))
        {
            Data[Index] = stoi(line);
            Index++;
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";


for(int i=2; i<2000; i++){
    CurrentNumber = Data[i-2] + Data[i-1] + Data[i]; 

    if( firstlinedone ){
            if( CurrentNumber > LastNumber ) increments++;   
            LastNumber = CurrentNumber;
    } else {    
            LastNumber = CurrentNumber;
            firstlinedone = true;
    }

    cout << i << ": " << Data[i-2] << " - " << Data[i-1] << " - " << Data[i] << " Sum: " << CurrentNumber << '\n';
}
    cout << " Total: " << increments << '\n';

    return 0;
}
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile ("day01_01_input.txt");

  bool firstlinedone = false;
  int increments = 0;  
  int LastNumber = 0;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        int CurrentNumber = stoi(line);
        //cout << line << '\n';
        
        if( firstlinedone ){
            if( CurrentNumber > LastNumber ) increments++;   
            LastNumber = CurrentNumber;
        } else {
        
            LastNumber = stoi(line);
            firstlinedone = true;
        }

        cout << "Current Number Found: " << line << " - Count: " << increments << '\n';



    }
    myfile.close();

    cout << " Total: " << increments << '\n';
  }

  else cout << "Unable to open file"; 

  return 0;
}
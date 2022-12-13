// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include <vector>   //for std::vector
#include <array>

using namespace std;

int main()
{
    std::string line;
    ifstream myfile("input.txt");
    std::string space_delimiter = " ";
    
    int gamma =0;
    int epsilon =0;
    std::array<int,12> One;
    std::array<int,12> Zero;
    
    One.fill(0);
    Zero.fill(0);


    if (myfile.is_open())
    {
        int Index = 0;
        while (getline(myfile, line))
        {
            for(int i = 0; i<12; i++){
                int Value = stoi(line.substr(i,1));
                switch (Value)
                {
                case 0:
                    Zero[i]++;
                    break;
                case 1:
                    One[i]++;

                default:
                    break;
                }
            }
            cout << Index << ": "  << line << "\n";
            Index++;
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file";
        return 1;
    }

    cout << "Ones:  "; 
    for(int i = 0; i<12;i++){
        cout << One[i] << " ";    
    }
    cout << "\n";

    cout << "Zeros: "; 
    for(int i = 0; i<12;i++){
        cout << Zero[i] << " ";    
    }
    cout << "\n";

    std::string gamma_str;
    std::string epsilon_str;

    for(int i = 0; i<12;i++){
        if(One[i]>Zero[i]){
            gamma_str.append("1");
            epsilon_str.append("0");
        } else {
            gamma_str.append("0");
            epsilon_str.append("1");
        }
    }

    gamma = stoi(gamma_str, 0, 2);
    epsilon = stoi(epsilon_str, 0, 2);

    cout << "Gamma: " << gamma_str << " Epsilon: " << epsilon_str << "\n";
    cout << "Gamma: " << gamma << " Epsilon: " << epsilon << "\n";
    cout << "Answer: " << gamma * epsilon << "\n";
    return 0;   
}

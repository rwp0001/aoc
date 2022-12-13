#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <array>
#include <stdexcept>

class sevenSegment {
    private:
    std::string str_key;
    std::string str_value;
    std::string intLookupTable[10];
    
    std::string Unique_chars(std::string a, std::string b){
        std::string returnValue = "";
        a.append(b);
        std::list<char> list;
        for(int c = 0;c<a.length();c++) list.push_back(a[c]);
        list.sort();
        list.unique();
        for (auto it = list.begin(); it !=  list.end(); it++) returnValue += *it;
        return returnValue;
    }

    std::string Sort_chars(std::string a){
        std::string returnValue = "";
        std::list<char> list;
        for(int c = 0;c<a.length();c++) list.push_back(a[c]);
        list.sort();
        for (auto it = list.begin(); it !=  list.end(); it++) returnValue += *it;
        return returnValue;
    }

    std::string Common_chars(std::string a, std::string b){
        std::string returnValue = "";
        if(b.length()>a.length()){
            returnValue = a;
            a = b;
            b = returnValue;
            returnValue = "";
        }
        for(int c = 0; c<a.length();c++) if(  b.find( a[c] ) != std::string::npos ) returnValue += a[c];
        return returnValue;
    }

    void Calculate(){
        /*

         aaa    a - 0 *     
        b   c   b - 1 
        b   c   c - 2 
         ddd    d - 3 
        e   f   e - 4 
        e   f   f - 5 
         ggg    g - 6 

        int - len
         0  -  6 
         1  -  2 *
         2  -  5 
         3  -  5 *
         4  -  4 *
         5  -  5 
         6  -  6 
         7  -  3 *
         8  -  7 *
         9  -  8 *

        */

        // 1,4,7,8
        std::string keys[4];
        std::stringstream lineStream1(str_key);
        int Index = 0;

        while(std::getline(lineStream1,keys[0], ' ')) {
            switch (keys[0].length())
            {
            case 2:
                intLookupTable[1] = keys[0];
                break;
            case 3:
                intLookupTable[7] = keys[0];
                break;
            case 4:
                intLookupTable[4] = keys[0];
                break;
            case 7:
                intLookupTable[8] = keys[0];
                break;             
            default:
                break;
            }
        }

        // load 6 segments
        Index = 1;
        std::stringstream lineStream3(str_key);
        while(std::getline(lineStream3,keys[0], ' ')) {
            switch (keys[0].length())
            {
            case 6:
                keys[Index] = keys[0]; // load array with possibles;
                Index++;
                break;             
            default:
                break;
            }
        }

        // 9
        keys[0] = intLookupTable[4]; // load 4
        for(int i = 1; i<4; i++) {
            std::string a = Common_chars(keys[i],keys[0]);
            if(a.length() == keys[0].length() ){ 
                intLookupTable[9] = keys[i];
                keys[i] = "";
                break;
            }    
        }

        // 0
        keys[0] = intLookupTable[7]; // load 7 
        for(int i = 1; i<4; i++) {
            std::string a = Common_chars(keys[i],keys[0]);
            if(a.length() == keys[0].length() ){ 
                intLookupTable[0] = keys[i];
                keys[i] = "";
                break;
            }
        }


        // 6
        for(int i = 1; i<4; i++) if( keys[i].length() > 1) intLookupTable[6] = keys[i];

        // load 5 segments
        Index = 1;
        std::stringstream lineStream2(str_key);
        while(std::getline(lineStream2,keys[0], ' ')) {
            switch (keys[0].length())
            {
            case 5:
                keys[Index] = keys[0]; // load array with possibles;
                Index++;
                break;             
            default:
                break;
            }
        }

        // 3
        keys[0] = intLookupTable[1]; // load 1 
        for(int i = 1; i<4; i++) {
            std::string a = Common_chars(keys[i],keys[0]);

            if(a.length() == keys[0].length() ){ 
                intLookupTable[3] = keys[i];
                keys[i] = "";
                break;
            }
        }

        // 5
        keys[0] =  intLookupTable[9]; // load 9 
        for(int i = 1; i<4; i++) {
            std::string a = Common_chars(keys[i],keys[0]);
            if(a.length()+1 == keys[0].length() ){ 
                intLookupTable[5] = keys[i];
                keys[i] = "";
                break;
            }
        }

        // 2
        for(int i = 1; i<4; i++) if( keys[i].length() > 1) intLookupTable[2] = keys[i];

        // sort keys
        for(int i = 0; i<10; i++) intLookupTable[i] = Sort_chars(intLookupTable[i]);
    }

    int DecodeString(std::string Input){
        for(int i = 0; i<10; i++) {
            if( Input == intLookupTable[i] ) {
                return i;
            }
        }
        return -1;
    }

    int answer(){
        int Decoded[4];

        std::string key;
        std::stringstream lineStream1(str_value);
        int Index = 0;
        while(std::getline(lineStream1,key, ' ')) {
            Decoded[Index] = DecodeString(Sort_chars(key));
            Index++;
        }
        
        int returnValue = Decoded[3];
        returnValue += Decoded[2] * 10;
        returnValue += Decoded[1] * 100;
        returnValue += Decoded[0] * 1000;
        return returnValue;
    }

    public:
    static int Sum;

    int Value;
    sevenSegment(std::string Input){
        int c = Input.find_first_of("|");
        str_key = Input.substr(0,c-1);
        str_value = Input.substr(c+2,std::string::npos);
        std::stringstream lineStream(str_value);
        Calculate();
        Value = answer();
        Sum += Value;

        std::cout << "Keys: ";
        for(int i = 0; i<10; i++) {
            std::cout.width(9);
            std::cout << intLookupTable[i]; 
        }
        std::cout << "    Value: ";
        std::cout.width(5);
        std::cout << Value; 
        std::cout << " Sum: " << Sum << "\n";
    }
};

std::list<sevenSegment> Data;

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile(filename);
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while (getline(myfile, line)){
                Data.push_back(sevenSegment(line));
                Count++;
            }
            std::cout << "Count: " << Count << "\n";
        } else throw(std::exception());
        myfile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
  
};

int sevenSegment::Sum = 0;

int main(){
    ReadFile("input.txt");
    return 0;
}
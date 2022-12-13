#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>

#define DISPLAY_PRECISION 2

class Position {
  
    public:
    double X = 0.0;
    double Y = 0.0;
    double Z = 0.0;

    Position(){
        X = 0;
        Y = 0;
        Z = 0;
    }

    Position( double x, double y, double z ){
        X = x;
        Y = y;
        Z = z;
    }

    Position(std::string Input){
        if( Input.length() == 0 ) throw std::exception();
        std::stringstream lineStream(Input);
        std::string item;
        int Count = 0;
        while( std::getline( lineStream, item, ',' ) ) {
            switch ( Count )
            {
            case 0:
                X = std::stoi( item );
                Count++;
                break;
            case 1:
                Y = std::stoi( item );
                Count++;
                break;
            case 2:
                Z = std::stoi( item );
                Count++;
                break;            
            default:
                break;
            }
        }
    }

    double distance(Position P) { return std::sqrt( std::pow( P.X - X, 2) + std::pow( P.Y - Y, 2) + std::pow( P.Z - Z, 2) * 1.0); }
    
    constexpr  bool operator> ( const Position &rhs){
        if ( *this == rhs ) return false;
        if ( X < rhs.X ) return false;
        if ( X == rhs.X & Y < rhs.Y ) return false;
        if ( X == rhs.X & Y == rhs.Y & Z < rhs.Z ) return false;
        return true;
    }

    constexpr  bool operator< ( const Position &rhs){
        if ( *this == rhs ) return false;
        if ( X > rhs.X ) return false;
        if ( X == rhs.X & Y > rhs.Y ) return false;
        if ( X == rhs.X & Y == rhs.Y & Z > rhs.Z ) return false;
        return true;
    }

    constexpr  bool operator== ( const Position &rhs){ 
        if ( X != rhs.X ) return false;
        if ( Y != rhs.Y ) return false;
        if ( Z != rhs.Z ) return false;
        return true;
    }

    constexpr  bool operator!= ( const Position &rhs){ 
        return !operator==(rhs);
    }

    Position operator+ ( const Position &rhs ){ 
        Position returnValue( rhs );
        returnValue.X = returnValue.X + X;
        returnValue.Y = returnValue.Y + Y;
        returnValue.Z = returnValue.Z + Z;
        return returnValue;
    }
    Position operator- ( const Position &rhs ){ 
        Position returnValue( rhs );
        returnValue.X = X - returnValue.X;
        returnValue.Y = Y - returnValue.Y;
        returnValue.Z = Z - returnValue.Z;
        return returnValue;
    }

    friend std::ostream& operator << (std::ostream &s, const Position &p){
        s << "X: ";     
        s << std::setw( DISPLAY_PRECISION + 3);
        s.precision(DISPLAY_PRECISION);
        s << std::fixed;
        s << std::setw(8);
        s << p.X;
        s << ", Y: ";
        s << std::setw( DISPLAY_PRECISION + 3);
        s.precision(DISPLAY_PRECISION);
        s << std::fixed;
        s << std::setw(8);
        s << p.Y;
        s << ", Z: ";
        s << std::setw( DISPLAY_PRECISION + 3);
        s.precision(DISPLAY_PRECISION);
        s << std::fixed;
        s << std::setw(8);
        s << p.Z;
        return s; 
    }

    int Manhattan( Position P ){
        P  = *this - P;
        return std::abs(P.X)+std::abs(P.Y)+std::abs(P.Z);
    } 

    //if( P1 == P2 ) std::cout << P1.toString() <<" == "<< P2.toString() << "\n";
    //if( P1 != P2 ) std::cout <<  P1.toString() <<" != "<< P2.toString() << "\n";
    //if( P1 < P2 ) std::cout <<  P1.toString() <<" <  "<< P2.toString() << "\n";
    //if( P1 > P2 ) std::cout <<  P1.toString() <<" >  "<< P2.toString() << "\n";

};


int main(){
    std::list<Position> Data;

    Data.push_back( Position(  108,-1254,  -76));
    Data.push_back( Position(-1155,-1259,   -2));
    Data.push_back( Position(  101,-1192,-1169));
    Data.push_back( Position(   41,-1150, 1244));
    Data.push_back( Position(-1007,-1211, 1138));
    Data.push_back( Position(   94,-1150,-2517));
    Data.push_back( Position(   84,-1142, 2403));
    Data.push_back( Position(-2255,-1123,  -11));
    Data.push_back( Position( 1222,-1292, 1106));
    Data.push_back( Position(   42,  -84, 1161));
    Data.push_back( Position(   59, 1202, 1119));
    Data.push_back( Position( 1248,  -92, 1150));
    Data.push_back( Position( 1226, 1228, 1133));
    Data.push_back( Position( 1337,-2482, 1108));
    Data.push_back( Position( 1380,-1177, 2341));
    Data.push_back( Position(  147,-2303,-2414));
    Data.push_back( Position( 2528,-2466, 1184));
    Data.push_back( Position(   63,-2422, 2442));
    Data.push_back( Position( 3650,-2428, 1199));
    Data.push_back( Position( 2512,  -32, 1212));
    Data.push_back( Position( 1386, 1215,   23));
    Data.push_back( Position( 1359,-2363, 2386));
    Data.push_back( Position( 1219, 2450, 1192));
    Data.push_back( Position( 3788,-1230, 1220));
    Data.push_back( Position( 1274, 2314, -144));
    Data.push_back( Position( 1316, 3662, 1082));
    Data.push_back( Position(    0,    0,    0));

    int Score = 0;

    for( Position P1 : Data ){
        for( Position P2 : Data ){
            int s = P1.Manhattan(P2);
            if( s == 0) continue;
            if( s > Score ) Score = s;
            std::cout << P1 << " - " << P2 << " Score: " << s << "\n";
        }
    }

    std::cout << "Score: "<< Score << "\n";

    std::cout <<  "\n";
    return 0;
}




/*
--- scanner 2 ---     108,-1254,  -76
--- scanner 8 ---   -1155,-1259,   -2
--- scanner 10 ---    101,-1192,-1169
--- scanner 12 ---     41,-1150, 1244
--- scanner 15 ---  -1007,-1211, 1138
--- scanner 18 ---     94,-1150,-2517
--- scanner 19 ---     84,-1142, 2403
--- scanner 24 ---  -2255,-1123,  -11
--- scanner 25 ---   1222,-1292, 1106
--- scanner 26 ---     42,  -84, 1161
--- scanner 4 ---      59, 1202, 1119
--- scanner 5 ---    1248,  -92, 1150
--- scanner 6 ---    1226, 1228, 1133
--- scanner 7 ---    1337,-2482, 1108
--- scanner 13 ---   1380,-1177, 2341
--- scanner 14 ---    147,-2303,-2414
--- scanner 16 ---   2528,-2466, 1184
--- scanner 17 ---     63,-2422, 2442
--- scanner 21 ---   3650,-2428, 1199
--- scanner 22 ---   2512,  -32, 1212
--- scanner 23 ---   1386, 1215,   23
--- scanner 1 ---    1359,-2363, 2386
--- scanner 3 ---    1219, 2450, 1192
--- scanner 9 ---    3788,-1230, 1220
--- scanner 11 ---   1274, 2314, -144
--- scanner 20 ---   1316, 3662, 1082
--- scanner 0 ---       0,    0,    0
*/
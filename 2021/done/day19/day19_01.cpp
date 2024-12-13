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
#include <chrono>

#define DISPLAY_PRECISION 2

#define MAX_RANGE 1000
//#define MIN_MATCHES 3
#define MIN_MATCHES 12

//#define FILENAME "sample2.txt"
//#define FILENAME "sample.txt"
#define FILENAME "input.txt"

class Position {
  
    public:
    int X = 0;
    int Y = 0;
    int Z = 0;

    constexpr bool operator> ( const Position &rhs ) const {
        //if ( *this == rhs ) return false;
        if ( X < rhs.X ) return false;
        if ( X == rhs.X & Y < rhs.Y ) return false;
        if ( X == rhs.X & Y == rhs.Y & Z < rhs.Z ) return false;
        return true;
    }

//bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}
    bool operator() ( const Position &lhs, const Position &rhs ) const { return lhs > rhs; }

    constexpr bool operator< ( const Position &rhs ) {
        //if ( *this == rhs ) return false;
        if ( X > rhs.X ) return false;
        if ( X == rhs.X & Y > rhs.Y ) return false;
        if ( X == rhs.X & Y == rhs.Y & Z > rhs.Z ) return false;
        return true;
    }

    constexpr  bool operator== ( const Position &rhs ) { 
        if ( X != rhs.X ) return false;
        if ( Y != rhs.Y ) return false;
        if ( Z != rhs.Z ) return false;
        return true;
    }

    //bool operator()( const Position & lhs, const Position & rhs ) const { return lhs == rhs; }

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
        s << std::fixed;
        s << std::setw(5);
        s << p.X;
        s << ", Y: ";
        s << std::fixed;
        s << std::setw(5);
        s << p.Y;
        s << ", Z: ";
        s << std::fixed;
        s << std::setw(5);
        s << p.Z;
        return s; 
    }

    Position(){
        X = 0;
        Y = 0;
        Z = 0;
    }

    Position( int x, int y, int z ){
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

};

class Scanner{
    public:
    std::string Name;
    Position Location;
    std::list<Position> RotationsArray[24];
    std::list<double> BeaconDistances;
    bool Found = false;
    int Rotation = 0;

    friend std::ostream& operator << (std::ostream &s, const Scanner &S){
        s << "Scanner: " << S.Name << " with " << S.RotationsArray[0].size() << " Beacons at " << S.Location << " and Rotation: " << S.Rotation;
        return s;
    }
    
    Scanner operator+= ( const Scanner &rhs ){
        Scanner returnValue = *this;
        Scanner S2 = rhs;
        for( Position P1 : S2.Beacons() ) {
            if( returnValue.BeaconAtPos( P1 ) ) continue;
            returnValue.AddBeacon(P1);
            std::cout << "Added Beacon at " << P1 << "\n";
        }
        return returnValue;
    }

    bool operator== ( const Scanner &rhs ){
        if( Name != rhs.Name ) return false;
        if( Location != rhs.Location ) return false;
        if( Rotation != rhs.Rotation ) return false;
        if( RotationsArray[0].size() != rhs.RotationsArray[0].size() ) return false;
        //for( Position P1 : rhs.Beacons() ) if ( !BeaconAtAbsPos( P1 ) ) return false;
        return true;
    }

    std::list<Position> Beacons(){ 
        std::list<Position> returnValue = std::list<Position>();
        for( Position P1 : RotationsArray[Rotation] ) returnValue.push_back( Offset( P1 ) );
        //returnValue.sort();
        return returnValue;
    }

    void AddBeacon( Position Input ){ 
        CalcBeaconRotations(Input);
        CalcBeaconDistances();
    }
    void AddBeacon( std::string Input ){ 
        CalcBeaconRotations(Input);
        CalcBeaconDistances();
    }
   
    /// @brief 
    Scanner(){}

    Scanner( std::string Input ){
        Name = Input;
    }

    ~Scanner(){}

    bool BeaconAtPos( Position Input ){
        for(Position P1 : Beacons() ) if( Input == P1 ) return true;
        return false;   
    }

    bool BeaconAtAbsPos( Position Input ){
        for(Position P1 : RotationsArray[0] ) if( Input == P1 ) return true;
        return false;   
    }

    std::list<Position> BeaconAbsAtDistance( double d ){
        std::list<Position> returnValue = std::list<Position>();
        for( Position P1 : RotationsArray[Rotation] ) for( Position P2 : RotationsArray[Rotation] ) if ( P1.distance( P2 ) == d ) returnValue.push_back(P1);
        //returnValue.sort();
        //returnValue.unique();
        return returnValue;
    }

    std::list<Position> BeaconAtDistance( double d ){
        std::list<Position> returnValue = std::list<Position>();
        for( Position P1 : Beacons() ) for( Position P2 : Beacons() ) if ( P1.distance( P2 ) == d ) returnValue.push_back(P1);
        returnValue.sort();
        returnValue.unique();
        return returnValue;
    }

    bool ContainsDistance( double Input ){
        for(double d : BeaconDistances ) if( Input == d ) return true;
        return false;
    }

    int SameDistanceCount( Scanner S ){
        int Count = 0;
        for(auto it = BeaconDistances.begin(); it != BeaconDistances.end(); it++ ) if(S.ContainsDistance(*it)) Count++;
        return Count;
    }
    
    static std::string PrintBeacons( std::list<Position> Data ){
        std::ostringstream returnValue;
        int Count = 1;
        for( Position P1 : Data ) returnValue << "Beacon: " << std::setw(4) << Count++ << "  |  " << P1 <<"\n";
        return returnValue.str();
    }
   
    bool CalculateOffset( Scanner KnownScanner ){  
        //Position Starting = Location;
        //bool Found = false;
        //std::cout << "Comparing " << Name << " to " << KnownScanner.Name << "\n";
        auto start = std::chrono::high_resolution_clock::now();
        for( double d : BeaconDistances ) {
            if( !KnownScanner.ContainsDistance(d) ) continue;
            for ( Position P1 : KnownScanner.BeaconAtDistance(d) ) {
                for (int iR = 0; iR < 24; iR++) {
                    Rotation = iR;
                    for ( Position P2 : BeaconAbsAtDistance(d) ) {
                        Location = P1 - P2;
                        //std::cout << "P1: " << P1 << " P2: " << P2 << " and Location: " << Location << "\n";
                        if ( CommonPositionCount( KnownScanner ) >= MIN_MATCHES ) Found = true;
                        if (Found) break;
                    }
                    if (Found) break;
                }
                if (Found) break;
            }
            if (Found) break;
        }
        
        std::cout << std::fixed;
        std::cout << std::setw(20);
        std::cout << Name;
        std::cout << " | Time taken by function: ";
        std::cout << std::fixed;
        std::cout << std::setw(6);
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        std::cout << " microseconds" << std::endl;

        // if(!Found){
        //     Location = Starting;
        //     Rotation = 0;
        //     return false;
        // }

        //std::cout << Name << " moved to new Location at " << Location << " and Rotation: " << Rotation << " and " << CommonPositionCount( KnownScanner ) << " Matches.\n";
        //return true;
        return Found;
    }

    int CommonPositionCount( Scanner S ){
        int Count = 0;
        for( Position P1 : Beacons() ) if( S.BeaconAtPos( P1 ) ) Count++;
        return Count;
    }

    double MostCommonDistance(){        
        std::list<double> MyDistances = std::list<double>();
        for( Position P1 : RotationsArray[0] ) for(Position P2 : RotationsArray[0] ) MyDistances.push_back(P1.distance(P2));
        double d = 0.0;
        int LastCount = 0;
        int Count = 0;
        for(double d2 : BeaconDistances ){
            Count = 0;
            for( double d3 : MyDistances ) if( d2 == d3) Count++;
            if( Count > LastCount ){
                d = d2;
                LastCount = Count;
            }
        }
        return d;
    }

    Position Offset( Position P ){
        Position returnValue(P);
        returnValue.X = Location.X + returnValue.X;
        returnValue.Y = Location.Y + returnValue.Y;
        returnValue.Z = Location.Z + returnValue.Z;
        return returnValue;
    }

    void CalcBeaconDistances(){
        BeaconDistances = std::list<double>();
        for( Position P1 : RotationsArray[0] ) for(Position P2 : RotationsArray[0] ) BeaconDistances.push_back(P1.distance(P2));
        BeaconDistances.sort();
        BeaconDistances.unique();
        BeaconDistances.pop_front();
    }

    void CalcBeaconRotations( Position P1 ){
        RotationsArray[  0 ].push_back( Position(  P1.X,  P1.Y,  P1.Z ) );
        RotationsArray[  1 ].push_back( Position(  P1.X, -P1.Y, -P1.Z ) );
        RotationsArray[  2 ].push_back( Position( -P1.X, -P1.Y,  P1.Z ) );
        RotationsArray[  3 ].push_back( Position( -P1.X,  P1.Y, -P1.Z ) );
        RotationsArray[  4 ].push_back( Position(  P1.X, -P1.Z,  P1.Y ) );
        RotationsArray[  5 ].push_back( Position(  P1.X,  P1.Z, -P1.Y ) );
        RotationsArray[  6 ].push_back( Position( -P1.X, -P1.Z, -P1.Y ) );
        RotationsArray[  7 ].push_back( Position( -P1.X,  P1.Z,  P1.Y ) );
        RotationsArray[  8 ].push_back( Position(  P1.Y,  P1.X, -P1.Z ) );
        RotationsArray[  9 ].push_back( Position(  P1.Y, -P1.X,  P1.Z ) );
        RotationsArray[ 10 ].push_back( Position( -P1.Y,  P1.X,  P1.Z ) );
        RotationsArray[ 11 ].push_back( Position( -P1.Y, -P1.X, -P1.Z ) );
        RotationsArray[ 12 ].push_back( Position(  P1.Y,  P1.Z,  P1.X ) );
        RotationsArray[ 13 ].push_back( Position(  P1.Y, -P1.Z, -P1.X ) );
        RotationsArray[ 14 ].push_back( Position( -P1.Y, -P1.Z,  P1.X ) );
        RotationsArray[ 15 ].push_back( Position( -P1.Y,  P1.Z, -P1.X ) );
        RotationsArray[ 16 ].push_back( Position(  P1.Z,  P1.X,  P1.Y ) );
        RotationsArray[ 17 ].push_back( Position(  P1.Z, -P1.X, -P1.Y ) );
        RotationsArray[ 18 ].push_back( Position( -P1.Z,  P1.X, -P1.Y ) );
        RotationsArray[ 19 ].push_back( Position( -P1.Z, -P1.X,  P1.Y ) );
        RotationsArray[ 20 ].push_back( Position(  P1.Z,  P1.Y, -P1.X ) );
        RotationsArray[ 21 ].push_back( Position(  P1.Z, -P1.Y,  P1.X ) );
        RotationsArray[ 22 ].push_back( Position( -P1.Z,  P1.Y,  P1.X ) );
        RotationsArray[ 23 ].push_back( Position( -P1.Z, -P1.Y, -P1.X ) );

        //for( int i = 0; i<24; i++) RotationsArray[i].sort();
    }

};


std::list<Scanner> Scanners = std::list<Scanner>(); 

void ReadFile(std::string filename){
    std::string line;
    std::ifstream myfile;
    myfile.open(filename);
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while (getline(myfile, line)){
                if( line.substr(0,3) == "---" ) {
                    Scanner S = Scanner(line);
                    while (getline(myfile, line)){
                        if( line.length() == 0 ) break;    
                        S.AddBeacon(line);
                    }
                    if( Scanners.size() == 0 ) S.Found = true;
                    Scanners.push_back(S);
                }
            }
        } else throw(std::exception());
        myfile.close();
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
}

int main(){

    ReadFile( FILENAME );
    //auto it = Scanners.begin();   
    //it->Found = true;
    
    bool AllFound = false;

    //Scanner S1 = *it;
    //Scanner S2 = *++it;
    //S2.CalculateOffset(S1);
    auto start = std::chrono::high_resolution_clock::now();
    do {
        for( Scanner& S1 : Scanners ){
            if(!S1.Found) continue;
            for( Scanner& S2 : Scanners ){
                if ( S2.Found ) continue;
                if(  S2.SameDistanceCount(S1) < MIN_MATCHES * 3 ) continue;
                S2.Found = S2.CalculateOffset(S1);
                if( S2.Found ) std::cout << S1.Name << " Found " << S2.Name << "\n"; // << Scanner::PrintBeacons( S2.Beacons() ) << "\n";
            }
        }
        AllFound = true;
        for( Scanner S1 : Scanners ) if(!S1.Found) AllFound = false;
    } while ( !AllFound );
    auto stop = std::chrono::high_resolution_clock::now();


    //std::cout << "\n";

    //for( Scanner S1 : Scanners ) std::cout << S1 << "\n";
    
    std::list<Position> BeaconData = std::list<Position>();

    for( Scanner S1 : Scanners ) if( S1.Found) for( Position P1 : S1.Beacons() ) BeaconData.push_back(P1);
    BeaconData.sort();
    BeaconData.unique();
    //BeaconData.reverse();

    std::cout << Scanner::PrintBeacons( BeaconData ) << "\n";

    std::cout << BeaconData.size() << " Beacons Found.\n";
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
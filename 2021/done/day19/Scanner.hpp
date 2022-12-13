#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <stdexcept>

#include "Position.hpp"

class Scanner{
    public:
    Scanner();
    Scanner( std::string Input );
    
    std::string Name;
    Position Location;
    double Rx = 0.0;
    double Ry = 0.0;
    double Rz = 0.0;
    
    std::list<Position> BeaconAbsPos;
    std::list<Position> ScannerAbsPos;
    std::list<Position> Beacons();
    
    void AddBeacon( Position Input );
    void AddBeacon( std::string Input );

    std::list<double> BeaconDistances();
    bool BeaconAtPos( Position Input );
    std::list<Position> BeaconAtDistance(double d);
    bool ContainsDistance( double Input );
    int SameDistanceCount( Scanner S );
    std::string PrintBeacons();
    std::string PrintMap();
    std::string toString();

    bool CalculateOffset( Scanner KnownScanner );

    int CommonPositionCount( Scanner S );
    double MostCommonDistance();

    private:
    double FindMinX();
    double FindMaxX();
    double FindMinY();
    double FindMaxY();
    Position Rotate( Position P );
    Position Offset( Position P );
};

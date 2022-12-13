#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <stdexcept>

#include "Position.cpp"

#define MAX_RANGE 1000
#define MIN_MATCHES 3
//#define MIN_MATCHES 12

class Scanner{
    public:
    std::string Name;
    Position Location;
    double Rx = 0.0;
    double Ry = 0.0;
    double Rz = 0.0;
    std::list<Position> BeaconAbsPos;
    std::list<Position> ScannerAbsPos;
    std::list<Position> Beacons(){
        std::list<Position> returnValue = std::list<Position>();
        for( Position P1 : BeaconAbsPos ) returnValue.push_back( Offset( Rotate( P1 ) ) );
        returnValue.sort();
        return returnValue;
    }
    void AddBeacon( Position Input ){ BeaconAbsPos.push_back( Input ); }
    void AddBeacon( std::string Input ){ BeaconAbsPos.push_back( Position( Input ) ); }
    Scanner(){}
    Scanner( std::string Input ){
        Name = Input;
    }
    std::list<double> BeaconDistances(){
        std::list<double> MyDistances = std::list<double>();
        for( Position P1 : BeaconAbsPos ) for(Position P2 : BeaconAbsPos ) MyDistances.push_back(P1.distance(P2));
        MyDistances.sort();
        MyDistances.unique();
        MyDistances.pop_front();
        return MyDistances;
    }
    bool BeaconAtPos( Position Input ){
        for(Position P1 : Beacons() ) if( Input == P1 ) return true;
        return false;   
    }
    std::list<Position> BeaconAtDistance(double d){
        std::list<Position> returnValue = std::list<Position>();
        for( Position P1 : Beacons() ) for( Position P2 : Beacons() ) if ( P1.distance( P2 ) == d ) returnValue.push_back(P1);
        returnValue.sort();
        returnValue.unique();
        return returnValue;
    }
    bool ContainsDistance( double Input ){
        for(double d : BeaconDistances() ) if( Input == d ) return true;
        return false;
    }
    int SameDistanceCount( Scanner S ){
        std::list<double> MyDistances = BeaconDistances();
        int Count = 0;
        for(auto it = MyDistances.begin(); it != MyDistances.end(); it++ ){
            if(S.ContainsDistance(*it)) Count++;
        }
        return Count;
    }
    std::string PrintBeacons(){
        std::string returnValue;
        int Count = 1;
        for( Position P1 : Beacons() ) {
            returnValue += "Beacon: ";
            returnValue += Count++;
            returnValue += " : " + P1.toString() + "\n";
        }
        return returnValue;
        
    }
    std::string PrintMap(){
        int MinX = FindMinX();
        int MinY = FindMinY();
        int MaxX = FindMaxX();
        int MaxY = FindMaxY();
        int RangeX = MaxX - MinX +1;
        int RangeY = MaxY - MinY +1;
        int OffsetX = std::abs( MinX );    
        int OffsetY = std::abs( MinY );
        //std::cout << "Scanner: " << Name << " : " << OffsetX << "," << OffsetY << "\n";
        //std::cout << "Min X: " << MinX << " Max X: " << MaxX << " Range X: " << RangeX << " Offest X: " << OffsetX << "\n";
        //std::cout << "Min Y: " << MinY << " Max Y: " << MaxY << " Range Y: " << RangeY << " Offest Y: " << OffsetY << "\n";
        char Data[RangeX][RangeY];
        for(int x = 0; x < RangeX; x++ ) for(int y = 0; y < RangeY; y++ ) Data[x][y] = '.';

        int Bx = 0;
        int By = 0;
        int Count = 0;
        for ( Position P1 : Beacons() ){
            Bx = P1.X + OffsetX;
            By = P1.Y + OffsetY;
            //std::cout << "Beacon: " << Count++ << " : " << Bx << "," << By << "\n";
            Data[Bx][By] = 'B';
        }
        for ( Position P1 : ScannerAbsPos ){
            Bx = P1.X + OffsetX;
            By = P1.Y + OffsetY;
            //std::cout << "Beacon: " << Count++ << " : " << Bx << "," << By << "\n";
            Data[Bx][By] = 'S';
        }
        Data[OffsetX][OffsetY] = 'X';

        std::ostringstream returnValue;
        for(int y = RangeY-1; y > -1 ; y-- ){
            for(int x = 0; x < RangeX; x++ ) returnValue << std::setw(3) << Data[x][y];
            returnValue << "\n";
        }

        return returnValue.str();
    }   
    std::string toString(){
        std::ostringstream returnValue;
        returnValue << "Scanner: " << Name << " at " << Location.toString() << " with " << BeaconAbsPos.size() << " Beacons";       
        return returnValue.str();
    }

    bool CalculateOffset( Scanner KnownScanner ){        
        std::cout << "Comparing " << Name << " to " << KnownScanner.Name << "\n";
        Position StartingPos = Location;
        std::list<double> MyDistances = BeaconDistances();
        int Count = 0;
        for( double d : MyDistances )  if( KnownScanner.ContainsDistance( d ) ) Count++;
        std::cout << "Distance Matches Found: " << Count << "\n";
        if( Count < MIN_MATCHES ) return false;

        std::list<Position> Known_List = KnownScanner.Beacons();
        //std::list<Position> Matches = std::list<Position>();

        double d1 = MostCommonDistance();
        double d2 = KnownScanner.MostCommonDistance();
        Position A1, A2, A3, A4;
        Position Offset = Position();
        bool Found = false;
        int r = 0;
        // check each beacon.
        for (Position P1 : BeaconAbsPos) {
            for (Position P2 : Known_List) {
                std::cout << "Trying P1: " << P1.toString() << ", and P2: " << P2.toString() << "\n";
                if( !(P2.X == -618 & P1.X == 686) ) continue;
                //for (int iRx = -3; iRx < 4; iRx++) {
                    //for (int iRy = -3; iRy < 4; iRy++) {
                        //for (int iRz = -3; iRz < 4; iRz++) {
                            //Rx = iRx * 90;
                            //Ry = iRy * 90;
                            //Rz = iRz * 90;
                            std::cout << "Trying Rotation - Rx:" << Rx << ", Ry: " << Ry << ", Rz: " << Rz << "\n";
                            Offset = P2 - P1;
                            Location = Offset;
                            r = CommonPositionCount(KnownScanner);
                            std::cout << "Offset: " << Offset.toString() << " Matches: " << r << "\n";
                            if ( r >= MIN_MATCHES)
                            {
                                Found = true;
                                break;
                            }
                           

                        //}
                        //if (Found) break;
                    //}
                    //if (Found)  break;
                //}
                //if (Found) break;
            }
            if (Found) break;
        }

        if(!Found){
            std::cout << "Location not found.\n";
            Location = StartingPos;
            return false;
        }

        std::cout << "New Location is " << Location.toString() << "\n";
        return true;
    }

    int CommonPositionCount( Scanner S ){
        int Count = 0;
        for( Position P1 : Beacons() ) if( S.BeaconAtPos( P1 ) ) Count++;
        //std::cout << "Found " << Count << " Positions in common.\n";
        return Count;
    }

    double MostCommonDistance(){        
        std::list<double> MyDistances = std::list<double>();
        for( Position P1 : BeaconAbsPos ) for(Position P2 : BeaconAbsPos ) MyDistances.push_back(P1.distance(P2));
        double d = 0.0;
        int LastCount = 0;
        int Count = 0;
        for(double d2 : BeaconDistances() ){
            Count = 0;
            for( double d3 : MyDistances ) if( d2 == d3) Count++;
            if( Count > LastCount ){
                d = d2;
                LastCount = Count;
            }
        }
        return d;
    }

    private:
    double FindMinX(){
        double returnValue = 0;
        for( Position P1 : Beacons() ) if( P1.X < returnValue ) returnValue = P1.X;
        for( Position P1 : ScannerAbsPos ) if( P1.X < returnValue ) returnValue = P1.X;
        return returnValue;
    }
    double FindMaxX(){
        double returnValue = 0;
        for( Position P1 : Beacons() ) if( P1.X > returnValue ) returnValue = P1.X;
        for( Position P1 : ScannerAbsPos ) if( P1.X > returnValue ) returnValue = P1.X;
        return returnValue;
    }
    double FindMinY(){
        double returnValue = 0;
        for( Position P1 : Beacons() ) if( P1.Y < returnValue ) returnValue = P1.Y;
        for( Position P1 : ScannerAbsPos ) if( P1.Y < returnValue ) returnValue = P1.Y;
        return returnValue;
    }
    double FindMaxY(){
        double returnValue = 0;
        for( Position P1 : Beacons() ) if( P1.Y > returnValue ) returnValue = P1.Y;
        for( Position P1 : ScannerAbsPos ) if( P1.Y > returnValue ) returnValue = P1.Y;
        return returnValue;
    }
    Position Rotate( Position P ) {
        // https://stackoverflow.com/questions/45357715/how-to-rotate-point-around-another-one
        // http://www.fastgraph.com/makegames/3drotation/3dsrce.html
        double pi = 4.0*atan(1.0);
        double px = P.X;
        double py = P.Y;
        double pz = P.Z;
        double cosa = std::cos( Rz * pi / 180 );
        double sina = std::sin( Rz * pi / 180 );
        double cosb = std::cos( Ry * pi / 180 );
        double sinb = std::sin( Ry * pi / 180 );
        double cosc = std::cos( Rx * pi / 180 );
        double sinc = std::sin( Rx * pi / 180 );
        double Axx = cosa * cosb;
        double Axy = cosa * sinb * sinc - sina * cosc;
        double Axz = cosa * sinb * cosc + sina * sinc;
        double Ayx = sina * cosb;
        double Ayy = sina * sinb * sinc + cosa * cosc;
        double Ayz = sina * sinb * cosc - cosa * sinc;
        double Azx = -sinb;
        double Azy = cosb * sinc;
        double Azz = cosb * cosc;
        Position returnValue;
        returnValue.X = Axx * px + Axy * py + Axz * pz;
        returnValue.Y = Ayx * px + Ayy * py + Ayz * pz;
        returnValue.Z = Azx * px + Azy * py + Azz * pz;
        return returnValue;
    }
    Position Offset( Position P ){
        Position returnValue(P);
        returnValue.X = returnValue.X + Location.X;
        returnValue.Y = returnValue.Y + Location.Y;
        returnValue.Z = returnValue.Z + Location.Z;
        return returnValue;
    }
};

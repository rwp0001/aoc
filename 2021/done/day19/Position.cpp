#include <string>
#include <list>
#include <stdexcept>
#include <cmath>
#include <iomanip>

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

    std::string toString(){
        std::ostringstream returnValue;
        returnValue << "X: ";     
        returnValue << std::setw( DISPLAY_PRECISION + 3);
        returnValue.precision(DISPLAY_PRECISION);
        returnValue << std::fixed;
        returnValue << X;
        returnValue << " Y: ";
        returnValue << std::setw( DISPLAY_PRECISION + 3);
        returnValue.precision(DISPLAY_PRECISION);
        returnValue << std::fixed;
        returnValue << Y;
        returnValue << " Z: ";
        returnValue << std::setw( DISPLAY_PRECISION + 3);
        returnValue.precision(DISPLAY_PRECISION);
        returnValue << std::fixed;
        returnValue << Z;
        return returnValue.str();
    }
    
    std::string Print_Dist( Position P ){
        std::ostringstream returnValue;
        returnValue << "Distance from " << toString() << " to " << P.toString() << " is ";
        returnValue.precision(DISPLAY_PRECISION);
        returnValue << std::fixed << distance(P);
        return returnValue.str();
    }

    constexpr  bool operator< ( const Position &rhs){ 
        if ( X > rhs.X ) return false;
        if ( Y > rhs.Y ) return false;
        if ( Z > rhs.Z ) return false;
        return true;
    }
    constexpr  bool operator==( const Position &rhs){ 
        if ( X != rhs.X ) return false;
        if ( Y != rhs.Y ) return false;
        if ( Z != rhs.Z ) return false;
        return true;
    }
    Position operator+ ( const Position &rhs){ 
        Position returnValue(rhs);
        //std::cout << "Adding: " << toString() << " to  " << returnValue.toString() << " = "; 
        returnValue.X = returnValue.X + X;
        returnValue.Y = returnValue.Y + Y;
        returnValue.Z = returnValue.Z + Z;
        //std::cout << returnValue.toString() << "\n";
        return returnValue;
    }
    Position operator- ( const Position &rhs){ 
        Position returnValue(rhs);
        returnValue.X = X - returnValue.X;
        returnValue.Y = Y - returnValue.Y;
        returnValue.Z = Z - returnValue.Z;
        return returnValue;
    }

    // std::ostream& operator<< (std::ostream& stream){
    //     stream << this->toString();
    //     return stream;
    // }

    // std::ostream& operator<< (std::ostream& out, const Position& point)
    // {
    //     // Since operator<< is a friend of the Point class, we can access Point's members directly.
    //     out << toString(); // actual output done here
    //     return out; // return std::ostream so we can chain calls to operator<<
    // }

};

#include <string>
#include <list>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class Position {
  
    public:
    Position();
    Position( double x, double y, double z );
    Position(std::string Input);

    double X;
    double Y;
    double Z;

    double distance(Position P);
    std::string toString();
    std::string Print_Dist( Position P );
    constexpr  bool operator< ( const Position &rhs);
    constexpr  bool operator==( const Position &rhs);
    Position operator+ ( const Position &rhs);
    Position operator- ( const Position &rhs);

};

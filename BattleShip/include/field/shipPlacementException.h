#ifndef SHIP_PLACEMENT_EXCEPTION
#define SHIP_PLACEMENT_EXCEPTION

#include <string>

class ShipPlacementException
{
public:
    ShipPlacementException(std::string message);
    ~ShipPlacementException();

    std::string what() const noexcept;

private:
    std::string message_;
}; 

#endif
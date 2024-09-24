#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <initializer_list>
#include <vector>
#include "ship.h"

class ShipManager
{
public:
    ShipManager(std::initializer_list<int> ship_sizes);

    ~ShipManager();

    void printShips();

private:
    std::vector<Ship> ships_;
};

#endif
#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <initializer_list>
#include <vector>
#include <tuple>
#include "ship.h"
#include "field.h"

class ShipManager
{
public:
    ShipManager(std::initializer_list<int> ship_sizes);

    ~ShipManager();

    int getSize() const;

    void placeShips(Field& field, std::initializer_list<std::tuple<int, int, ShipOrientation>> ship_coordinates);

    void printShips() const;

private:
    std::vector<Ship> ships_;
    const int size_;
};

#endif
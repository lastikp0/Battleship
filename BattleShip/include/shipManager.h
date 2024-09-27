#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <initializer_list>
#include <vector>
#include <list>
#include <utility>
#include "ship.h"
#include "field.h"

class ShipManager
{
public:
    ShipManager();

    explicit ShipManager(std::initializer_list<int> ship_sizes);

    ~ShipManager();

    void printShips() const noexcept;

    void placeShip(Field& field, int index, int x, int y, ShipOrientation orientation);

    void addShip(int ship_size);

    std::vector<Ship> getUnusedShips() const noexcept;

    std::vector<Ship> getUsedShips() const noexcept;

    int getUnusedShipsSize() const noexcept;

    int getUsedShipsSize() const noexcept;

private:
    std::list<std::pair<Ship, bool>> ships_;
};

#endif
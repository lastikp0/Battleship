#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <initializer_list>
#include <vector>
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

    void addShip(int ship_size) noexcept;

    const std::vector<Ship>& getUnusedShips() const noexcept;

    const std::vector<Ship>& getUsedShips() const noexcept;

    int getUnusedShipsSize() const noexcept;

    int getUsedShipsSize() const noexcept;

private:
    std::vector<Ship> unused_ships_;
    std::vector<Ship> used_ships_;
};

#endif
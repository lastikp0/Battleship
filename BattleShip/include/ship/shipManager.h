#ifndef SHIP_MANAGER
#define SHIP_MANAGER

#include <iostream>
#include <vector>

#include "ship.h"
#include "field.h"

class ShipManager
{
public:
    ShipManager();
    explicit ShipManager(std::vector<int> ship_sizes);

    ~ShipManager();

    void printShips() const noexcept;

    void addShip(Ship* ship);

    Ship* getUnusedShip(int index) const;
    Ship* getUsedShip(int index) const;

    void makeShipUsed(int index);

    int getUnusedShipSize() const noexcept;
    int getUsedShipSize() const noexcept;
    int getAliveShipSize() const noexcept;

private:
    std::vector<Ship*> unused_ships_;
    std::vector<Ship*> used_ships_;
};

#endif

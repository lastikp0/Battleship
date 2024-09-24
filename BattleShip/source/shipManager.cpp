#include "shipManager.h"
#include "ship.h"

#include <initializer_list>
#include <vector>

ShipManager::ShipManager(std::initializer_list<int> ship_sizes)
{
    for (auto ship : ship_sizes) {
        ships_.push_back(Ship(ship));
    }
}

ShipManager::~ShipManager()
{
    ships_.clear();
}

void ShipManager::printShips()
{
    //add
    return;
}
#include "shipManager.h"
#include "ship.h"
#include "field.h"

#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>

ShipManager::ShipManager() = default;
 
ShipManager::ShipManager(std::initializer_list<int> ship_sizes)
{
    for (auto ship_size : ship_sizes) {
        Ship* ship = new Ship(ship_size);
        unused_ships_.push_back(ship);
    }
}

ShipManager::~ShipManager()
{
    for (int i = 0; i < unused_ships_.size(); i++) {
        delete unused_ships_[i];
    }
    unused_ships_.clear();

    for (int i = 0; i < used_ships_.size(); i++) {
        delete used_ships_[i];
    }
    used_ships_.clear();
}

void ShipManager::printShips() const noexcept
{  
    int counter = 0;

    std::cout << "Unused ships:" << "\n";
    for (auto ship: unused_ships_) {
        std::cout << "Ship " << counter++ << ": ";
        for (int i = 0; i < ship->getSize(); i++) {
            if (ship->getSegmentStatus(i) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (ship->getSegmentStatus(i) == ShipSegmentStatus::damaged) {
                std::cout << "[1]";
            } else {
                std::cout << "[0]";
            }
        }
        std::cout << "\n";
    }
    if (unused_ships_.size() == 0) {
        std::cout << "None" << "\n";
    }

    std::cout << "\n";

    counter = 0;

    std::cout << "Used ships:" << "\n";
    for (auto ship: used_ships_) {
        std::cout << "Ship " << counter++ << ": ";
        for (int i = 0; i < ship->getSize(); i++) {
            if (ship->getSegmentStatus(i) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (ship->getSegmentStatus(i) == ShipSegmentStatus::damaged) {
                std::cout << "[1]";
            } else {
                std::cout << "[0]";
            }
        }
        std::cout << "\n";
    }
    if (used_ships_.size() == 0) {
        std::cout << "None" << "\n";
    }

    std::cout << "\n";

    return;
}

void ShipManager::addShip(int ship_size)
{
    Ship* ship = new Ship(ship_size);
    unused_ships_.push_back(ship);
}

Ship* ShipManager::getUnusedShip(int index) const
{
    if (index < 0 || index >= unused_ships_.size()) {
        throw std::out_of_range("Ship index out of range");
    }

    return unused_ships_[index];
}

Ship* ShipManager::getUsedShip(int index) const
{
    if (index < 0 || index >= used_ships_.size()) {
        throw std::out_of_range("Ship index out of range");
    }

    return used_ships_[index];
}

void ShipManager::makeShipUsed(int index)
{
    if (index < 0 || index >= unused_ships_.size()) {
        throw std::out_of_range("Ship index out of range");
    }

    std::move(unused_ships_.begin()+index, unused_ships_.begin()+index+1, std::back_inserter(used_ships_));
    unused_ships_.erase(unused_ships_.begin()+index);
}

int ShipManager::getUnusedShipSize() const noexcept
{
    return unused_ships_.size();
}

int ShipManager::getUsedShipSize() const noexcept
{
    return used_ships_.size();
}
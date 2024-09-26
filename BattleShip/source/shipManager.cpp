#include "shipManager.h"
#include "ship.h"
#include "field.h"

#include <iostream>
#include <initializer_list>
#include <vector>

ShipManager::ShipManager() = default;
 
ShipManager::ShipManager(std::initializer_list<int> ship_sizes)
{
    for (auto ship : ship_sizes) {
        unused_ships_.push_back(Ship(ship));
    }
}

ShipManager::~ShipManager()
{
    unused_ships_.clear();
    used_ships_.clear();
}

void ShipManager::printShips() const noexcept
{
    std::cout << "Unused ships:" << "\n";
    for (int i = 0; i < unused_ships_.size(); i++) {
        std::cout << "Ship " << i << ": ";
        for (int j = 0; j < unused_ships_[i].getSize(); j++) {
            if (unused_ships_[i].getSegmentStatus(j) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (unused_ships_[i].getSegmentStatus(j) == ShipSegmentStatus::damaged) {
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

    std::cout << "Used ships:" << "\n";
    for (int i = 0; i < used_ships_.size(); i++) {
        std::cout << "Ship " << i << ": ";
        for (int j = 0; j < used_ships_[i].getSize(); j++) {
            if (used_ships_[i].getSegmentStatus(j) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (used_ships_[i].getSegmentStatus(j) == ShipSegmentStatus::damaged) {
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

void ShipManager::placeShip(Field& field, int index, int x, int y, ShipOrientation orientation)
{
    if (index < 0 || index >= unused_ships_.size()) {
        throw std::out_of_range("Index out of range");
    }
    
    used_ships_.push_back(unused_ships_[index]);
    field.placeShip(&used_ships_[used_ships_.size() - 1], x, y, orientation);

    unused_ships_.erase(unused_ships_.begin() + index);
}

void ShipManager::addShip(int ship_size)
{
    unused_ships_.push_back(Ship(ship_size));
}

const std::vector<Ship>& ShipManager::getUnusedShips() const noexcept
{
    return unused_ships_;
}

const std::vector<Ship>& ShipManager::getUsedShips() const noexcept
{
    return unused_ships_;
}

int ShipManager::getUnusedShipsSize() const noexcept
{
    return unused_ships_.size();
}

int ShipManager::getUsedShipsSize() const noexcept
{
    return used_ships_.size();
}

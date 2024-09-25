#include "shipManager.h"
#include "ship.h"
#include "field.h"

#include <iostream>
#include <initializer_list>
#include <vector>
#include <tuple>

ShipManager::ShipManager(std::initializer_list<int> ship_sizes) : size_(ship_sizes.size())
{
    for (auto ship : ship_sizes) {
        ships_.push_back(Ship(ship));
    }
}

ShipManager::~ShipManager()
{
    ships_.clear();
}

int ShipManager::getSize() const
{
    return size_;
}

void ShipManager::placeShips(Field& field, std::initializer_list<std::tuple<int, int, ShipOrientation>> ship_coordinates)
{
    if (ship_coordinates.size() != size_) {
        throw std::logic_error("Number of ships must be equal to number of coordinates");
    }

    int ship_index = 0;
    for (auto ship : ship_coordinates) {
        field.placeShip(&ships_[ship_index++], std::get<0>(ship), std::get<1>(ship), std::get<2>(ship));
    }
}

void ShipManager::printShips() const
{
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < ships_[i].getSize(); j++) {
            if (ships_[i].getSegmentStatus(j) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (ships_[i].getSegmentStatus(j) == ShipSegmentStatus::damaged) {
                std::cout << "[1]";
            } else {
                std::cout << "[0]";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    return;
}
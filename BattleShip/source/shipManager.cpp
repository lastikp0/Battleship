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
        ships_.push_back({ship, false});
    }
}

ShipManager::ShipManager(const ShipManager& other)
{
    ships_.resize(other.ships_.size());
    for (int i = 0; i < ships_.size(); i++) {
        ships_[i].first = new Ship(other.ships_[i].first.getSize());
        //damage segments?
        ships_[i].second = (other.ships_[i].second;
    }
}

//method that copies placement of ships on new Field

ShipManager::~ShipManager()
{
    for (int i = 0; i < ships_.size(); i++) {
        delete ships_[i].first;
    }
    ships_.clear();
}

void ShipManager::printShips() const noexcept
{
    for (auto ship: ships_) {
        std::cout << "Ship " << counter++ << ": ";
        for (int i = 0; i < ship.first->getSize(); i++) {
            if (ship.first->getSegmentStatus(i) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (ship.first->getSegmentStatus(i) == ShipSegmentStatus::damaged) {
                std::cout << "[1]";
            } else {
                std::cout << "[0]";
            }
        }
        
        if (ship.second) {
            std::cout << " Used" << "\n";
        } else {
            std::cout << " Unused" << "\n";
        }
    }
    
    if (ships_.size() == 0) {
        std::cout << "None" << "\n";
    }

    std::cout << "\n";

    return;
}

void ShipManager::placeShip(Field& field, int index, int x, int y, ShipOrientation orientation)
{
    if (index < 0 || index >= ships_.size()) {
        throw std::out_of_range("Index out of range");
    }

    if (ships_[i].second) {
        throw std::logic_error("Ship was already placed to field");
    }

    ships_[i].second = true;
    field.placeShip(ships_[i].first, x, y, orientation);
}

void ShipManager::addShip(int ship_size)
{
    ships_.push_back({Ship(ship_size), false});
}

std::vector<Ship> ShipManager::getUnusedShips() const noexcept
{
    std::vector<Ship> unused_ships;
    for(auto ship: ships_)
        if(ship.second == false)
            unused_ships.push_back(*ship.first);
    return unused_ships;
}

std::vector<Ship> ShipManager::getUsedShips() const noexcept
{
    std::vector<Ship> used_ships;
    for(auto ship: ships_)
        if(ship.second == false)
            used_ships.push_back(*ship.first);
    return used_ships;
}

int ShipManager::getUnusedShipsSize() const noexcept
{
    int unused_ships_num;
    for(auto ship: ships_)
        if(ship.second == false)
            unused_ships_num++;
    return unused_ships_num;
}

int ShipManager::getUsedShipsSize() const noexcept
{
    int used_ships_num;
    for(auto ship: ships_)
        if(ship.second == false)
            used_ships_num++;
    return used_ships_num;
}

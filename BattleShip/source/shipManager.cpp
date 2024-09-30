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
    for (auto ship : ship_sizes) {
        ships_.push_back({Ship(ship), false});
    }
}

ShipManager::~ShipManager()
{
    ships_.clear();
}

void ShipManager::printShips() const noexcept
{

    int counter = 0;
    for (auto ship: ships_) {
        std::cout << "Ship " << counter++ << ": ";
        for (int i = 0; i < ship.first.getSize(); i++) {
            if (ship.first.getSegmentStatus(i) == ShipSegmentStatus::intact) {
                std::cout << "[2]";
            } else if (ship.first.getSegmentStatus(i) == ShipSegmentStatus::damaged) {
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

    std::list<std::pair<Ship, bool>>::iterator it = ships_.begin();
    std::advance(it, index);

    if (it->second) {
        throw std::logic_error("Ship was already placed to field");
    }

    it->second = true;
    field.placeShip(&(it->first), x, y, orientation);
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
            unused_ships.push_back(ship.first);
    return unused_ships;
}

std::vector<Ship> ShipManager::getUsedShips() const noexcept
{
    std::vector<Ship> used_ships;
    for(auto ship: ships_)
        if(ship.second == false)
            used_ships.push_back(ship.first);
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
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
        ships_.push_back({ship, nullptr});
    }
}

void ShipManager::copyShipsFromOldToNewField(Field* old_field, Field* new_field)
{
    if (old_field == nullptr || new_field == nullptr) {
        throw std::invalid_argument("Field is nullptr");
    }
    if (old_field == new_field) {
        throw std::logic_error("Old and New fields are same");
    }

    int size = ships_.size();
    for (int i = 0; i < size; i++) {
        if (ships_[i].second == old_field) {
            Ship* ship = new Ship(ships_[i].first->getSize());

            for (int j = 0; j < ship->getSize(); j++) {
                ship->setSegmentHealth(j, ships_[i].first->getSegmentHealth(j));
            }

            new_field->placeShip(ship, ships_[i].first->getHeadX(0), ships_[i].first->getHeadY(0), ships_[i].first->getOrientation());

            ships_.push_back({ship, new_field});
        }
    }
}

ShipManager::~ShipManager()
{
    for (int i = 0; i < ships_.size(); i++) {
        delete ships_[i].first;
    }
    ships_.clear();
}

void ShipManager::printShips() const noexcept
{
    int counter = 0;
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

void ShipManager::placeShip(Field* field, int index, int x, int y, ShipOrientation orientation)
{
    if (index < 0 || index >= ships_.size()) {
        throw std::out_of_range("Index out of range");
    }

    if (ships_[index].second) {
        throw std::logic_error("Ship was already placed to field");
    }

    ships_[index].second = field;
    field->placeShip(ships_[index].first, x, y, orientation);
}

void ShipManager::addShip(int ship_size)
{
    Ship* ship = new Ship(ship_size);
    ships_.push_back({ship, nullptr});
}

std::vector<Ship> ShipManager::getUnusedShips() const noexcept
{
    std::vector<Ship> unused_ships;
    for(auto ship: ships_)
        if(ship.second == nullptr)
            unused_ships.push_back(*ship.first);
    return unused_ships;
}

std::vector<Ship> ShipManager::getUsedShips() const noexcept
{
    std::vector<Ship> used_ships;
    for(auto ship: ships_)
        if(ship.second != nullptr)
            used_ships.push_back(*ship.first);
    return used_ships;
}

int ShipManager::getUnusedShipsSize() const noexcept
{
    int unused_ships_num;
    for(auto ship: ships_)
        if(ship.second == nullptr)
            unused_ships_num++;
    return unused_ships_num;
}

int ShipManager::getUsedShipsSize() const noexcept
{
    int used_ships_num;
    for(auto ship: ships_)
        if(ship.second != nullptr)
            used_ships_num++;
    return used_ships_num;
}

#include "field.h"
#include "ship.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <string>

#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

bool Coords::operator==(const Coords& other) const
{
    return x == other.x && y == other.y;
}

std::size_t CoordsHash::operator()(const Coords& coords) const
{
    return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) << 1);
}

Field::Field() = default;

Field::Field(int size_x, int size_y)
{
    if (size_x <= 0 || size_y <= 0) {
        throw std::invalid_argument("Field size must be grater than 0");
    }
    size_x_ = size_x;
    size_y_ = size_y;
}

Field::Field(const Field& other) :
    ships_(other.ships_),
    opened_cells_(other.opened_cells_),
    size_x_(other.size_x_),
    size_y_(other.size_y_)
{}

Field& Field::operator=(const Field& other)
{
    if (this == &other) {
        return *this;
    }

    ships_ = other.ships_;
    opened_cells_ = other.opened_cells_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;

    return *this;
}

Field::Field(Field&& other) :
    ships_(std::move(other.ships_)),
    opened_cells_(std::move(other.opened_cells_)),
    size_x_(std::move(other.size_x_)),
    size_y_(std::move(other.size_y_))
{}

Field& Field::operator=(Field&& other)
{
    if (this == &other) {
        return *this;
    }

    ships_ = std::move(other.ships_);
    opened_cells_ = std::move(other.opened_cells_);
    size_x_ = std::move(other.size_x_);
    size_y_ = std::move(other.size_y_);

    return *this;
}

Field::~Field()
{
    ships_.clear();
    opened_cells_.clear();
}

void Field::placeShip(Ship* ship, Coords coords, ShipOrientation orientation)
{   
    if (ship == nullptr) {
        throw ShipPlacementException("Ship pointer is nullptr");
    }
        
    int offset_x, offset_y;
    if (orientation == ShipOrientation::horizontal) {
        offset_x = ship->getSize() - 1;
        offset_y = 0;
    } else {
        offset_x = 0;
        offset_y = ship->getSize() - 1;
    }

    if (coords.x < 0 || coords.x >= size_x_ - offset_x || coords.y < 0 || coords.y >= size_y_ - offset_y) {
        throw ShipPlacementException("Ship coordinates out of range");
    }

    for (int i = coords.x - 1; i < coords.x + offset_x + 1; i++) {
        if (i >= 0 && i < size_x_) {
            for (int j = coords.y - 1; j < coords.y + offset_y + 1; j++) {
                if (j >= 0 && j < size_y_) {
                    if (ships_.count({i, j}) != 0) {
                        throw ShipPlacementException("Ships may not contact each other");
                    }
                }   
            }
        }
    }
    
    int segment_index = 0;     
    for (int i = coords.x; i < coords.x + offset_x + 1; i++) {
        for (int j = coords.y; j < coords.y + offset_y + 1; j++) {
            ship->setOrientation(orientation);
            ships_[{i, j}] = ShipCell(ship, segment_index++);
        }
    }
}

bool Field::attackCell(Coords coords, int damage)
{
    if (coords.x < 0 || coords.x >= size_x_ || coords.y < 0 || coords.y >= size_y_) {
        throw AttackOutOfRangeException("Coordinates out of range");
    }

    if (ships_.count({coords.x, coords.y}) != 0) {
        ships_[{coords.x, coords.y}].attackCell(damage);
        damage = 1;
        opened_cells_[{coords.x, coords.y}] = FieldCell(FieldCellStatus::ship);

        if (ships_[{coords.x, coords.y}].getShipStatus() == ShipStatus::dead) {
            return true;
        }

        return false;
    }

    opened_cells_[{coords.x, coords.y}] = FieldCell(FieldCellStatus::empty);
    return false;
}

void Field::printField() const noexcept
{
    for (int y = 0; y < size_y_; y++) {
        for (int x = 0; x < size_x_; x++) {
            if (opened_cells_.count({x, y}) != 0) {
                if (opened_cells_.at({x, y}).getStatus() == FieldCellStatus::ship) {
                    if (ships_.at({x, y}).getShipSegmentStatus() == ShipSegmentStatus::intact) {
                        std::cout << "[2]";
                    } else if (ships_.at({x, y}).getShipSegmentStatus() == ShipSegmentStatus::damaged) {
                        std::cout << "[1]";
                    } else {
                        std::cout << "[0]";
                    }
                    
                } else {
                    std::cout << "[.]";
                }
            } else {
                std::cout << "[ ]";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool Field::isShip(Coords coords) const
{
    if (coords.x < 0 || coords.x >= size_x_ || coords.y < 0 || coords.y >= size_y_) {
        throw std::out_of_range("Coordinates out of range");
    }

    return ships_.count({coords.x, coords.y}) != 0;
}

Coords Field::getSize() const noexcept
{
    return {size_x_, size_y_};
}

void Field::getRandomShip(Ship** ship, int& index) const noexcept
{
    int ship_index = rand() % ships_.size();

    auto it = ships_.begin();
    std::advance(it, ship_index);
    it->second.getShipSegment(ship, index);

    return;
}

Field::ShipCell::ShipCell() = default;

Field::ShipCell::ShipCell(Ship* ship, int index)
{
    ship_ = ship;
    ship_segment_index_ = index;
}

Field::ShipCell::~ShipCell() = default;

void Field::ShipCell::attackCell(int damage)
{
    ship_->damageSegment(ship_segment_index_, damage);
}

void Field::ShipCell::setShipSegment(Ship* ship, int index) noexcept
{
    ship_ = ship;
    ship_segment_index_ = index;
}

ShipSegmentStatus Field::ShipCell::getShipSegmentStatus() const noexcept
{
    return ship_->getSegmentStatus(ship_segment_index_);
}

ShipStatus Field::ShipCell::getShipStatus() const noexcept
{
    return ship_->getShipStatus();
}

void Field::ShipCell::getShipSegment(Ship** ship, int& index) const noexcept
{
    *ship = ship_;
    index = ship_segment_index_;
}

Field::FieldCell::FieldCell()
{
    status_ = FieldCellStatus::unknown;
}

Field::FieldCell::FieldCell(FieldCellStatus status)
{
    status_ = status;
}

Field::FieldCell::~FieldCell() = default;

FieldCellStatus Field::FieldCell::getStatus() const noexcept
{
    return status_;
}

void Field::FieldCell::setStatus(FieldCellStatus status) noexcept
{
    status_ = status;
}

std::string Field::getField() const noexcept
{
    std::string result = "";

    result += std::to_string(size_x_) + " ";
    result += std::to_string(size_y_) + "\n";

    for (int y = 0; y < size_y_; y++) {
        for (int x = 0; x < size_x_; x++) {
            if (opened_cells_.count({x, y}) != 0) {
                if (opened_cells_.at({x, y}).getStatus() == FieldCellStatus::ship) {
                    result += "2 ";
                } else {
                    result += "1 ";
                }
            } else {
                result += "0 ";
            }
        }
        result += "\n";
    }

    return result;
}

std::string Field::getShips() const noexcept
{
    int count = 0;
    std::string result = "";

    for (int x = 0; x < size_x_; x++) {
        for (int y = 0; y < size_y_; y++) {
            if (ships_.count({x, y}) != 0) {
                Ship* ship;
                int index;
                
                ships_.at({x, y}).getShipSegment(&ship, index);
                if (index == 0) {
                    count++;
                    result += std::to_string(x) + " " + std::to_string(y) + " ";

                    if (ship->getOrientation() == ShipOrientation::horizontal) {
                        result += "0 ";
                    } else {
                        result += "1 ";
                    }

                    result += std::to_string(ship->getSize());
                    for (int i = 0; i < ship->getSize(); i++) {
                        result += " " + std::to_string(ship->getSegmentHealth(i));
                    }
                    result += "\n";
                }
            }
        }
    }

    result = std::to_string(count) + "\n" + result;

    return result;
}

void Field::setField(std::vector<std::vector<char>>& info)
{
    opened_cells_.clear();
    ships_.clear();

    for (int y = 0; y < size_y_; y++) {
        for (int x = 0; x < size_x_; x++) {
            if (info[y][x] == '1') {
                opened_cells_[{x, y}] = FieldCell(FieldCellStatus::empty);
            } else if (info[y][x] == '2') {
                opened_cells_[{x, y}] = FieldCell(FieldCellStatus::ship);
            }
        }
    }
}
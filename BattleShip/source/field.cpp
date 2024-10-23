#include "field.h"
#include "ship.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

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

    // field_.resize(size_x_);

    // for (int i = 0; i < size_x_; i++) {
    //     for (int j = 0; j < size_y_; j++) {
    //         field_[i].push_back(FieldCell());
    //     }
    // }
}

Field::Field(const Field& other) :
    //field_(other.field_),
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

    //field_ = other.field_;
    ships_ = other.ships_;
    opened_cells_ = other.opened_cells_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;

    return *this;
}

Field::Field(Field&& other) :
    //field_(std::move(other.field_)),
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

    //field_ = std::move(other.field_);
    ships_ = std::move(other.ships_);
    opened_cells_ = std::move(other.opened_cells_);
    size_x_ = std::move(other.size_x_);
    size_y_ = std::move(other.size_y_);

    return *this;
}

Field::~Field()
{
    // for (int i = 0; i < size_x_; i++) {
    //     field_[i].clear();
    // }

    // field_.clear();

    ships_.clear();
    opened_cells_.clear();
}

void Field::placeShip(Ship* ship, int x, int y, ShipOrientation orientation)
{   
    if (ship == nullptr) {
        throw std::invalid_argument("Ship pointer is nullptr");
    }
        
    int offset_x, offset_y;
    if (orientation == ShipOrientation::horizontal) {
        offset_x = ship->getSize() - 1;
        offset_y = 0;
    } else {
        offset_x = 0;
        offset_y = ship->getSize() - 1;
    }

    if (x < 0 || x >= size_x_ - offset_x || y < 0 || y >= size_y_ - offset_y) {
        throw std::out_of_range("Ship coordinates out of range");
    }

    for (int i = x - 1; i < x + offset_x + 1; i++) {
        if (i >= 0 && i < size_x_) {
            for (int j = y - 1; j < y + offset_y + 1; j++) {
                if (j >= 0 && j < size_y_) {
                    // if (field_[i][j].isShip()) {
                    //     throw std::logic_error("Ships may not contact each other");
                    // }
                    if (ships_.count({i, j}) != 0) {
                        throw std::logic_error("Ships may not contact each other");
                    }
                }   
            }
        }
    }
    
    int segment_index = 0;     
    for (int i = x; i < x + offset_x + 1; i++) {
        for (int j = y; j < y + offset_y + 1; j++) {
            //field_[i][j].setShipSegment(ship, segment_index++);
            ships_[{i, j}] = ShipCell(ship, segment_index++);
        }
    }
}

bool Field::attackCell(int x, int y, int& damage)
{
    if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) {
        throw std::out_of_range("Coordinates out of range");
    }

    if (ships_.count({x, y}) != 0) {
        ships_[{x, y}].attackCell(damage);
        damage = 1;
        opened_cells_[{x, y}] = FieldCell(FieldCellStatus::ship);

        if (ships_[{x, y}].getShipStatus() == ShipStatus::dead) {
            return true;
        }

        return false;
    }
    //field_[x][y].attackCell(damage);
    damage = 1;
    opened_cells_[{x, y}] = FieldCell(FieldCellStatus::empty);
    return false;

    // if (field_[x][y].isShip()) {
    //     field_[x][y].setStatus(FieldCellStatus::ship);

    //     if (field_[x][y].getShipStatus() == ShipStatus::dead) {
    //         return true;
    //     }
    //     return false;
    // } else {
    //     field_[x][y].setStatus(FieldCellStatus::empty);
    //     return false;
    // }
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

    // for (int y = 0; y < size_y_; y++) {
    //     for (int x = 0; x < size_x_; x++) {
    //         if (field_[x][y].getStatus() == FieldCellStatus::unknown) {
    //             std::cout << "[ ]";
    //         } else if (field_[x][y].getStatus() == FieldCellStatus::empty) {
    //             std::cout << "[.]";
    //         } else {
    //             if (field_[x][y].getShipSegmentStatus() == ShipSegmentStatus::intact) {
    //                 std::cout << "[2]";
    //             } else if (field_[x][y].getShipSegmentStatus() == ShipSegmentStatus::damaged) {
    //                 std::cout << "[1]";
    //             } else {
    //                 std::cout << "[0]";
    //             }
    //         }
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "\n";
}

bool Field::isShip(int x, int y) const
{
    if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) {
        throw std::out_of_range("Coordinates out of range");
    }

    return ships_.count({x, y}) != 0;

    // return field_[x][y].isShip();
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

// Field::FieldCell::FieldCell()
// {
//     status_ = FieldCellStatus::unknown;
//     ship_ = nullptr;
//     ship_segment_index_ = -1;
// }

// Field::FieldCell::~FieldCell() = default;

// FieldCellStatus Field::FieldCell::getStatus() const noexcept
// {
//     return status_;
// }

// void Field::FieldCell::setStatus(FieldCellStatus status) noexcept
// {
//     status_ = status;
// }

// void Field::FieldCell::attackCell(int damage)
// {
//     if (ship_ != nullptr) {
//         ship_->damageSegment(ship_segment_index_, damage);
//     }
// }

// bool Field::FieldCell::isShip() const noexcept
// {
//     return ship_ != nullptr;
// }

// void Field::FieldCell::setShipSegment(Ship* ship, int index) noexcept
// {
//     ship_ = ship;
//     ship_segment_index_ = index;
// }

// ShipSegmentStatus Field::FieldCell::getShipSegmentStatus() const noexcept
// {
//     return ship_->getSegmentStatus(ship_segment_index_);
// }

// ShipStatus Field::FieldCell::getShipStatus() const noexcept
// {
//     return ship_->getShipStatus();
// }
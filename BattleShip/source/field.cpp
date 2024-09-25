#include "field.h"
#include "ship.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

Field::Field(int size_x, int size_y)
{
    if (size_x <= 0 || size_y <= 0) {
        throw std::invalid_argument("Field size must be grater than 0");
    }
    size_x_ = size_x;
    size_y_ = size_y;

    field_.resize(size_x_);

    for (int i = 0; i < size_x; i++) {
        field_[i].resize(size_y_);
    }
}

Field::Field(const Field& other) :
    field_(other.field_),
    size_x_(other.size_x_),
    size_y_(other.size_y_)
{}

Field& Field::operator=(const Field& other)
{
    if (this == &other) {
        throw std::logic_error("Can't copy oneself");
    }

    field_ = other.field_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;

    return *this;
}

Field::Field(Field&& other) :
    field_(std::move(other.field_)),
    size_x_(std::move(other.size_x_)),
    size_y_(std::move(other.size_y_))
{}

Field& Field::operator=(Field&& other)
{
    if (this == &other) {
        throw std::logic_error("Can't move to oneself");
    }

    field_ = std::move(other.field_);
    size_x_ = std::move(other.size_x_);
    size_y_ = std::move(other.size_y_);

    return *this;
}

Field::~Field()
{
    for (int i = 0; i < size_x_; i++) {
        field_[i].clear();
    }

    field_.clear();
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
                    if (field_[i][j].isShip()) {
                        throw std::logic_error("Ships may not contact each other");
                    }
                }   
            }
        }
    }

    int segment_index = 0;     
    for (int i = x; i < x + offset_x + 1; i++) {
        for (int j = y; j < y + offset_y + 1; j++) {
            field_[i][j].setShipSegment(ship, segment_index++);
        }
    }
}

void Field::attackCell(int x, int y, int damage)
{
    if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) {
        throw std::out_of_range("Coordinates out of range");
    }

    field_[x][y].attackCell(damage);

    if (field_[x][y].isShip()) {
        field_[x][y].setStatus(FieldCellStatus::ship);
    } else {
        field_[x][y].setStatus(FieldCellStatus::empty);
    }
}

void Field::printField() const
{
    for (int y = 0; y < size_y_; y++) {
        for (int x = 0; x < size_x_; x++) {
            if (field_[x][y].getStatus() == FieldCellStatus::unknown) {
                std::cout << "[ ]";
            } else if (field_[x][y].getStatus() == FieldCellStatus::empty) {
                std::cout << "[.]";
            } else {
                if (field_[x][y].getShipSegmentStatus() == ShipSegmentStatus::intact) {
                    std::cout << "[2]";
                } else if (field_[x][y].getShipSegmentStatus() == ShipSegmentStatus::damaged) {
                    std::cout << "[1]";
                } else {
                    std::cout << "[0]";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Field::FieldCell::FieldCell()
{
    status_ = FieldCellStatus::unknown;
    ship_ = nullptr;
    ship_segment_index_ = -1;
}

FieldCellStatus Field::FieldCell::getStatus() const
{
    return status_;
}

void Field::FieldCell::setStatus(FieldCellStatus status)
{
    status_ = status;
}

void Field::FieldCell::attackCell(int damage)
{
    if (ship_ != nullptr) {
        ship_->damageSegment(ship_segment_index_, damage);
    }
}

bool Field::FieldCell::isShip() const
{
    return ship_ != nullptr;
}

void Field::FieldCell::setShipSegment(Ship* ship, int index)
{
    ship_ = ship;
    ship_segment_index_ = index;
}

ShipSegmentStatus Field::FieldCell::getShipSegmentStatus() const
{
    return ship_->getSegmentStatus(ship_segment_index_);
}

#include "ship.h"

#include <vector>
#include <stdexcept>

Ship::Ship() = default;

Ship::Ship(int size)
{
    if (size < kMinSize || size > kMaxSize) {
        throw std::logic_error("Ship size can be from 1 to 4");
    }

    orientation_ = ShipOrientation::horizontal;
    
    size_ = size;

    for (int i = 0; i < size_; i++) {
        segments_.push_back(ShipSegment());
    }
}

Ship::~Ship()
{
    segments_.clear();
}

int Ship::getSize() const noexcept
{
    return size_;
}

void Ship::setSegmentHealth(int index, int health)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    segments_[index].setHealth(health);
}

int Ship::getSegmentHealth(int index) const
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    return segments_[index].getHealth();
}

ShipSegmentStatus Ship::getSegmentStatus(int index) const
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    return segments_[index].getStatus();
}

ShipStatus Ship::getShipStatus() const noexcept
{
    int dead_flag = 1;
    for (int i = 0; i < size_; i++) {
        if (segments_[i].getStatus() != ShipSegmentStatus::destroyed) {
            dead_flag = 0;
            break;
        }
    }

    if (dead_flag) {
        return ShipStatus::dead;
    } else {
        return ShipStatus::alive;
    }
}

void Ship::damageSegment(int index, int damage)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    segments_[index].takeDamege(damage);
}

void Ship::healSegment(int index, int heal)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    segments_[index].takeHeal(heal);
}

void Ship::setOrientation(ShipOrientation orientation) noexcept
{
    orientation_ = orientation;
}

ShipOrientation Ship::getOrientation() const noexcept
{
    return orientation_;
}

void Ship::setSegmentCoordX(int index, int coord)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    segments_[index].setCoordX(coord);
}

int Ship::getSegmentCoordX(int index)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    return segments_[index].getCoordX();
}

void Ship::setSegmentCoordY(int index, int coord)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    segments_[index].setCoordY(coord);
}

int Ship::getSegmentCoordY(int index)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    return segments_[index].getCoordY();
}

Ship::ShipSegment::ShipSegment()
{
    health_ = kMaxHealth;
    coord_x_ = -1;
    coord_y_ = -1;
}

void Ship::ShipSegment::takeDamege(int damage)
{
    if (damage < 0) {
        throw std::invalid_argument("Damage can't be negative");
    }

    health_ = std::max(0, health_ - damage);
}

void Ship::ShipSegment::takeHeal(int heal)
{
    if (heal < 0) {
        throw std::invalid_argument("Heal can't be negative");
    }

    health_ = std::min(kMaxHealth, health_ + heal);
}

void Ship::ShipSegment::setHealth(int health)
{
    if (health < 0 || health > kMaxHealth) {
        throw std::invalid_argument("Wrong ShipSegment health ammout");
    }

    health_ = health;
}

int Ship::ShipSegment::getHealth() const noexcept
{
    return health_;
}

ShipSegmentStatus Ship::ShipSegment::getStatus() const noexcept
{
    if (health_ == kMaxHealth) {
        return ShipSegmentStatus::intact;
    } else if (health_ == 0) {
        return ShipSegmentStatus::destroyed;
    } else {
        return ShipSegmentStatus::damaged;
    }
}

void Ship::ShipSegment::setCoordX(int coord) noexcept
{
    coord_x_ = coord;
}

int Ship::ShipSegment::getCoordX() const noexcept
{
    return coord_x_;
}

void Ship::ShipSegment::setCoordY(int coord) noexcept
{
    coord_y_ = coord;
}

int Ship::ShipSegment::getCoordY() const noexcept
{
    return coord_y_;
}
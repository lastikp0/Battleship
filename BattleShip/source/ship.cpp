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

//replce get/set SegmentHealth with copy construct

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

void Ship::setOrientation(ShipOrientation orientation) noexcept
{
    orientation_ = orientation;
}

ShipOrientation Ship::getOrientation() const noexcept
{
    return orientation_;
}

void Ship::setHeadX(int head_x) noexcept
{    
    head_x_ = head_x;
}

int Ship::getHeadX() const noexcept
{
    return head_x_;
}

void Ship::setHeadY(int head_y) noexcept
{
    head_y_ = head_y;
}

int Ship::getHeadY(int index) const noexcept
{
    return head_y_;
}

Ship::ShipSegment::ShipSegment()
{
    health_ = kMaxHealth;
}

void Ship::ShipSegment::takeDamege(int damage) noexcept
{
    health_ = std::max(0, health_ - damage);
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

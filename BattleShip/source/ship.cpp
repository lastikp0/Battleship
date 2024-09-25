#include "ship.h"

#include <vector>
#include <stdexcept>

Ship::Ship(int size) : size_(size)
{
    if (size < kMinSize || size > kMaxSize) {
        throw std::logic_error("Ship size can be from 1 to 4");
    }

    for (int i = 0; i < size_; i++) {
        segments_.push_back(ShipSegment());
    }
}

Ship::~Ship()
{
    segments_.clear();
}

int Ship::getSize() const
{
    return size_;
}

ShipSegmentStatus Ship::getSegmentStatus(int index) const
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Ship segment index out of range");
    }

    return segments_[index].getStatus();
}

ShipStatus Ship::getShipStatus() const
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

Ship::ShipSegment::ShipSegment()
{
    health_ = kMaxHealth;
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

ShipSegmentStatus Ship::ShipSegment::getStatus() const
{
    if (health_ == kMaxHealth) {
        return ShipSegmentStatus::intact;
    } else if (health_ == 0) {
        return ShipSegmentStatus::destroyed;
    } else {
        return ShipSegmentStatus::damaged;
    }
}
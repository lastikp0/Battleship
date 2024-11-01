#include "ship.h"

#include <vector>
#include <stdexcept>

Ship::Ship() = default;

Ship::Ship(int size)
{
    if (size < kMinSize || size > kMaxSize) {
        throw std::logic_error("Ship size can be from 1 to 4");
    }
    
    size_ = size;

    for (int i = 0; i < size_; i++) {
        segments_.push_back(ShipSegment());
    }
}

Ship::Ship(const Ship& other) :
    Ship(other.size_)
{
    for (int i = 0; i < size_; i++) {
        segments_[i] = other.segments_[i];
    }
}

Ship& Ship::operator=(const Ship& other)
{
    size_ = other.size_;

    for (int i = 0; i < size_; i++) {
        segments_.push_back(ShipSegment());
        segments_[i] = other.segments_[i];
    }

    return *this;
}

Ship::Ship(Ship&& other) :
    size_(std::move(other.size_)),
    segments_(std::move(other.segments_))
{}

Ship& Ship::operator=(Ship&& other)
{
    size_ = std::move(other.size_);
    segments_ = std::move(other.segments_);

    return *this;
}

Ship::~Ship()
{
    segments_.clear();
}

int Ship::getSize() const noexcept
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

Ship::ShipSegment::ShipSegment()
{
    health_ = kMaxHealth;
}

Ship::ShipSegment::ShipSegment(const ShipSegment& other) :
    health_(other.health_)
{}

Ship::ShipSegment& Ship::ShipSegment::operator=(const ShipSegment& other)
{
    health_ = other.health_;
    return *this;
}

Ship::ShipSegment::ShipSegment(ShipSegment&& other) :
    health_(std::move(other.health_))
{}

Ship::ShipSegment& Ship::ShipSegment::operator=(ShipSegment&& other)
{
    health_ = std::move(other.health_);
    return *this;
}

void Ship::ShipSegment::takeDamege(int damage) noexcept
{
    health_ = std::max(0, health_ - damage);
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

#ifndef SHIP
#define SHIP

#include <vector>
#include <stdexcept>

enum class ShipStatus : int
{
    dead,
    alive
};

enum class ShipSegmentStatus : int
{
    destroyed,
    damaged,
    intact
};

class Ship
{
public:
    Ship(int size);

    ~Ship();

    int getSize() const;

    ShipSegmentStatus getSegmentStatus(int index) const;

    ShipStatus getShipStatus() const;

    void damageSegment(int index, int damage);

    void healSegment(int index, int heal);

private:
    class ShipSegment
    {
    public:
        ShipSegment();

        ~ShipSegment() = default;

        void takeDamege(int damage);

        void takeHeal(int heal);

        ShipSegmentStatus getStatus() const;

    private:
        const int kMaxHealth = 2;
        int health_;
    };

    const int kMinSize = 1;
    const int kMaxSize = 4;
    const int size_;
    std::vector<ShipSegment> segments_;
};

#endif
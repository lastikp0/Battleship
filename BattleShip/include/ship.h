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
    Ship();

    explicit Ship(int size);

    ~Ship();

    int getSize() const noexcept;

    ShipSegmentStatus getSegmentStatus(int index) const;

    ShipStatus getShipStatus() const noexcept;

    void damageSegment(int index, int damage);

    void healSegment(int index, int heal);

private:
    class ShipSegment
    {
    public:
        ShipSegment();

        ~ShipSegment();

        void takeDamege(int damage);

        void takeHeal(int heal);

        ShipSegmentStatus getStatus() const noexcept;

    private:
        int kMaxHealth = 2;
        int health_;
    };

    int kMinSize = 1;
    int kMaxSize = 4;
    int size_;
    std::vector<ShipSegment> segments_;
};

#endif

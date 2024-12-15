#ifndef SHIP
#define SHIP

#include <vector>
#include <stdexcept>
 
enum class ShipOrientation : int
{
    horizontal,
    vertical
};

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

    Ship(const Ship& other);
    Ship& operator=(const Ship& other);
    Ship(Ship&& other);
    Ship& operator=(Ship&& other);

    ~Ship();

    int getSize() const noexcept;

    ShipSegmentStatus getSegmentStatus(int index) const;
    ShipStatus getShipStatus() const noexcept;

    void damageSegment(int index, int damage);
    int getSegmentHealth(int index) const;
    void setSegmentHealth(int index, int health);

    ShipOrientation getOrientation() const noexcept;
    void setOrientation(ShipOrientation orientation) noexcept;

private:
    class ShipSegment
    {
    public:
        ShipSegment();
        ShipSegment(const ShipSegment& other);

        ShipSegment& operator=(const ShipSegment& other);
        ShipSegment(ShipSegment&& other);
        ShipSegment& operator=(ShipSegment&& other);

        ~ShipSegment() = default;

        void takeDamege(int damage) noexcept;

        int getHealth() const noexcept;
        void setHealth(int health);

        ShipSegmentStatus getStatus() const noexcept;

    private:
        int kMaxHealth = 2;
        int health_;
    };

    int kMinSize = 1;
    int kMaxSize = 4;
    int size_;
    std::vector<ShipSegment> segments_;
    ShipOrientation orientation_;
};

#endif

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

    ~Ship();

    int getSize() const noexcept;

    void setSegmentHealth(int index, int health);

    int getSegmentHealth(int index) const;

    ShipSegmentStatus getSegmentStatus(int index) const;

    ShipStatus getShipStatus() const noexcept;

    void damageSegment(int index, int damage);

    void setOrientation(ShipOrientation orientation) noexcept;

    ShipOrientation getOrientation() const noexcept;

    void setHeadX(int head_x) noexcept;

    int getHeadX() const noexcept;

    void setHeadY(int head_y) noexcept;

    int getHeadY() const noexcept;

private:
    class ShipSegment
    {
    public:
        ShipSegment();

        ~ShipSegment() = default;

        void takeDamege(int damage) noexcept;

        void setHealth(int health);

        int getHealth() const noexcept;

        ShipSegmentStatus getStatus() const noexcept;

    private:
        int kMaxHealth = 2;
        int health_;
    };

    int kMinSize = 1;
    int kMaxSize = 4;
    int size_;
    ShipOrientation orientation_;
    int head_x_;
    int head_y_;
    std::vector<ShipSegment> segments_;
};

#endif

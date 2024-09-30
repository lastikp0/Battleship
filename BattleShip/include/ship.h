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

    void healSegment(int index, int heal);

    void setOrientation(ShipOrientation orientation) noexcept;

    ShipOrientation getOrientation() const noexcept;

    void setSegmentCoordX(int index, int coord);

    int getSegmentCoordX(int index);

    void setSegmentCoordY(int index, int coord);

    int getSegmentCoordY(int index);

private:
    class ShipSegment
    {
    public:
        ShipSegment();

        ~ShipSegment() = default;

        void takeDamege(int damage);

        void takeHeal(int heal);

        void setHealth(int health);

        int getHealth() const noexcept;

        ShipSegmentStatus getStatus() const noexcept;

        void setCoordX(int coord) noexcept;

        int getCoordX() const noexcept;

        void setCoordY(int coord) noexcept;

        int getCoordY() const noexcept;

    private:
        int kMaxHealth = 2;
        int health_;
        int coord_x_;
        int coord_y_;
    };

    int kMinSize = 1;
    int kMaxSize = 4;
    int size_;
    ShipOrientation orientation_;
    std::vector<ShipSegment> segments_;
};

#endif

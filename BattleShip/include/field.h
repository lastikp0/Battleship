#ifndef FIELD
#define FIELD

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "ship.h"
 
enum class ShipOrientation : int
{
    horizontal,
    vertical
};

enum class FieldCellStatus : int
{
    unknown,
    empty,
    ship
};

class Field
{
public:
    Field(int size_x, int size_y);

    Field(Field& other);

    Field& operator=(Field& other);

    Field(Field&& other);

    Field& operator=(Field&& other);

    ~Field();

    void placeShip(Ship* ship, int x, int y, ShipOrientation orientation);

    void attackCell(int x, int y, int damage);

    void printField();

private:
    class FieldCell
    {
    public:
        FieldCell();

        ~FieldCell() = default;

        FieldCellStatus getStatus();

        void setStatus(FieldCellStatus status);

        void attackCell(int damage);

        bool isShip();

        void setShipSegment(Ship* ship, int index);

        ShipSegmentStatus getShipSegmentStatus();

    private:
        FieldCellStatus status_;
        Ship* ship_;
        int ship_segment_index_;
    };

    int size_x_;
    int size_y_;
    std::vector<std::vector<FieldCell>> field_;
};

#endif
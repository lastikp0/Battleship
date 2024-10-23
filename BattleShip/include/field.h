#ifndef FIELD
#define FIELD

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

#include "ship.h"

enum class FieldCellStatus : int
{
    unknown,
    empty,
    ship
};

struct Coords
{
    int x;
    int y;

    bool operator==(const Coords& other) const;
};

struct CoordsHash
{
    std::size_t operator()(const Coords& coords) const;
};

class Field
{
public:
    Field();

    explicit Field(int size_x, int size_y);

    Field(const Field& other);

    Field& operator=(const Field& other);

    Field(Field&& other);

    Field& operator=(Field&& other);

    ~Field();

    void placeShip(Ship* ship, int x, int y, ShipOrientation orientation);

    bool attackCell(int x, int y, int& damage);

    void printField() const noexcept;

    bool isShip(int x, int y) const;

private:
    // class FieldCell
    // {
    // public:
    //     FieldCell();

    //     ~FieldCell();

    //     FieldCellStatus getStatus() const noexcept;

    //     void setStatus(FieldCellStatus status) noexcept;

    //     void attackCell(int damage);

    //     bool isShip() const noexcept;

    //     void setShipSegment(Ship* ship, int index) noexcept;

    //     ShipSegmentStatus getShipSegmentStatus() const noexcept;

    //     ShipStatus getShipStatus() const noexcept;

    // private:
    //     FieldCellStatus status_;
    //     Ship* ship_;
    //     int ship_segment_index_;
    // };

    class ShipCell
    {
    public:
        ShipCell();

        explicit ShipCell(Ship* ship, int index);

        ~ShipCell();

        void attackCell(int damage);

        void setShipSegment(Ship* ship, int index) noexcept;

        ShipSegmentStatus getShipSegmentStatus() const noexcept;

        ShipStatus getShipStatus() const noexcept;

    private:
        Ship* ship_;
        int ship_segment_index_;
    };

    class FieldCell
    {
    public:
        FieldCell();

        explicit FieldCell(FieldCellStatus status);

        ~FieldCell();

        FieldCellStatus getStatus() const noexcept;

        void setStatus(FieldCellStatus status) noexcept;

    private:
        FieldCellStatus status_;
    };

    int size_x_;
    int size_y_;
    //std::vector<std::vector<FieldCell>> field_;

    std::unordered_map<Coords, ShipCell, CoordsHash> ships_;
    std::unordered_map<Coords, FieldCell, CoordsHash> opened_cells_;
};

#endif
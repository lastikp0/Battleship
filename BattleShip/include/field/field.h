#ifndef FIELD
#define FIELD

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <string>

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

    void placeShip(Ship* ship, Coords coords, ShipOrientation orientation);

    bool attackCell(Coords coords, int damage);

    void printField() const noexcept;

    bool isShip(Coords coords) const;

    FieldCellStatus getCellStatus(Coords coords) const;
    ShipSegmentStatus getShipSegmentStatus(Coords coords) const;

    Coords getSize() const noexcept;

    void getRandomShip(Ship** ship, int& index) const noexcept;

    std::string getField() const noexcept;
    std::string getShips() const noexcept;
    void setField(std::vector<std::vector<char>>& info);

private:
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
        void getShipSegment(Ship** ship, int& index) const noexcept;

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

    std::unordered_map<Coords, ShipCell, CoordsHash> ships_;
    std::unordered_map<Coords, FieldCell, CoordsHash> opened_cells_;
};

#endif
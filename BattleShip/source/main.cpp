#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    Field field(5, 5);

    ShipManager ship_manager({1, 2, 3, 4});

    ship_manager.printShips();

    ship_manager.placeShip(field, 2, 1, 1, ShipOrientation::horizontal);

    ship_manager.printShips();

    field.attackCell(0, 1, 1);
    field.attackCell(1, 1, 1);
    field.attackCell(2, 1, 1);
    field.attackCell(3, 0, 1);
    field.attackCell(4, 1, 1);

    field.printField();

    ship_manager.printShips();

    return 0;
}
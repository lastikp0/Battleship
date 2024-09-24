#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    Field field(10, 10);

    Ship ship1(4);

    Ship ship2(3);

    field.placeShip(&ship1, 1, 1, ShipOrientation::horizontal);
    // field.placeShip(&ship2, 1, 1, ShipOrientation::vertical);
    // field.placeShip(&ship2, 0, 0, ShipOrientation::vertical);
    field.placeShip(&ship2, 3, 3, ShipOrientation::vertical);

    field.attackCell(0, 0, 1);
    field.attackCell(1, 1, 3);
    field.attackCell(3, 4, 1);
    field.attackCell(4, 3, 1);

    field.printField();

    return 0;
}
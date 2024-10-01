#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    ShipManager manager({1, 3, 4});
    manager.printShips();

    Field field(5, 5);

    manager.placeShip(&field, 1, 0, 0, ShipOrientation::horizontal);
    manager.printShips();

    field.attackCell(0, 0, 1);
    field.attackCell(1, 0, 0);
    field.attackCell(3, 0, 0);
    field.attackCell(0, 1, 0);
    field.attackCell(1, 1, 0);
    field.attackCell(2, 1, 0);
    field.attackCell(3, 1, 0);

    manager.printShips();

    Field field_copy(field);
    manager.copyShipsFromOldToNewField(&field, &field_copy);

    manager.printShips();
    field.attackCell(2, 0, 1);
    field.printField();
    field_copy.printField();
}

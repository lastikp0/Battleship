#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    Ship test_ship_1(2); // OK

    test_ship_1.damageSegment(0, 1); // OK

    ShipManager manager({1, 3, 4});
    manager.printShips();

    Field field(5, 5);

    manager.placeShip(&field, 1, 0, 0, ShipOrientation::horizontal); // OK

    Field field_copy(field);

    manager.addShip(2);

    manager.printShips();

    field.attackCell(0, 0, 1); // OK
    manager.copyShipsFromOldToNewField(&field, &field_copy);

    field.attackCell(1, 0, 0);
    field.attackCell(2, 0, 1);
    field.attackCell(3, 0, 0);
    field.attackCell(0, 1, 0);
    field.attackCell(1, 1, 0);
    field.attackCell(2, 1, 0);
    field.attackCell(3, 1, 0);
    
    manager.printShips();
    field.printField();

    field_copy.attackCell(0, 0, 0);
    field_copy.attackCell(1, 0, 0);
    field_copy.attackCell(2, 0, 0);
    field_copy.attackCell(3, 0, 0);
    field_copy.attackCell(0, 1, 0);
    field_copy.attackCell(1, 1, 0);
    field_copy.attackCell(2, 1, 0);
    field_copy.attackCell(3, 1, 0);
    field_copy.printField();
}

#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    Ship test_ship_1(2); // OK
    Ship test_ship_2(0); // Error
    Ship test_ship_3(5); // Error

    test_ship_1.damageSegment(0, 1); // OK
    test_ship_1.damageSegment(0, -1); // Error
    test_ship_1.damageSegment(3, 1); // Error

    ShipManager manager({1, 3, 4});
    manager.printShips();

    Field field(5, 5);

    manager.placeShip(field, 1, 0, 0, ShipOrientation::horizontal); // OK
    manager.placeShip(field, 1, 0, 3, ShipOrientation::horizontal); // Error
    manager.placeShip(field, 2, 0, 0, ShipOrientation::vertical); // Error
    manager.placeShip(field, 2, 3, 0, ShipOrientation::vertical); // Error

    manager.addShip(2);

    manager.printShips();
    field.attackCell(0, 0, 1); // OK
    field.attackCell(6, 10, 1); // Error

    field.attackCell(1, 0, 0);
    field.attackCell(2, 0, 1);
    field.attackCell(3, 0, 0);
    field.attackCell(0, 1, 0);
    field.attackCell(1, 1, 0);
    field.attackCell(2, 1, 0);
    field.attackCell(3, 1, 0);
    
    manager.printShips();
    field.printField();
}

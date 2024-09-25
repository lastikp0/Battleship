#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    Field field(10, 10);

    ShipManager ship_manager({4, 3, 2});

    ship_manager.printShips();

    ship_manager.placeShips(field, {{1,1,ShipOrientation::horizontal}, {3,3,ShipOrientation::vertical}, {0,9,ShipOrientation::horizontal}});

    field.attackCell(1, 1, 1);
    field.attackCell(2, 1, 1);
    field.attackCell(3, 1, 1);
    field.attackCell(4, 1, 1);

    ship_manager.printShips();

    field.attackCell(3, 3, 1);
    field.attackCell(3, 4, 1);
    field.attackCell(3, 5, 1);

    field.attackCell(0, 9, 1);
    field.attackCell(1, 9, 1);

    field.printField();
    ship_manager.printShips();

    return 0;
}
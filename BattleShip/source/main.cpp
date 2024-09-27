#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    ShipManager ship_manager({1, 3, 4});
    ship_manager.printShips();

    Field field(5,5);

    ship_manager.placeShip(field, 0, 1, 1, ShipOrientation::horizontal);
    ship_manager.placeShip(field, 2, 0, 3, ShipOrientation::horizontal);

    ship_manager.addShip(2);

    ship_manager.printShips();
    field.printField();

    return 0;
}
#include <iostream>
#include "ship.h"
#include "shipManager.h"
#include "field.h"

int main()
{
    int playerDamage = 1;

    ShipManager ship_manager({1, 2, 3, 4});

    ship_manager.printShips();

    Field field(5, 5);

    field.placeShip(ship_manager.getUnusedShip(2), 0, 0, ShipOrientation::horizontal);
    ship_manager.makeShipUsed(2);

    ship_manager.printShips();
    field.printField();

    Field new_field(field);

    field.attackCell(0, 0, playerDamage);
    new_field.attackCell(0, 0, playerDamage);

    ship_manager.printShips();
    field.printField();
    new_field.printField();

    playerDamage *= 2;
    if (field.attackCell(1, 0, playerDamage)) {
        std::cout << "+\n";
    } else {
        std::cout << "-\n";
    }
    
    playerDamage *= 2;
    if (field.attackCell(2, 0, playerDamage)) {
        std::cout << "+\n";
    } else {
        std::cout << "-\n";
    }

    return 0;
}

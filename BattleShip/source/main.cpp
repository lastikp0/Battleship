#include <iostream>

#include "ship.h"
#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"
#include "noAbilityException.h"
#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

int main()
{
    int playerDamage = 1;
    bool scan_result;

    ShipManager ship_manager({1, 2, 3, 4});
    Field field(5, 5);
    AbilityManager ability_manager;

    field.placeShip(ship_manager.getUnusedShip(2), {0, 0}, ShipOrientation::horizontal);
    ship_manager.makeShipUsed(2);
    field.placeShip(ship_manager.getUnusedShip(0), {4, 4}, ShipOrientation::horizontal);
    ship_manager.makeShipUsed(0);

    field.attackCell({0, 0}, 0);
    field.attackCell({1, 0}, 0);
    field.attackCell({2, 0}, 0);

    std::cout << "Ability count: " << ability_manager.size() << "\n\n";

    if (field.attackCell({4, 4}, 2)) {
        ability_manager.addAbility();
    }

    ship_manager.printShips();
    field.printField();

    std::cout << "Ability count: " <<  ability_manager.size() << "\n\n";

    AbilityType a_type;

    while (ability_manager.size() > 0) {
        a_type = ability_manager.getAbility();

        if (a_type == AbilityType::DoubleDamage) {
            std::cout << "Double Damage:\n";
            DoubleDamageSettings settings(playerDamage);
            ability_manager.castAbility(&settings);

            field.attackCell({0 ,0}, playerDamage);
            ship_manager.printShips();
            field.printField();
        } else if (a_type == AbilityType::Scanner) {
            std::cout << "Scanner:\n";
            ScannerSettings settings(field, {0, 0}, scan_result);
            ability_manager.castAbility(&settings);

            if (scan_result) {
                std::cout << "Ship\n\n";
            } else {
                std::cout << "No ship\n\n";
            }
        } else {
            std::cout << "Bombardment:\n";
            BombardmentSettings settings(field, playerDamage);
            ability_manager.castAbility(&settings);

            ship_manager.printShips();
            field.printField();
            playerDamage = 1;
        }
    }
    
    std::cout << "Ability count: " <<  ability_manager.size() << "\n\n";

    try
    {
        DoubleDamageSettings settings(playerDamage);
        ability_manager.castAbility(&settings);
    }
    catch(const NoAbilityException& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        field.placeShip(ship_manager.getUnusedShip(0), {0, 1}, ShipOrientation::vertical);
        ship_manager.makeShipUsed(0);
    }
    catch(const ShipPlacementException& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        field.placeShip(ship_manager.getUnusedShip(0), {0, 4}, ShipOrientation::vertical);
        ship_manager.makeShipUsed(0);
    }
    catch(const ShipPlacementException& e)
    {
        std::cout << e.what() << '\n';
    }

    try
    {
        field.attackCell({5, 5}, playerDamage);
    }
    catch(const AttackOutOfRangeException& e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}
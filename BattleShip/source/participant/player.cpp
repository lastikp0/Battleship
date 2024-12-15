#include "player.h"

#include "field.h"
#include "shipManager.h"
#include "abilityManager.h"

#include "debug_CLI.h"

Player::Player() :
    Participant(),
    ability_manager(nullptr)
{}

Player::Player(Coords field_size, std::vector<int> ship_sizes) :
    Participant(field_size, ship_sizes)
{
    ability_manager = new AbilityManager();
}

Player::~Player()
{
    delete field;
    delete ship_manager;
    delete ability_manager;
}

void Player::placeShips()
{
    //debug message
    std::cout << "Placing player ships\n";

    while (ship_manager->getUnusedShipSize() > 0) {
        InputShip* input_ship = getInputShip(this);

        Ship* ship;
        try
        {
            ship = ship_manager->getUnusedShip(input_ship->ship_index);
        }
        catch(const std::out_of_range& e)
        {
            std::cout << e.what() << '\n';
            continue;
        }

        try
        {
            if (input_ship->orientation == 1) {
                field->placeShip(ship, input_ship->coords, ShipOrientation::vertical);
            } else if (input_ship->orientation == 0) {
                field->placeShip(ship, input_ship->coords, ShipOrientation::horizontal);
            } else {
                throw std::invalid_argument("Ship must be horizontal(0) or vertical(1)");
            }
        }
        catch(const ShipPlacementException& e)
        {
            std::cout << e.what() << '\n';
            continue;
        }
        
        ship_manager->makeShipUsed(input_ship->ship_index);
    }

    //debug message
    std::cout << "Player ships placed\n";
}

bool Player::attackCell(Participant* target)
{
    Coords coords;
    bool success = false;
    bool attack_result;

    while (!success) {
        coords = getCoords(target);

        try
        {
            attack_result = target->field->attackCell(coords, damage);
        }
        catch(const AttackOutOfRangeException& e)
        {
            std::cout << e.what() << '\n';
            continue;
        }
        
        success = true;
    }

    damage = 1;
    //debug mode
    std::cout << "Target:\n";
    target->field->printField();

    return attack_result;
}

void Player::castAbility(Participant* target)
{
    AbilityType a_type;
    a_type = ability_manager->getAbility();

    if (a_type == AbilityType::DoubleDamage) {
        //debug message
        std::cout << "Double Damage\n";

        DoubleDamageSettings settings(damage);
        ability_manager->castAbility(&settings);
    } else if (a_type == AbilityType::Scanner) {
        //debug message
        std::cout << "Scanner:\n";

        Coords coords = getCoords(target);
        bool scan_result;

        ScannerSettings settings(*(target->field), coords, scan_result);
        ability_manager->castAbility(&settings);

        //debug mode
        if (scan_result) {
            std::cout << "Ship\n\n";
        } else {
            std::cout << "No ship\n\n";
        }
    } else {
        //debug message
        std::cout << "Bombardment\n";

        BombardmentSettings settings(*(target->field), damage);
        ability_manager->castAbility(&settings);
        damage = 1;
    }
}

void Player::addAbility()
{
    ability_manager->addAbility();
}

AbilityType Player::getAbility()
{
    return ability_manager->getAbility();
}
#include "bot.h"

#include <ctime>

#include "field.h"
#include "shipManager.h"

Bot::Bot() :
    Participant()
{}

Bot::Bot(Coords field_size, std::vector<int> ship_sizes) :
    Participant(field_size, ship_sizes)
{}

Bot::~Bot()
{
    delete field;
    delete ship_manager;
}

void Bot::placeShips()
{
    //debug message
    std::cout << "Placing bot ships\n";

    Ship* ship;

    ship = ship_manager->getUnusedShip(0);
    field->placeShip(ship, {0, 0}, ShipOrientation::horizontal);

    // ship = ship_manager.getUnusedShip(1);
    // field.placeShip(ship, {2, 1}, ShipOrientation::vertical);

    // ship = ship_manager.getUnusedShip(2);
    // field.placeShip(ship, {0, 2}, ShipOrientation::vertical);

    // ship = ship_manager.getUnusedShip(3);
    // field.placeShip(ship, {4, 1}, ShipOrientation::vertical);


    while (ship_manager->getUnusedShipSize() > 0) {
        ship_manager->makeShipUsed(0);
    }

    //debug message
    std::cout << "Bot ships placed\n";
}

bool Bot::attackCell(Participant* target)
{
    Coords coords;
    coords.x = 0;
    coords.y = 0;

    bool attack_result;
    attack_result = target->field->attackCell(coords, damage);
    damage = 1;

    //debug mode
    std::cout << "Target:\n";
    target->field->printField();

    return attack_result;
}
#include "debug_CLI.h"

#include <iostream>
#include <ctime>
#include <vector>

#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"

#include "participant.h"
#include "bot.h"
#include "player.h"

#include "noAbilityException.h"
#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

PlayerStats* getPlayerStats()
{
    PlayerStats* player_stats = new PlayerStats();
    std::cout << "Input field horizontal size(x): ";
    std::cin >> player_stats->field_size.x;

    std::cout << "Input field vertical size(y): ";
    std::cin >> player_stats->field_size.y;

    int ship_count;

    std::cout << "Input ship count: ";
    std::cin >> ship_count;

    int ship_size;

    for (int i = 0; i < ship_count; i++) {
        std::cout << "Input ship size: ";
        std::cin >> ship_size;
        player_stats->ship_sizes.push_back(ship_size);
    }

    return player_stats;
}

InputShip* getInputShip(Player* player)
{
    InputShip* input_ship = new InputShip();

    player->ship_manager->printShips();
    std::cout << "Input ship index: ";
    std::cin >> input_ship->ship_index;

    player->field->printField();
    std::cout << "Input ship horizontal coordinate(x): ";
    std::cin >> input_ship->coords.x;
    std::cout << "Input ship vertical coordinate(y): ";
    std::cin >> input_ship->coords.y;
    std::cout << "Input ship orientation (0 - h, 1 - v): ";
    std::cin >> input_ship->orientation;

    return input_ship;
}

Coords getCoords(Participant* target)
{
    Coords coords;

    target->field->printField();
    std::cout << "Input ship horizontal coordinate(x): ";
    std::cin >> coords.x;
    std::cout << "Input ship vertical coordinate(y): ";
    std::cin >> coords.y;

    return coords;
}

int getCommand()
{
    int command;
    std::cout << "Input command (0 - attackCell, 1 - castAbility, 2 - save, 3 - load): ";
    std::cin >> command;
    
    return command;
}
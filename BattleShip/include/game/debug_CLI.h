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

struct PlayerStats
{
    Coords field_size;
    std::vector<int> ship_sizes;
};

//debug only
PlayerStats* getPlayerStats();

struct InputShip
{
    int ship_index;
    Coords coords;
    int orientation;
};

//debug only
InputShip* getInputShip(Player* player);

//debug only
Coords getCoords(Participant* target);

//debug only
int getCommand();
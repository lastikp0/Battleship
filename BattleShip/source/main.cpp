#include <iostream>
#include <ctime>

#include "shipManager.h"
#include "field.h"
#include "abilityManager.h"
#include "game.h"

#include "noAbilityException.h"
#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

#include "hasher.h"

int main()
{
    srand(time(0));

    Game game;
    game.start(1, 1);

    return 0;
}
#include "player.h"

#include "field.h"
#include "shipManager.h"
#include "abilityManager.h"

Player::Player() :
    Participant()
{
    ability_manager = nullptr;
}

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

bool Player::isBot()
{
    return false;
}

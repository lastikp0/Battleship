#ifndef PLAYER
#define PLAYER

#include "participant.h"

#include "field.h"
#include "shipManager.h"
#include "abilityManager.h"

struct Player: public Participant
{
    AbilityManager* ability_manager;

    Player();
	Player(Coords field_size, std::vector<int> ship_sizes);
    ~Player();

    void placeShips() override;
    bool attackCell(Participant* target) override;
    
    void castAbility(Participant* target);
    void addAbility();
    AbilityType getAbility();
};

#endif
#ifndef PLAYER
#define PLAYER

#include "participant.h"

struct Player: public Participant
{
    Player();
	Player(Coords field_size, std::vector<int> ship_sizes);
    ~Player();
    
    bool isBot() override;
};

#endif

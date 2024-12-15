#ifndef BOT
#define BOT

#include "participant.h"

#include <ctime>

#include "field.h"
#include "shipManager.h"

struct Bot: public Participant
{
    Bot();
	Bot(Coords field_size, std::vector<int> ship_sizes);
    ~Bot();

    void placeShips() override;
    bool attackCell(Participant* target) override;
};

#endif
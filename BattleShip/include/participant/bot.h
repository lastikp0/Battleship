#ifndef BOT
#define BOT

#include "participant.h"

struct Bot: public Participant
{
    Bot();
	Bot(Coords field_size, std::vector<int> ship_sizes);
    ~Bot();

    bool isBot() override;
};

#endif
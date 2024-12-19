#include "bot.h"

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

bool Bot::isBot()
{
    return true;
}
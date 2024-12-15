#include "participant.h"

#include "field.h"
#include "shipManager.h"

Participant::Participant() :
    field(nullptr),
    ship_manager(nullptr)
{}

Participant::Participant(Coords field_size, std::vector<int> ship_sizes)
{
    field = new Field(field_size.x, field_size.y);
    ship_manager = new ShipManager(ship_sizes);
}

bool Participant::isAlive()
{
    return ship_manager->getAliveShipSize() > 0;
}

bool Participant::ready()
{
    return ship_manager->getUnusedShipSize() == 0;
}
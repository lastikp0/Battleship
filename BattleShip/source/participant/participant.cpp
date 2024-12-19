#include "participant.h"

#include "field.h"
#include "shipManager.h"

#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

Participant::Participant() :
    field(nullptr),
    ship_manager(nullptr)
{}

Participant::Participant(Coords field_size, std::vector<int> ship_sizes)
{
    field = new Field(field_size.x, field_size.y);
    ship_manager = new ShipManager(ship_sizes);
}

void Participant::placeShip(int index, Coords coords, ShipOrientation orientation)
{
    Ship* ship = ship_manager->getUnusedShip(index);

    field->placeShip(ship, coords, orientation);

    ship_manager->makeShipUsed(index);
}

bool Participant::attackCell(Participant* target, Coords coords)
{
    bool attack_result;

    attack_result = target->field->attackCell(coords, damage);

    damage = 1;

    return attack_result;
}

bool Participant::isAlive()
{
    return ship_manager->getAliveShipSize() > 0;
}

bool Participant::ready()
{
    if (ship_manager == nullptr) {
        return false;
    }
    
    return ship_manager->getUnusedShipSize() == 0;
}
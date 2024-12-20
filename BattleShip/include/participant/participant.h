#ifndef PARTICIPANT
#define PARTICIPANT

#include <vector>

#include "field.h"
#include "shipManager.h"
#include "abilityManager.h"

#include "shipPlacementException.h"
#include "attackOutOfRangeException.h"

struct Participant
{
	Field* field;
	ShipManager* ship_manager;
	AbilityManager* ability_manager;
	int damage = 1;

	Participant();
	Participant(Coords field_size, std::vector<int> ship_sizes);
	
	void placeShip(int index, Coords coords, ShipOrientation orientation);

	bool attackCell(Participant* target, Coords coords);

	virtual bool isBot() = 0;

	bool isAlive();
	bool ready();
};
#endif

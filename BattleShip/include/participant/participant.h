#ifndef PARTICIPANT
#define PARTICIPANT

#include <vector>

#include "field.h"
#include "shipManager.h"

struct Participant
{
	Field* field;
	ShipManager* ship_manager;
	int damage = 1;

	Participant();
	Participant(Coords field_size, std::vector<int> ship_sizes);

	virtual void placeShips() = 0;
	virtual bool attackCell(Participant* target) = 0;

	bool isAlive();
	bool ready();
};
#endif
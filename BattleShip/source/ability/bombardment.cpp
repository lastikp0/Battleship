#include "bombardment.h"

#include "iAbility.h"
#include "field.h"

Bombardment::Bombardment(Field& field, int damage) :
    field_(field),
    damage_(damage)
{}

Bombardment::~Bombardment() = default;

void Bombardment::cast()
{
    Ship* ship;
    int index;
    field_.getRandomShip(&ship, index);

    ship->damageSegment(index, damage_);
}
#include "doubleDamage.h"

#include "iAbility.h"

DoubleDamage::DoubleDamage(int& damage) :
    damage_(damage)
{}

DoubleDamage::~DoubleDamage() = default;

void DoubleDamage::cast()
{
    damage_ *= 2;
}
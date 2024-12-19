#include "doubleDamageSettings.h"

#include "iAbilitySettings.h"
#include "iVisitor.h"

DoubleDamageSettings::DoubleDamageSettings(int& damage) :
    damage_(damage)
{}

DoubleDamageSettings::~DoubleDamageSettings() = default;

AbilityType DoubleDamageSettings::getType()
{
    return AbilityType::DoubleDamage;
}

void DoubleDamageSettings::acceptVisitor(IVisitor& visitor)
{
    visitor.visit(this);
}
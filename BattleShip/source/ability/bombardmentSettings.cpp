#include "bombardmentSettings.h"

#include "iAbilitySettings.h"
#include "iVisitor.h"
#include "field.h"

BombardmentSettings::BombardmentSettings(Field& field, int damage) :
    field_(field),
    damage_(damage)
{}

BombardmentSettings::~BombardmentSettings() = default;

AbilityType BombardmentSettings::getType()
{
    return AbilityType::Bombardment;
}

void BombardmentSettings::acceptVisitor(IVisitor& visitor)
{
    visitor.visit(this);
}
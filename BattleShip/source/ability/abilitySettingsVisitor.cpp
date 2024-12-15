#include "abilitySettingsVisitor.h"

#include "abilityFactory.h"

AbilitySettingsVisitor::AbilitySettingsVisitor(AbilityFactory& factory) :
    factory_(factory)
{}

AbilitySettingsVisitor::~AbilitySettingsVisitor() = default;

void AbilitySettingsVisitor::visit(DoubleDamageSettings* settings)
{
    factory_.buildDoubleDamage(settings);
}

void AbilitySettingsVisitor::visit(ScannerSettings* settings)
{
    factory_.buildScanner(settings);
}

void AbilitySettingsVisitor::visit(BombardmentSettings* settings)
{
    factory_.buildBombardment(settings);
}
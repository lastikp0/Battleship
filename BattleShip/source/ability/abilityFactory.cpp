#include "abilityFactory.h"

#include "iAbility.h"

#include "doubleDamage.h"
#include "doubleDamageSettings.h"

#include "scanner.h"
#include "scannerSettings.h"

#include "bombardment.h"
#include "bombardmentSettings.h"

AbilityFactory::AbilityFactory() = default;

AbilityFactory::~AbilityFactory() = default;

IAbility* AbilityFactory::getAbility()  const noexcept
{
    return ability_;
}

void AbilityFactory::buildDoubleDamage(DoubleDamageSettings* settings)
{
    ability_ = new DoubleDamage(settings->damage_);
}

void AbilityFactory::buildScanner(ScannerSettings* settings)
{
    ability_ = new Scanner(settings->field_, settings->coords_, settings->scan_result_);
}

void AbilityFactory::buildBombardment(BombardmentSettings* settings)
{
    ability_ = new Bombardment(settings->field_, settings->damage_);
}
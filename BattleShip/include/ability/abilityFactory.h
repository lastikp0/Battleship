#ifndef ABILITY_FACTORY
#define ABILITY_FACTORY

#include "iAbility.h"

#include "doubleDamage.h"
#include "doubleDamageSettings.h"

#include "scanner.h"
#include "scannerSettings.h"

#include "bombardment.h"
#include "bombardmentSettings.h"


class AbilityFactory
{
public:
    AbilityFactory();
    ~AbilityFactory();

    IAbility* getAbility() const noexcept;

    void buildDoubleDamage(DoubleDamageSettings* settings);
    void buildScanner(ScannerSettings* settings);
    void buildBombardment(BombardmentSettings* settings);

private:
    IAbility* ability_ = nullptr;
};

#endif
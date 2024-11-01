#ifndef ABILITY_MANAGER
#define ABILITY_MANAGER

#include <queue>
#include <vector>
#include <ctime>

#include "abilityFactory.h"
#include "iAbility.h"
#include "abilitySettingsVisitor.h"

class AbilityManager
{
public:
    AbilityManager();

    ~AbilityManager();

    int size() const noexcept;

    AbilityType getAbility() const;

    void castAbility(IAbilitySettings* settings);

    void addAbility();

private:
    IAbility* buildAbility(IAbilitySettings* settings);

    int kAbilitiesNum = 3;

    std::queue<AbilityType> abilities_;
    AbilityFactory factory_;
    AbilitySettingsVisitor visitor_;
};

#endif
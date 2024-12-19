#ifndef ABILITY_MANAGER
#define ABILITY_MANAGER

#include <vector>
#include <string>

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

    std::string getAllAbilities() const noexcept;
    void setAbilities(std::vector<int>& info);

private:
    IAbility* buildAbility(IAbilitySettings* settings);

    std::vector<AbilityType> kAbilitiesType = {AbilityType::DoubleDamage, AbilityType::Scanner, AbilityType::Bombardment};

    std::vector<AbilityType> abilities_;
    AbilityFactory factory_;
    AbilitySettingsVisitor visitor_;
};

#endif
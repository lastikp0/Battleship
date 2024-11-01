#include "abilityManager.h"

#include <queue>
#include <vector>
#include <ctime>

#include "abilityFactory.h"
#include "iAbility.h"
#include "abilitySettingsVisitor.h"

#include "noAbilityException.h"

AbilityManager::AbilityManager() :
    visitor_(factory_)
{
    srand(time(0));

    std::vector<AbilityType> abilitiesType = {AbilityType::DoubleDamage, AbilityType::Scanner, AbilityType::Bombardment};
    int ability_index;

    for (int i = 0; i < kAbilitiesNum; i++) {
        ability_index = rand() % abilitiesType.size();
        abilities_.push(abilitiesType[ability_index]);
        abilitiesType.erase(abilitiesType.begin() + ability_index);
    }
}

AbilityManager::~AbilityManager() = default;

int AbilityManager::size() const noexcept
{
    return abilities_.size();
}

AbilityType AbilityManager::getAbility() const
{
    if (this->size() == 0) {
        throw NoAbilityException("No abilities avaliable");
    }
    
    return abilities_.front();
}

void AbilityManager::castAbility(IAbilitySettings* settings)
{
    if (this->size() == 0) {
        throw NoAbilityException("No abilities avaliable");
    }

    if(settings->getType() != abilities_.front()) {
        throw std::logic_error("Invalid ability settings type");
    }
    
    IAbility* ability = this->buildAbility(settings);

    ability->cast();

    delete ability;

    abilities_.pop();
}

void AbilityManager::addAbility()
{
    int ability_index = rand() % kAbilitiesNum;
    
    switch (ability_index)
    {
    case 0:
    {
        abilities_.push(AbilityType::DoubleDamage);
        break;
    }

    case 1:
    {
        abilities_.push(AbilityType::Scanner);
        break;
    }

    case 2:
    {
        abilities_.push(AbilityType::Bombardment);
        break;
    }
    
    default:
        break;
    }
}

IAbility* AbilityManager::buildAbility(IAbilitySettings* settings)
{
    settings->acceptVisitor(visitor_);
    
    return factory_.getAbility();
}
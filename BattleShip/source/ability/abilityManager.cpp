#include "abilityManager.h"

#include <vector>
#include <string>

#include "abilityFactory.h"
#include "iAbility.h"
#include "abilitySettingsVisitor.h"

#include "noAbilityException.h"

AbilityManager::AbilityManager() :
    visitor_(factory_)
{
    for (int i = 0; i < kAbilitiesType.size(); i++) {
        int j = rand() % kAbilitiesType.size();

        std::swap(kAbilitiesType[i], kAbilitiesType[j]);
    }

    for (int i = 0; i < kAbilitiesType.size(); i++) {
        abilities_.push_back(kAbilitiesType[i]);
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

    abilities_.erase(abilities_.begin());
}

void AbilityManager::addAbility()
{
    int index = rand() % kAbilitiesType.size();
    abilities_.push_back(kAbilitiesType[index]);
}

IAbility* AbilityManager::buildAbility(IAbilitySettings* settings)
{
    settings->acceptVisitor(visitor_);
    
    return factory_.getAbility();
}

std::string AbilityManager::getAllAbilities() const noexcept
{
    std::string result = "";

    result += std::to_string(abilities_.size()) + "\n";

    for (int i = 0; i < abilities_.size(); i++) {
        if (abilities_[i] == AbilityType::DoubleDamage) {
            result += "0 ";
        } else if (abilities_[i] == AbilityType::Scanner) {
            result += "1 ";
        } else if(abilities_[i] == AbilityType::Bombardment) {
            result += "2 ";
        }
    }

    result += "\n";
    return result;
}

void AbilityManager::setAbilities(std::vector<int>& info)
{
    abilities_.clear();

    for (int i = 0; i < info.size(); i++) {
        if (info[i] == 0) {
            abilities_.push_back(AbilityType::DoubleDamage);
        } else if (info[i] == 1) {
            abilities_.push_back(AbilityType::Scanner);
        } else if(info[i] == 2) {
            abilities_.push_back(AbilityType::Bombardment);
        }
    }
}
#ifndef ABILITY_SETTINGS
#define ABILITY_SETTINGS

#include "iVisitor.h"

enum class AbilityType : int
{
    DoubleDamage,
    Scanner,
    Bombardment
};

class IAbilitySettings
{
public:
    virtual AbilityType getType() = 0;
    virtual void acceptVisitor(IVisitor& visitor) = 0;
};

#endif
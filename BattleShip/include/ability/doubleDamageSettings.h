#ifndef DOUBLE_DAMAGE_SETTINGS
#define DOUBLE_DAMAGE_SETTINGS

#include "iAbilitySettings.h"
#include "iVisitor.h"

class DoubleDamageSettings: public IAbilitySettings
{
public:
    int& damage_;

    DoubleDamageSettings(int& damage);

    ~DoubleDamageSettings();

    AbilityType getType() override;

    void acceptVisitor(IVisitor& visitor) override;
};

#endif
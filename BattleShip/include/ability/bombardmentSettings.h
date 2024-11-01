#ifndef BOMBARDMENT_SETTINGS
#define BOMBARDMENT_SETTINGS

#include "iAbilitySettings.h"
#include "iVisitor.h"
#include "field.h"

class BombardmentSettings: public IAbilitySettings
{
public:
    Field& field_;
    int damage_;

    BombardmentSettings(Field& field, int damage);

    ~BombardmentSettings();

    AbilityType getType() override;

    void acceptVisitor(IVisitor& visitor) override;
};

#endif
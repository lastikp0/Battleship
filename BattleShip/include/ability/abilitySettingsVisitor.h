#ifndef ABILITY_SETTINGS_VISITOR
#define ABILITY_SETTINGS_VISITOR

#include "iVisitor.h"

#include "abilityFactory.h"

class AbilitySettingsVisitor : public IVisitor
{
public:
    AbilitySettingsVisitor(AbilityFactory& factory_);
    ~AbilitySettingsVisitor();

    void visit(class DoubleDamageSettings* settings);
    void visit(class ScannerSettings* settings);
    void visit(class BombardmentSettings* settings);

private:
    AbilityFactory& factory_;
};

#endif
#ifndef SCANER_SETTINGS
#define SCANER_SETTINGS

#include "iAbilitySettings.h"
#include "iVisitor.h"
#include "field.h"

class ScannerSettings: public IAbilitySettings
{
public:
    Field& field_;
    Coords coords_;
    bool& scan_result_;

    ScannerSettings(Field& field, Coords coords, bool& scan_result);
    ~ScannerSettings();

    AbilityType getType() override;

    void acceptVisitor(IVisitor& visitor) override;
};

#endif
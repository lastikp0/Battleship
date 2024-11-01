#include "scannerSettings.h"

#include "iAbilitySettings.h"
#include "iVisitor.h"
#include "field.h"

ScannerSettings::ScannerSettings(Field& field, Coords coords, bool& scan_result) :
    field_(field),
    coords_(coords),
    scan_result_(scan_result)
{}

ScannerSettings::~ScannerSettings() = default;

AbilityType ScannerSettings::getType()
{
    return AbilityType::Scanner;
}

void ScannerSettings::acceptVisitor(IVisitor& visitor)
{
    visitor.visit(this);
}
#ifndef SCANER
#define SCANER

#include "iAbility.h"
#include "field.h"

class Scanner: public IAbility
{
public:
    Scanner(Field& field, Coords coords, bool& scan_result);

    ~Scanner();

    void cast() override;

private:
    int kScanRadius = 2;

    Field& field_;
    Coords coords_;
    bool& scan_result_;
};

#endif
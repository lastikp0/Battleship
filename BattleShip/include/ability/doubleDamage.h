#ifndef DOUBLE_DAMAGE
#define DOUBLE_DAMAGE

#include "iAbility.h"

class DoubleDamage: public IAbility
{
public:
    
    DoubleDamage(int& damage);

    ~DoubleDamage();

    void cast() override;

private:
    int& damage_;
};

#endif
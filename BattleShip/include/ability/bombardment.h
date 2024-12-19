#ifndef BOMBARDMENT
#define BOMBARDMENT

#include "iAbility.h"
#include "field.h"

class Bombardment: public IAbility
{
public:
    Bombardment(Field& field, int damage);
    ~Bombardment();

    void cast() override;

private:
    Field& field_;
    int damage_;
};

#endif
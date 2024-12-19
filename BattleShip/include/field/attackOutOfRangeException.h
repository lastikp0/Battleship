#ifndef ATTACK_OUT_OF_RANGE_EXCEPTION
#define ATTACK_OUT_OF_RANGE_EXCEPTION

#include <string>

class AttackOutOfRangeException
{
public:
    AttackOutOfRangeException(std::string message);
    ~AttackOutOfRangeException();

    std::string what() const noexcept;

private:
    std::string message_;
}; 

#endif
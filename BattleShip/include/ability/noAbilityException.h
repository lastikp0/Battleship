#ifndef NO_ABILITY_EXCEPTION
#define NO_ABILITY_EXCEPTION

#include <string>

class NoAbilityException
{
public:
    NoAbilityException(std::string message);
    ~NoAbilityException();

    std::string what() const noexcept;

private:
    std::string message_;
}; 

#endif
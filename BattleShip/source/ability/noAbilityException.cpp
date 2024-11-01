#include "noAbilityException.h"

#include <string>

NoAbilityException::NoAbilityException(std::string message = "") :
    message_(message)
{}
 
NoAbilityException::~NoAbilityException() = default;

std::string NoAbilityException::what() const noexcept
{
    return message_;
}
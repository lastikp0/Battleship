#include "attackOutOfRangeException.h"

#include <string>

AttackOutOfRangeException::AttackOutOfRangeException(std::string message = "") :
    message_(message)
{}
 
AttackOutOfRangeException::~AttackOutOfRangeException() = default;

std::string AttackOutOfRangeException::what() const noexcept
{
    return message_;
}
#include "shipPlacementException.h"

#include <string>

ShipPlacementException::ShipPlacementException(std::string message = "") :
    message_(message)
{}
 
ShipPlacementException::~ShipPlacementException() = default;

std::string ShipPlacementException::what() const noexcept
{
    return message_;
}
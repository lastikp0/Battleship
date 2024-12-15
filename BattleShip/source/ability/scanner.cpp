#include "scanner.h"

#include "iAbility.h"
#include "field.h"

Scanner::Scanner(Field& field, Coords coords, bool& scan_result) :
    field_(field),
    coords_(coords),
    scan_result_(scan_result)
{}

Scanner::~Scanner() = default;

void Scanner::cast()
{
    int size_x = field_.getSize().x;
    int size_y = field_.getSize().y;
    
    for (int i = coords_.x; i < coords_.x + kScanRadius; i++) {
        for (int j = coords_.y; j < coords_.y + kScanRadius; j++) {
            if (i >= 0 && i < size_x && j >= 0 && j < size_y) {
                if (field_.isShip({i, j})) {
                    scan_result_ = true;
                    return;
                }
            }
        }
    }

    scan_result_ = false;
    return;
}
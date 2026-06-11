#include "Cell.h"

Cell::Cell() : value(0), fixed(false) {}

Cell::Cell(int value, bool fixed) : value(value), fixed(fixed) {}

int Cell::getValue() const
{
    return value;
}

void Cell::setValue(int value)
{
    this->value = value;
}

bool Cell::isFixed() const
{
    return fixed;
}

void Cell::setFixed(bool fixed)
{
    this->fixed = fixed;
}

bool Cell::isEmpty() const
{
    return value == 0;
}

void Cell::clear()
{
    if (!fixed)
    {
        value = 0;
    }
}

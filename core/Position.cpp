#include "Position.h"

#include <ostream>

Position::Position(int row, int col)
    : row(row),
      col(col)
{
}

int Position::getRow() const
{
    return row;
}

int Position::getCol() const
{
    return col;
}

void Position::set(int newRow, int newCol)
{
    row = newRow;
    col = newCol;
}

bool Position::operator==(const Position& other) const
{
    return row == other.row && col == other.col;
}

bool Position::operator!=(const Position& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const Position& position)
{
    stream << "(" << position.row + 1 << ", " << position.col + 1 << ")";
    return stream;
}

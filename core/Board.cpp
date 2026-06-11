#include "Board.h"

Board::Board()
{
}

Cell& Board::at(int row, int col)
{
    return cells[row][col];
}

const Cell& Board::at(int row, int col) const
{
    return cells[row][col];
}

Cell& Board::operator()(int row, int col)
{
    return at(row, col);
}

const Cell& Board::operator()(int row, int col) const
{
    return at(row, col);
}

int Board::getValue(int row, int col) const
{
    return at(row, col).getValue();
}

void Board::setValue(int row, int col, int value)
{
    at(row, col).setValue(value);
}

bool Board::isEmpty(int row, int col) const
{
    return at(row, col).isEmpty();
}

bool Board::isFixed(int row, int col) const
{
    return at(row, col).isFixed();
}

bool Board::isFull() const
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (isEmpty(row, col))
            {
                return false;
            }
        }
    }

    return true;
}

void Board::clear()
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            at(row, col).clear();
        }
    }
}

#include "Solver.h"
#include "Sudokurules.h"

bool Solver::findEmptyCell(const Board& board, int& row, int& col) const
{
    for (row = 0; row < Board::SIZE; row++)
    {
        for (col = 0; col < Board::SIZE; col++)
        {
            if (board.isEmpty(row, col))
            {
                return true;
            }
        }
    }

    return false;
}

bool Solver::solve(Board& board)
{
    int row = 0;
    int col = 0;

    if (!findEmptyCell(board, row, col))
    {
        return true;
    }

    for (int value = 1; value <= Board::SIZE; value++)
    {
        if (SudokuRules::isMoveValid(board, row, col, value))
        {
            board.setValue(row, col, value);

            if (solve(board))
            {
                return true;
            }

            board.setValue(row, col, 0);
        }
    }

    return false;
}
#include "Sudokurules.h"

bool SudokuRules::isValueInRow(const Board& board, int row, int value)
{
    for (int col = 0; col < Board::SIZE; col++)
    {
        if (board.getValue(row, col) == value)
        {
            return true;
        }
    }

    return false;
}

bool SudokuRules::isValueInColumn(const Board& board, int col, int value)
{
    for (int row = 0; row < Board::SIZE; row++)
    {
        if (board.getValue(row, col) == value)
        {
            return true;
        }
    }

    return false;
}

bool SudokuRules::isValueInBox(const Board& board, int row, int col, int value)
{
    int startRow = row - row % Board::BOX_SIZE;
    int startCol = col - col % Board::BOX_SIZE;

    for (int row = startRow; row < startRow + Board::BOX_SIZE; row++)
    {
        for (int col = startCol; col < startCol + Board::BOX_SIZE; col++)
        {
            if (board.getValue(row, col) == value)
            {
                return true;
            }
        }
    }

    return false;
}

bool SudokuRules::isMoveValid(const Board& board, int row, int col, int value)
{
    if (value < 1 || value > Board::SIZE)
    {
        return false;
    }

    if (board.isFixed(row, col))
    {
        return false;
    }

    if (isValueInRow(board, row, value))
    {
        return false;
    }

    if (isValueInColumn(board, col, value))
    {
        return false;
    }

    if (isValueInBox(board, row, col, value))
    {
        return false;
    }

    return true;
}

bool SudokuRules::isBoardValid(const Board& board)
{
    for (int row = 0; row < Board::SIZE; row++)
    {
        for (int col = 0; col < Board::SIZE; col++)
        {
            int value = board.getValue(row, col);

            if (value == 0)
            {
                return false;
            }

            for (int checkCol = 0; checkCol < Board::SIZE; checkCol++)
            {
                if (checkCol != col && board.getValue(row, checkCol) == value)
                {
                    return false;
                }
            }

            for (int checkRow = 0; checkRow < Board::SIZE; checkRow++)
            {
                if (checkRow != row && board.getValue(checkRow, col) == value)
                {
                    return false;
                }
            }

            int startRow = row - row % Board::BOX_SIZE;
            int startCol = col - col % Board::BOX_SIZE;

            for (int checkRow = startRow; checkRow < startRow + Board::BOX_SIZE; checkRow++)
            {
                for (int checkCol = startCol; checkCol < startCol + Board::BOX_SIZE; checkCol++)
                {
                    bool isSameCell = checkRow == row && checkCol == col;

                    if (!isSameCell && board.getValue(checkRow, checkCol) == value)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

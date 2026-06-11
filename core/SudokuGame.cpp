#include "SudokuGame.h"
#include "Generator.h"
#include "Sudokurules.h"

SudokuGame::SudokuGame()
{
}

void SudokuGame::newGame(int emptyCells)
{
    Generator generator;
    board = generator.generatePuzzle(emptyCells);
}

bool SudokuGame::makeMove(int row, int col, int value)
{
    if (board.isFixed(row, col))
    {
        return false;
    }

    int oldValue = board.getValue(row, col);
    board.setValue(row, col, 0);

    if (!SudokuRules::isMoveValid(board, row, col, value))
    {
        board.setValue(row, col, oldValue);
        return false;
    }

    board.setValue(row, col, value);

    return true;
}

bool SudokuGame::clearCell(int row, int col)
{
    if (board.isFixed(row, col))
    {
        return false;
    }

    board.setValue(row, col, 0);

    return true;
}

bool SudokuGame::isCompleted() const
{
    return SudokuRules::isBoardValid(board);
}

const Board& SudokuGame::getBoard() const
{
    return board;
}

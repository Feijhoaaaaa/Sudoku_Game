#include "LargeSudokuMode.h"

LargeSudokuMode::LargeSudokuMode()
    : SudokuModeBase(4)
{
}

std::string LargeSudokuMode::getName() const
{
    return "Sudoku 4x4 (16x16)";
}

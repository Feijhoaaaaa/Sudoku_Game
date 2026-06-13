#include "StandardSudokuMode.h"

StandardSudokuMode::StandardSudokuMode()
    : SudokuModeBase(3)
{
}

std::string StandardSudokuMode::getName() const
{
    return "Sudoku 3x3 (9x9)";
}

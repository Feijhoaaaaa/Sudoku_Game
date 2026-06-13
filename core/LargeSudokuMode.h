#ifndef LARGESUDOKUMODE_H
#define LARGESUDOKUMODE_H

#include "SudokuModeBase.h"

/**
 * @class LargeSudokuMode
 * @brief Rozszerzone Sudoku z blokami 4x4 i planszą 16x16.
 */
class LargeSudokuMode : public SudokuModeBase
{
public:
    /**
     * @brief Tworzy rozszerzony tryb Sudoku.
     */
    LargeSudokuMode();

    std::string getName() const override;
};

#endif // LARGESUDOKUMODE_H

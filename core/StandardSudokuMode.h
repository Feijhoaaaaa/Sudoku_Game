#ifndef STANDARDSUDOKUMODE_H
#define STANDARDSUDOKUMODE_H

#include "SudokuModeBase.h"

/**
 * @class StandardSudokuMode
 * @brief Klasyczne Sudoku z blokami 3x3 i planszą 9x9.
 */
class StandardSudokuMode : public SudokuModeBase
{
public:
    /**
     * @brief Tworzy klasyczny tryb Sudoku.
     */
    StandardSudokuMode();

    std::string getName() const override;
};

#endif // STANDARDSUDOKUMODE_H

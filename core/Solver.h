#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

/**
   * @class Solver
   * @brief Odpowiada za rozwiązywanie planszy Sudoku.
   *
   * Klasa wykorzystuje algorytm backtrackingu do znalezienia
   * poprawnego rozwiązania planszy.
   */
class Solver
{
public:

    /**
       * @brief Próbuje rozwiązać podaną planszę Sudoku.
       *
       * @param board Plansza Sudoku do rozwiązania.
       * @return true jeśli udało się znaleźć rozwiązanie.
       * @return false jeśli plansza nie ma rozwiązania.
       */
    bool solve(Board& board);

private:

    /**
       * @brief Znajduje pierwsze puste pole na planszy.
       *
       * @param board Plansza Sudoku.
       * @param row Referencja, do której zostanie zapisany numer wiersza.
       * @param col Referencja, do której zostanie zapisany numer kolumny.
       * @return true jeśli znaleziono puste pole.
       * @return false jeśli plansza jest pełna.
       */
    bool findEmptyCell(const Board& board, int& row, int& col) const;
};

#endif // SOLVER_H
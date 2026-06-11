#ifndef GENERATOR_H
#define GENERATOR_H

#include "Board.h"

/**
   * @class Generator
   * @brief Odpowiada za generowanie plansz Sudoku.
   *
   * Klasa tworzy pełne poprawne plansze Sudoku,
   * a następnie usuwa część pól, aby powstała zagadka.
   */
class Generator
{
public:

    /**
       * @brief Generuje planszę startową Sudoku.
       *
       * @param emptyCells Liczba pól, które mają zostać usunięte.
       * @return Wygenerowana plansza Sudoku.
       */
    Board generatePuzzle(int emptyCells);

private:

    /**
       * @brief Generuje pełną rozwiązaną planszę Sudoku.
       *
       * @return Pełna poprawna plansza Sudoku.
       */
    Board generateSolvedBoard();

    /**
       * @brief Wypełnia planszę poprawnymi wartościami Sudoku.
       *
       * Metoda używa algorytmu backtrackingu. Dla każdego pustego pola
       * próbuje wartości w losowej kolejności, dzięki czemu wygenerowane
       * pełne plansze różnią się między uruchomieniami programu.
       *
       * @param board Plansza Sudoku do wypełnienia.
       * @return true jeśli udało się wypełnić planszę.
       * @return false jeśli nie znaleziono poprawnego wypełnienia.
       */
    bool fillBoard(Board& board);

    /**
       * @brief Usuwa wybraną liczbę pól z planszy.
       *
       * @param board Plansza, z której usuwane są pola.
       * @param emptyCells Liczba pól do usunięcia.
       */
    void removeCells(Board& board, int emptyCells);

    /**
       * @brief Oznacza wszystkie niepuste pola jako stałe.
       *
       * @param board Plansza Sudoku.
       */
    void markFixedCells(Board& board);
};

#endif // GENERATOR_H

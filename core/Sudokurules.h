#ifndef SUDOKURULES_H
#define SUDOKURULES_H

#include "Board.h"

/**
   * @class SudokuRules
   * @brief Odpowiada za sprawdzanie zasad gry Sudoku.
   *
   * Klasa udostępnia metody pomocnicze do sprawdzania,
   * czy wartości na planszy spełniają reguły Sudoku.
   */
class SudokuRules
{
public:

    /**
       * @brief Sprawdza, czy wartość znajduje się w podanym wierszu.
       *
       * @param board Plansza Sudoku.
       * @param row Numer wiersza.
       * @param value Sprawdzana wartość.
       * @return true jeśli wartość występuje w wierszu.
       * @return false jeśli wartość nie występuje w wierszu.
       */
    static bool isValueInRow(const Board& board, int row, int value);

    /**
       * @brief Sprawdza, czy wartość znajduje się w podanej kolumnie.
       *
       * @param board Plansza Sudoku.
       * @param col Numer kolumny.
       * @param value Sprawdzana wartość.
       * @return true jeśli wartość występuje w kolumnie.
       * @return false jeśli wartość nie występuje w kolumnie.
       */
    static bool isValueInColumn(const Board& board, int col, int value);

    /**
       * @brief Sprawdza, czy wartość znajduje się w bloku 3x3.
       *
       * @param board Plansza Sudoku.
       * @param row Numer wiersza pola należącego do bloku.
       * @param col Numer kolumny pola należącego do bloku.
       * @param value Sprawdzana wartość.
       * @return true jeśli wartość występuje w bloku.
       * @return false jeśli wartość nie występuje w bloku.
       */
    static bool isValueInBox(const Board& board, int row, int col, int value);

    /**
       * @brief Sprawdza, czy ruch jest zgodny z zasadami Sudoku.
       *
       * @param board Plansza Sudoku.
       * @param row Numer wiersza.
       * @param col Numer kolumny.
       * @param value Wartość do wpisania.
       * @return true jeśli ruch jest poprawny.
       * @return false jeśli ruch łamie zasady Sudoku.
       */
    static bool isMoveValid(const Board& board, int row, int col, int value);

    /**
       * @brief Sprawdza, czy cała plansza jest poprawnie wypełniona.
       *
       * Metoda weryfikuje, czy plansza nie zawiera pustych pól
       * oraz czy żadna wartość nie powtarza się w tym samym wierszu,
       * kolumnie ani bloku 3x3.
       *
       * @param board Plansza Sudoku do sprawdzenia.
       * @return true jeśli plansza jest pełna i zgodna z zasadami Sudoku.
       * @return false jeśli plansza zawiera puste pola lub łamie zasady Sudoku.
       */
    static bool isBoardValid(const Board& board);
};

#endif // SUDOKURULES_H

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "Board.h"

/**
   * @class SudokuGame
   * @brief Zarządza aktualną rozgrywką Sudoku.
   *
   * Klasa przechowuje aktualną planszę gry oraz udostępnia
   * metody do rozpoczęcia nowej gry, wykonywania ruchów
   * i sprawdzania stanu rozgrywki.
   */
class SudokuGame
{
private:

    /**
       * @brief Aktualna plansza gry.
       */
    Board board;

public:

    /**
       * @brief Tworzy pustą grę Sudoku.
       */
    SudokuGame();

    /**
       * @brief Rozpoczyna nową grę.
       *
       * @param emptyCells Liczba pól, które mają być puste.
       */
    void newGame(int emptyCells);

    /**
       * @brief Próbuje wpisać wartość w wybrane pole planszy.
       *
       * Metoda nie pozwala modyfikować pól stałych. Jeśli pole zawierało
       * wcześniej wartość wpisaną przez gracza, zostaje ona tymczasowo
       * usunięta na czas sprawdzania poprawności nowego ruchu. Gdy nowy
       * ruch jest niepoprawny, poprzednia wartość zostaje przywrócona.
       *
       * @param row Numer wiersza.
       * @param col Numer kolumny.
       * @param value Wartość do wpisania.
       * @return true jeśli wartość została wpisana.
       * @return false jeśli pole jest stałe lub ruch łamie zasady Sudoku.
       */
    bool makeMove(int row, int col, int value);

    /**
       * @brief Czyści wybrane pole planszy.
       *
       * @param row Numer wiersza.
       * @param col Numer kolumny.
       * @return true jeśli pole zostało wyczyszczone.
       * @return false jeśli pole nie może być wyczyszczone.
       */
    bool clearCell(int row, int col);

    /**
       * @brief Sprawdza, czy gra została ukończona.
       *
       * Gra jest ukończona, gdy plansza jest pełna i wszystkie wpisane
       * wartości spełniają zasady Sudoku.
       *
       * @return true jeśli plansza jest pełna i poprawna.
       * @return false jeśli plansza zawiera puste pola lub błędy.
       */
    bool isCompleted() const;

    /**
       * @brief Zwraca aktualną planszę do odczytu.
       *
       * @return Stała referencja do planszy.
       */
    const Board& getBoard() const;
};

#endif // SUDOKUGAME_H

#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

/**
 * @class Board
 * @brief Reprezentuje planszę Sudoku 9x9.
 *
 * Klasa przechowuje wszystkie pola planszy oraz
 * udostępnia metody do odczytu i modyfikacji ich zawartości.
 */
class Board
{
private:

    /**
     * @brief Dwuwymiarowa tablica pól planszy Sudoku.
     */
    Cell cells[9][9];

public:

    /**
     * @brief Rozmiar planszy Sudoku.
     */
    static const int SIZE = 9;

    /**
     * @brief Rozmiar pojedynczego bloku 3x3.
     */
    static const int BOX_SIZE = 3;

    /**
     * @brief Tworzy pustą planszę Sudoku.
     */
    Board();

    /**
     * @brief Zwraca referencję do pola na podanej pozycji.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Referencja do obiektu Cell.
     */
    Cell& at(int row, int col);

    /**
     * @brief Zwraca stałą referencję do pola na podanej pozycji.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Stała referencja do obiektu Cell.
     */
    const Cell& at(int row, int col) const;

    /**
     * @brief Przeciążenie operatora dostępu do pola planszy.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Referencja do obiektu Cell.
     */
    Cell& operator()(int row, int col);

    /**
     * @brief Stała wersja operatora dostępu do pola planszy.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Stała referencja do obiektu Cell.
     */
    const Cell& operator()(int row, int col) const;

    /**
     * @brief Pobiera wartość z wybranego pola.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Wartość przechowywana w polu.
     */
    int getValue(int row, int col) const;

    /**
     * @brief Ustawia wartość wybranego pola.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @param value Nowa wartość pola.
     */
    void setValue(int row, int col, int value);

    /**
     * @brief Sprawdza, czy wybrane pole jest puste.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return true jeśli pole jest puste.
     * @return false jeśli pole zawiera wartość.
     */
    bool isEmpty(int row, int col) const;

    /**
     * @brief Sprawdza, czy wybrane pole jest stałe.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return true jeśli pole jest stałe.
     * @return false jeśli pole może być edytowane.
     */
    bool isFixed(int row, int col) const;

    /**
     * @brief Sprawdza, czy plansza jest całkowicie wypełniona.
     *
     * @return true jeśli wszystkie pola zawierają wartości.
     * @return false jeśli istnieje przynajmniej jedno puste pole.
     */
    bool isFull() const;

    /**
     * @brief Czyści całą planszę.
     *
     * Wszystkie pola zostają przywrócone do stanu początkowego.
     */
    void clear();
};

#endif // BOARD_H
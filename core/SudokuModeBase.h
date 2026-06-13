#ifndef SUDOKUMODEBASE_H
#define SUDOKUMODEBASE_H

#include "GameMode.h"

#include <vector>

/**
 * @class SudokuModeBase
 * @brief Wspólna baza dla konkretnych wariantów Sudoku.
 *
 * Klasa implementuje większość logiki gry niezależnej od rozmiaru planszy.
 * Klasy pochodne podają tylko rozmiar bloku, np. 3 dla planszy 9x9
 * albo 4 dla planszy 16x16.
 */
class SudokuModeBase : public GameMode
{
protected:
    int boxSize;
    int size;
    Difficulty difficulty;
    std::vector<int> values;
    std::vector<int> fixedFields;

    /**
     * @brief Zwraca indeks pola w jednowymiarowej tablicy.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Indeks pola.
     */
    int index(int row, int col) const;

    /**
     * @brief Sprawdza, czy współrzędne mieszczą się na planszy.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return true jeśli współrzędne są poprawne.
     */
    bool isInside(int row, int col) const;

    /**
     * @brief Ustala liczbę pól do usunięcia dla poziomu trudności.
     *
     * @param difficulty Wybrany poziom trudności.
     * @return Liczba pól pustych na starcie.
     */
    int emptyCellsForDifficulty(Difficulty difficulty) const;

    /**
     * @brief Generuje pełną, poprawną planszę.
     *
     * @return Wektor wartości rozwiązanej planszy.
     */
    std::vector<int> generateSolvedValues() const;

    /**
     * @brief Sprawdza, czy wartość nie koliduje z zasadami Sudoku.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @param value Sprawdzana wartość.
     * @return true jeśli wartość można wpisać.
     */
    bool canPlaceValue(int row, int col, int value) const;

public:
    /**
     * @brief Tworzy bazę trybu Sudoku.
     *
     * @param boxSize Rozmiar boku jednego bloku.
     */
    explicit SudokuModeBase(int boxSize);

    void startNew(Difficulty difficulty) override;
    Difficulty getDifficulty() const override;
    int getSize() const override;
    int getBoxSize() const override;
    int getMaxValue() const override;
    int getValue(int row, int col) const override;
    bool isFixed(int row, int col) const override;
    bool makeMove(int row, int col, int value) override;
    bool clearCell(int row, int col) override;
    bool isCompleted() const override;
    bool loadState(const int* values, const int* fixed, Difficulty difficulty) override;
};

#endif // SUDOKUMODEBASE_H

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "SudokuGame.h"

#include <string>

/**
 * @class ConsoleUI
 * @brief Obsługuje interaktywny terminalowy interfejs gry Sudoku.
 *
 * Klasa odpowiada za wyświetlanie planszy, sterowanie kursorem
 * za pomocą strzałek oraz przekazywanie ruchów gracza do klasy SudokuGame.
 */
class ConsoleUI
{
private:

    /**
     * @brief Aktualnie zaznaczony wiersz planszy.
     */
    int selectedRow;

    /**
     * @brief Aktualnie zaznaczona kolumna planszy.
     */
    int selectedCol;

    /**
     * @brief Komunikat wyświetlany pod planszą.
     */
    std::string statusMessage;

    /**
     * @brief Aktualna rozgrywka Sudoku.
     */
    SudokuGame game;

    /**
     * @brief Rysuje aktualny stan interfejsu w terminalu.
     */
    void render() const;

    /**
     * @brief Przesuwa zaznaczenie o podany wektor.
     *
     * @param rowDelta Zmiana wiersza.
     * @param colDelta Zmiana kolumny.
     */
    void moveSelection(int rowDelta, int colDelta);

    /**
     * @brief Próbuje wpisać wartość w aktualnie zaznaczone pole.
     *
     * @param value Wartość do wpisania.
     */
    void enterValue(int value);

    /**
     * @brief Próbuje wyczyścić aktualnie zaznaczone pole.
     */
    void clearSelectedCell();

public:

    /**
     * @brief Tworzy interfejs z kursorem ustawionym w lewym górnym rogu.
     */
    ConsoleUI();

    /**
     * @brief Uruchamia główną pętlę interaktywnej gry.
     */
    void run();
};

#endif // CONSOLEUI_H

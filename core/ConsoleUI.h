#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "GameMode.h"
#include "Position.h"

#include <memory>
#include <string>

/**
 * @class ConsoleUI
 * @brief Obsługuje menu i interaktywny terminalowy interfejs gry Sudoku.
 *
 * Klasa pokazuje praktyczne użycie polimorfizmu: przechowuje aktywną grę
 * jako wskaźnik do GameMode, a rzeczywisty tryb może być planszą 9x9
 * albo 16x16.
 */
class ConsoleUI
{
private:

    /**
     * @brief Aktualnie zaznaczony wiersz planszy.
     */
    Position selectedPosition;

    /**
     * @brief Komunikat wyświetlany pod planszą.
     */
    std::string statusMessage;

    /**
     * @brief Aktualnie wybrany poziom trudności.
     */
    Difficulty selectedDifficulty;

    /**
     * @brief Wybrany rozmiar bloku: 3 oznacza 9x9, 4 oznacza 16x16.
     */
    int selectedBoxSize;

    /**
     * @brief Aktualny tryb gry obsługiwany polimorficznie.
     */
    std::unique_ptr<GameMode> game;

    /**
     * @brief Pierwsza cyfra wartości dwucyfrowej w trybie 16x16.
     */
    int pendingLeadingDigit;

    /**
     * @brief Tworzy tryb gry zgodny z wyborem w menu.
     *
     * @return Wskaźnik do nowego trybu gry.
     */
    std::unique_ptr<GameMode> createSelectedMode() const;

    /**
     * @brief Rysuje menu główne.
     *
     * @param selectedOption Aktualnie zaznaczona opcja menu.
     */
    void renderMenu(int selectedOption) const;

    /**
     * @brief Obsługuje menu główne.
     */
    void runMenu();

    /**
     * @brief Rysuje aktualny stan interfejsu gry w terminalu.
     */
    void renderGame() const;

    /**
     * @brief Uruchamia pętlę aktywnej gry.
     */
    void runGame();

    /**
     * @brief Przesuwa zaznaczenie o podany wektor.
     *
     * @param rowDelta Zmiana wiersza.
     * @param colDelta Zmiana kolumny.
     */
    void moveSelection(int rowDelta, int colDelta);

    /**
     * @brief Obsługuje wpisywanie cyfry.
     *
     * W trybie 16x16 cyfra 1 może rozpocząć wartość dwucyfrową.
     *
     * @param value Wciśnięta cyfra.
     */
    void handleDigit(int value);

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

    /**
     * @brief Zapisuje aktywną rozgrywkę.
     */
    void saveCurrentGame();

    /**
     * @brief Rozpoczyna nową rozgrywkę zgodnie z ustawieniami menu.
     */
    void startNewGame();

    /**
     * @brief Próbuje wczytać ostatni zapis gry.
     *
     * @return true jeśli zapis został wczytany.
     */
    bool loadSavedGame();

public:

    /**
     * @brief Tworzy interfejs z kursorem ustawionym w lewym górnym rogu.
     */
    ConsoleUI();

    /**
     * @brief Uruchamia program od menu głównego.
     */
    void run();
};

#endif // CONSOLEUI_H

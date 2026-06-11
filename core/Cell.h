#ifndef CELL_H
#define CELL_H

/**
 * @class Cell
 * @brief Reprezentuje pojedyncze pole planszy Sudoku.
 *
 * Klasa przechowuje wartość pola oraz informację,
 * czy pole jest stałym elementem wygenerowanej planszy.
 * Pole stałe nie może być modyfikowane przez gracza.
 */
class Cell
{
private:

    /**
    * @brief Wartość przechowywana w polu Sudoku.
    *
    * Wartość 0 oznacza pole puste.
    * Dopuszczalne wartości to liczby od 1 do 9.
    */
    int value;

    /**
     * @brief Określa, czy pole jest stałym elementem planszy.
     *
     * Pole stałe jest generowane na początku gry
     * i nie może być modyfikowane przez gracza.
     */
    bool fixed;

public:

    /**
     * @brief Tworzy puste, edytowalne pole.
     */
    Cell();

    /**
     * @brief Tworzy pole z określoną wartością.
     *
     * @param value Wartość początkowa pola.
     * @param fixed Określa, czy pole jest stałe.
     */
    Cell(int value, bool fixed);

    /**
     * @brief Zwraca wartość pola.
     *
     * @return Aktualna wartość pola.
     */
    int getValue() const;

    /**
     * @brief Ustawia nową wartość pola.
     *
     * @param value Wartość do zapisania w polu.
     */
    void setValue(int value);

    /**
     * @brief Sprawdza, czy pole jest stałe.
     *
     * @return true jeśli pole jest stałe.
     * @return false jeśli pole jest edytowalne.
     */
    bool isFixed() const;

    /**
     * @brief Ustawia stan pola.
     *
     * @param fixed Nowy stan pola.
     */
    void setFixed(bool fixed);

    /**
     * @brief Sprawdza, czy pole jest puste.
     *
     * Pole jest uznawane za puste, gdy jego wartość wynosi 0.
     *
     * @return true jeśli pole jest puste.
     * @return false jeśli pole zawiera liczbę.
     */
    bool isEmpty() const;

    /**
     * @brief Czyści zawartość pola.
     *
     * Jeśli pole nie jest stałe, jego wartość zostanie
     * ustawiona na 0.
     * Pole stałe pozostaje niezmienione.
     */
    void clear();
};

#endif // CELL_H
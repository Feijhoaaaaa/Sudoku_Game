#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>

/**
 * @enum Difficulty
 * @brief Określa poziom trudności rozgrywki.
 */
enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

/**
 * @brief Zamienia poziom trudności na tekst.
 *
 * @param difficulty Poziom trudności.
 * @return Nazwa poziomu trudności.
 */
std::string difficultyToString(Difficulty difficulty);

/**
 * @brief Zamienia tekst z pliku zapisu na poziom trudności.
 *
 * @param text Tekstowa nazwa poziomu.
 * @return Poziom trudności.
 */
Difficulty difficultyFromString(const std::string& text);

/**
 * @class GameMode
 * @brief Abstrakcyjna baza dla trybów gry.
 *
 * Klasa pokazuje polimorfizm: interfejs użytkownika pracuje na wskaźniku
 * do GameMode, a konkretne zachowanie zależy od rzeczywistej klasy pochodnej.
 */
class GameMode
{
public:
    /**
     * @brief Wirtualny destruktor umożliwia poprawne niszczenie klas pochodnych.
     */
    virtual ~GameMode() = default;

    /**
     * @brief Rozpoczyna nową rozgrywkę.
     *
     * @param difficulty Wybrany poziom trudności.
     */
    virtual void startNew(Difficulty difficulty) = 0;

    /**
     * @brief Zwraca nazwę trybu gry.
     *
     * @return Nazwa trybu.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Zwraca poziom trudności aktualnej rozgrywki.
     *
     * @return Poziom trudności.
     */
    virtual Difficulty getDifficulty() const = 0;

    /**
     * @brief Zwraca rozmiar planszy.
     *
     * @return Liczba wierszy i kolumn planszy.
     */
    virtual int getSize() const = 0;

    /**
     * @brief Zwraca rozmiar bloku.
     *
     * @return Rozmiar jednego boku bloku.
     */
    virtual int getBoxSize() const = 0;

    /**
     * @brief Zwraca największą dopuszczalną wartość.
     *
     * @return Maksymalna wartość pola.
     */
    virtual int getMaxValue() const = 0;

    /**
     * @brief Pobiera wartość pola.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return Wartość pola.
     */
    virtual int getValue(int row, int col) const = 0;

    /**
     * @brief Sprawdza, czy pole jest polem startowym.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return true jeśli pole jest stałe.
     */
    virtual bool isFixed(int row, int col) const = 0;

    /**
     * @brief Wpisuje wartość w pole.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @param value Wpisywana wartość.
     * @return true jeśli ruch został przyjęty.
     */
    virtual bool makeMove(int row, int col, int value) = 0;

    /**
     * @brief Czyści pole gracza.
     *
     * @param row Numer wiersza.
     * @param col Numer kolumny.
     * @return true jeśli pole zostało wyczyszczone.
     */
    virtual bool clearCell(int row, int col) = 0;

    /**
     * @brief Sprawdza, czy plansza jest poprawnie ukończona.
     *
     * @return true jeśli rozgrywka jest zakończona.
     */
    virtual bool isCompleted() const = 0;

    /**
     * @brief Wczytuje stan planszy z danych liczbowych.
     *
     * @param values Wartości pól.
     * @param fixed Informacja, które pola są stałe.
     * @param difficulty Poziom trudności zapisu.
     * @return true jeśli dane pasują do trybu gry.
     */
    virtual bool loadState(const int* values, const int* fixed, Difficulty difficulty) = 0;
};

#endif // GAMEMODE_H

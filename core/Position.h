#ifndef POSITION_H
#define POSITION_H

#include <iosfwd>

/**
 * @class Position
 * @brief Reprezentuje położenie pola na planszy.
 *
 * Klasa jest małym przykładem przeciążania operatorów. Operator porównania
 * zdefiniowany jest jako metoda składowa, a operator wypisywania jako funkcja
 * zaprzyjaźniona, ponieważ potrzebuje bezpośredniego dostępu do pól klasy.
 */
class Position
{
private:
    int row;
    int col;

public:
    /**
     * @brief Tworzy pozycję na planszy.
     *
     * @param row Numer wiersza liczony od zera.
     * @param col Numer kolumny liczony od zera.
     */
    Position(int row = 0, int col = 0);

    /**
     * @brief Zwraca numer wiersza.
     *
     * @return Numer wiersza liczony od zera.
     */
    int getRow() const;

    /**
     * @brief Zwraca numer kolumny.
     *
     * @return Numer kolumny liczony od zera.
     */
    int getCol() const;

    /**
     * @brief Ustawia nową pozycję.
     *
     * @param newRow Nowy numer wiersza.
     * @param newCol Nowy numer kolumny.
     */
    void set(int newRow, int newCol);

    /**
     * @brief Porównuje dwie pozycje.
     *
     * @param other Druga pozycja.
     * @return true jeśli obie pozycje wskazują to samo pole.
     */
    bool operator==(const Position& other) const;

    /**
     * @brief Sprawdza, czy pozycje są różne.
     *
     * @param other Druga pozycja.
     * @return true jeśli pozycje wskazują różne pola.
     */
    bool operator!=(const Position& other) const;

    /**
     * @brief Wypisuje pozycję w czytelnej formie.
     *
     * Funkcja jest zaprzyjaźniona z klasą Position, dlatego może odczytać
     * prywatne pola row i col bez używania getterów.
     *
     * @param stream Strumień wyjściowy.
     * @param position Pozycja do wypisania.
     * @return Referencja do strumienia wyjściowego.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Position& position);
};

#endif // POSITION_H

#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "GameMode.h"

#include <memory>
#include <string>

/**
 * @class SaveManager
 * @brief Zapisuje i odczytuje stan gry z pliku tekstowego.
 */
class SaveManager
{
public:
    /**
     * @brief Domyślna ścieżka pliku zapisu.
     */
    static const char* DEFAULT_SAVE_FILE;

    /**
     * @brief Zapisuje aktualny tryb gry do pliku.
     *
     * @param game Tryb gry do zapisania.
     * @param fileName Nazwa pliku zapisu.
     * @return true jeśli zapis się udał.
     */
    static bool save(const GameMode& game, const std::string& fileName = DEFAULT_SAVE_FILE);

    /**
     * @brief Wczytuje tryb gry z pliku.
     *
     * @param fileName Nazwa pliku zapisu.
     * @return Wskaźnik do odtworzonego trybu gry albo nullptr przy błędzie.
     */
    static std::unique_ptr<GameMode> load(const std::string& fileName = DEFAULT_SAVE_FILE);
};

#endif // SAVEMANAGER_H

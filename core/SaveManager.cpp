#include "SaveManager.h"

#include "LargeSudokuMode.h"
#include "StandardSudokuMode.h"

#include <fstream>
#include <memory>
#include <vector>

const char* SaveManager::DEFAULT_SAVE_FILE = "sudoku_save.txt";

bool SaveManager::save(const GameMode& game, const std::string& fileName)
{
    std::ofstream file(fileName);

    if (!file)
    {
        return false;
    }

    int size = game.getSize();

    file << "SUDOKU_SAVE 1\n";
    file << "box_size " << game.getBoxSize() << "\n";
    file << "difficulty " << difficultyToString(game.getDifficulty()) << "\n";
    file << "values\n";

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            file << game.getValue(row, col) << ' ';
        }

        file << '\n';
    }

    file << "fixed\n";

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            file << (game.isFixed(row, col) ? 1 : 0) << ' ';
        }

        file << '\n';
    }

    return true;
}

std::unique_ptr<GameMode> SaveManager::load(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file)
    {
        return nullptr;
    }

    std::string marker;
    int version = 0;
    file >> marker >> version;

    if (marker != "SUDOKU_SAVE" || version != 1)
    {
        return nullptr;
    }

    std::string label;
    int boxSize = 0;
    std::string difficultyText;

    file >> label >> boxSize;

    if (label != "box_size")
    {
        return nullptr;
    }

    file >> label >> difficultyText;

    if (label != "difficulty")
    {
        return nullptr;
    }

    std::unique_ptr<GameMode> game;

    if (boxSize == 3)
    {
        game = std::make_unique<StandardSudokuMode>();
    }
    else if (boxSize == 4)
    {
        game = std::make_unique<LargeSudokuMode>();
    }
    else
    {
        return nullptr;
    }

    int size = game->getSize();
    std::vector<int> values(size * size, 0);
    std::vector<int> fixed(size * size, 0);

    file >> label;

    if (label != "values")
    {
        return nullptr;
    }

    for (int i = 0; i < size * size; i++)
    {
        file >> values[i];
    }

    file >> label;

    if (label != "fixed")
    {
        return nullptr;
    }

    for (int i = 0; i < size * size; i++)
    {
        file >> fixed[i];
    }

    if (!file || !game->loadState(values.data(), fixed.data(), difficultyFromString(difficultyText)))
    {
        return nullptr;
    }

    return game;
}

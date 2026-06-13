#include "SudokuModeBase.h"

#include <algorithm>
#include <numeric>
#include <random>

namespace
{
std::mt19937& randomGenerator()
{
    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());

    return generator;
}

std::vector<int> shuffledRange(int first, int count)
{
    std::vector<int> values(count);
    std::iota(values.begin(), values.end(), first);
    std::shuffle(values.begin(), values.end(), randomGenerator());

    return values;
}
}

SudokuModeBase::SudokuModeBase(int boxSize)
    : boxSize(boxSize),
      size(boxSize * boxSize),
      difficulty(Difficulty::Medium),
      values(size * size, 0),
      fixedFields(size * size, 0)
{
}

int SudokuModeBase::index(int row, int col) const
{
    return row * size + col;
}

bool SudokuModeBase::isInside(int row, int col) const
{
    return row >= 0 && row < size && col >= 0 && col < size;
}

int SudokuModeBase::emptyCellsForDifficulty(Difficulty difficulty) const
{
    int totalCells = size * size;

    switch (difficulty)
    {
    case Difficulty::Easy:
        return totalCells * 35 / 100;
    case Difficulty::Medium:
        return totalCells * 50 / 100;
    case Difficulty::Hard:
        return totalCells * 62 / 100;
    }

    return totalCells / 2;
}

std::vector<int> SudokuModeBase::generateSolvedValues() const
{
    std::vector<int> result(size * size, 0);
    std::vector<int> rowBands = shuffledRange(0, boxSize);
    std::vector<int> colBands = shuffledRange(0, boxSize);
    std::vector<int> symbols = shuffledRange(1, size);

    std::vector<int> rows;
    std::vector<int> cols;

    for (int band : rowBands)
    {
        std::vector<int> offsets = shuffledRange(0, boxSize);

        for (int offset : offsets)
        {
            rows.push_back(band * boxSize + offset);
        }
    }

    for (int band : colBands)
    {
        std::vector<int> offsets = shuffledRange(0, boxSize);

        for (int offset : offsets)
        {
            cols.push_back(band * boxSize + offset);
        }
    }

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            int pattern = (boxSize * (rows[row] % boxSize) + rows[row] / boxSize + cols[col]) % size;
            result[index(row, col)] = symbols[pattern];
        }
    }

    return result;
}

bool SudokuModeBase::canPlaceValue(int row, int col, int value) const
{
    if (!isInside(row, col) || value < 1 || value > size)
    {
        return false;
    }

    for (int checkCol = 0; checkCol < size; checkCol++)
    {
        if (checkCol != col && getValue(row, checkCol) == value)
        {
            return false;
        }
    }

    for (int checkRow = 0; checkRow < size; checkRow++)
    {
        if (checkRow != row && getValue(checkRow, col) == value)
        {
            return false;
        }
    }

    int startRow = row - row % boxSize;
    int startCol = col - col % boxSize;

    for (int checkRow = startRow; checkRow < startRow + boxSize; checkRow++)
    {
        for (int checkCol = startCol; checkCol < startCol + boxSize; checkCol++)
        {
            bool sameCell = checkRow == row && checkCol == col;

            if (!sameCell && getValue(checkRow, checkCol) == value)
            {
                return false;
            }
        }
    }

    return true;
}

void SudokuModeBase::startNew(Difficulty newDifficulty)
{
    difficulty = newDifficulty;
    values = generateSolvedValues();
    fixedFields.assign(size * size, 1);

    std::vector<int> positions = shuffledRange(0, size * size);
    int cellsToRemove = emptyCellsForDifficulty(difficulty);

    for (int i = 0; i < cellsToRemove; i++)
    {
        values[positions[i]] = 0;
        fixedFields[positions[i]] = 0;
    }
}

Difficulty SudokuModeBase::getDifficulty() const
{
    return difficulty;
}

int SudokuModeBase::getSize() const
{
    return size;
}

int SudokuModeBase::getBoxSize() const
{
    return boxSize;
}

int SudokuModeBase::getMaxValue() const
{
    return size;
}

int SudokuModeBase::getValue(int row, int col) const
{
    if (!isInside(row, col))
    {
        return 0;
    }

    return values[index(row, col)];
}

bool SudokuModeBase::isFixed(int row, int col) const
{
    if (!isInside(row, col))
    {
        return false;
    }

    return fixedFields[index(row, col)] != 0;
}

bool SudokuModeBase::makeMove(int row, int col, int value)
{
    if (!isInside(row, col) || isFixed(row, col))
    {
        return false;
    }

    int oldValue = getValue(row, col);
    values[index(row, col)] = 0;

    if (!canPlaceValue(row, col, value))
    {
        values[index(row, col)] = oldValue;
        return false;
    }

    values[index(row, col)] = value;

    return true;
}

bool SudokuModeBase::clearCell(int row, int col)
{
    if (!isInside(row, col) || isFixed(row, col))
    {
        return false;
    }

    values[index(row, col)] = 0;

    return true;
}

bool SudokuModeBase::isCompleted() const
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            int value = getValue(row, col);

            if (value == 0 || !canPlaceValue(row, col, value))
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuModeBase::loadState(const int* newValues, const int* newFixed, Difficulty newDifficulty)
{
    if (newValues == nullptr || newFixed == nullptr)
    {
        return false;
    }

    difficulty = newDifficulty;

    for (int i = 0; i < size * size; i++)
    {
        if (newValues[i] < 0 || newValues[i] > size)
        {
            return false;
        }

        values[i] = newValues[i];
        fixedFields[i] = newFixed[i] == 0 ? 0 : 1;
    }

    return true;
}

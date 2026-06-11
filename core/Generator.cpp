#include "Generator.h"
#include "Sudokurules.h"

#include <algorithm>
#include <random>
#include <vector>

namespace
{
std::vector<int> shuffledValues()
{
    std::vector<int> values;

    for (int value = 1; value <= Board::SIZE; value++)
    {
        values.push_back(value);
    }

    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());

    std::shuffle(values.begin(), values.end(), generator);

    return values;
}
}

Board Generator::generatePuzzle(int emptyCells)
{
    Board board = generateSolvedBoard();

    removeCells(board, emptyCells);
    markFixedCells(board);

    return board;
}

Board Generator::generateSolvedBoard()
{
    Board board;

    fillBoard(board);

    return board;
}

bool Generator::fillBoard(Board& board)
{
    for (int row = 0; row < Board::SIZE; row++)
    {
        for (int col = 0; col < Board::SIZE; col++)
        {
            if (board.isEmpty(row, col))
            {
                std::vector<int> values = shuffledValues();

                for (int value : values)
                {
                    if (SudokuRules::isMoveValid(board, row, col, value))
                    {
                        board.setValue(row, col, value);

                        if (fillBoard(board))
                        {
                            return true;
                        }

                        board.setValue(row, col, 0);
                    }
                }

                return false;
            }
        }
    }

    return true;
}

void Generator::removeCells(Board& board, int emptyCells)
{
    if (emptyCells < 0)
    {
        emptyCells = 0;
    }

    if (emptyCells > Board::SIZE * Board::SIZE)
    {
        emptyCells = Board::SIZE * Board::SIZE;
    }

    std::vector<int> positions;

    for (int i = 0; i < Board::SIZE * Board::SIZE; i++)
    {
        positions.push_back(i);
    }

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::shuffle(positions.begin(), positions.end(), generator);

    for (int i = 0; i < emptyCells; i++)
    {
        int row = positions[i] / Board::SIZE;
        int col = positions[i] % Board::SIZE;

        board.setValue(row, col, 0);
    }
}

void Generator::markFixedCells(Board& board)
{
    for (int row = 0; row < Board::SIZE; row++)
    {
        for (int col = 0; col < Board::SIZE; col++)
        {
            if (board.isEmpty(row, col))
            {
                board.at(row, col).setFixed(false);
            }
            else
            {
                board.at(row, col).setFixed(true);
            }
        }
    }
}

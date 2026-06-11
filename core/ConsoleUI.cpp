#include "ConsoleUI.h"

#include "Board.h"

#include <cctype>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

namespace
{
const char* RESET_COLOR = "\033[0m";
const char* TITLE_COLOR = "\033[1;38;5;81m";
const char* STATUS_COLOR = "\033[38;5;250m";
const char* FIXED_CELL_COLOR = "\033[1;38;5;255m";
const char* PLAYER_CELL_COLOR = "\033[1;38;5;114m";
const char* EMPTY_CELL_COLOR = "\033[38;5;244m";
const char* SELECTED_CELL_COLOR = "\033[1;38;5;16;48;5;117m";
const char* HELP_TITLE_COLOR = "\033[1;38;5;117m";
const char* HELP_TEXT_COLOR = "\033[38;5;250m";

enum class Key
{
    Up,
    Down,
    Left,
    Right,
    Digit0,
    Digit1,
    Digit2,
    Digit3,
    Digit4,
    Digit5,
    Digit6,
    Digit7,
    Digit8,
    Digit9,
    Backspace,
    Delete,
    Quit,
    Unknown
};

class RawTerminalMode
{
private:
    termios originalSettings;
    bool enabled;

public:
    RawTerminalMode() : enabled(false)
    {
        if (tcgetattr(STDIN_FILENO, &originalSettings) == 0)
        {
            termios rawSettings = originalSettings;
            rawSettings.c_lflag &= static_cast<unsigned>(~(ICANON | ECHO));
            rawSettings.c_cc[VMIN] = 1;
            rawSettings.c_cc[VTIME] = 0;

            enabled = tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawSettings) == 0;
        }
    }

    ~RawTerminalMode()
    {
        if (enabled)
        {
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalSettings);
        }
    }
};

void clearScreen()
{
    std::cout << "\033[2J\033[H";
}

Key digitToKey(char character)
{
    switch (character)
    {
    case '0':
        return Key::Digit0;
    case '1':
        return Key::Digit1;
    case '2':
        return Key::Digit2;
    case '3':
        return Key::Digit3;
    case '4':
        return Key::Digit4;
    case '5':
        return Key::Digit5;
    case '6':
        return Key::Digit6;
    case '7':
        return Key::Digit7;
    case '8':
        return Key::Digit8;
    case '9':
        return Key::Digit9;
    default:
        return Key::Unknown;
    }
}

Key readKey()
{
    char character = '\0';

    if (read(STDIN_FILENO, &character, 1) != 1)
    {
        return Key::Unknown;
    }

    if (character == 'q' || character == 'Q')
    {
        return Key::Quit;
    }

    if (std::isdigit(static_cast<unsigned char>(character)))
    {
        return digitToKey(character);
    }

    if (character == 127 || character == 8)
    {
        return Key::Backspace;
    }

    if (character != '\033')
    {
        return Key::Unknown;
    }

    char sequence[3] = {};

    if (read(STDIN_FILENO, &sequence[0], 1) != 1)
    {
        return Key::Unknown;
    }

    if (read(STDIN_FILENO, &sequence[1], 1) != 1)
    {
        return Key::Unknown;
    }

    if (sequence[0] != '[')
    {
        return Key::Unknown;
    }

    switch (sequence[1])
    {
    case 'A':
        return Key::Up;
    case 'B':
        return Key::Down;
    case 'C':
        return Key::Right;
    case 'D':
        return Key::Left;
    case '3':
        if (read(STDIN_FILENO, &sequence[2], 1) == 1 && sequence[2] == '~')
        {
            return Key::Delete;
        }
        return Key::Unknown;
    default:
        return Key::Unknown;
    }
}

int keyToValue(Key key)
{
    switch (key)
    {
    case Key::Digit0:
        return 0;
    case Key::Digit1:
        return 1;
    case Key::Digit2:
        return 2;
    case Key::Digit3:
        return 3;
    case Key::Digit4:
        return 4;
    case Key::Digit5:
        return 5;
    case Key::Digit6:
        return 6;
    case Key::Digit7:
        return 7;
    case Key::Digit8:
        return 8;
    case Key::Digit9:
        return 9;
    default:
        return -1;
    }
}

std::string helpLine(int row)
{
    switch (row)
    {
    case 0:
        return "Sterowanie:";
    case 1:
        return "  Strzalki  - ruch kursorem";
    case 2:
        return "  1-9       - wpisz cyfre";
    case 3:
        return "  0         - wyczysc pole";
    case 4:
        return "  Backspace - wyczysc pole";
    case 5:
        return "  Delete    - wyczysc pole";
    case 6:
        return "  q         - wyjscie";
    case 7:
        return "Kolory:";
    case 8:
        return "  bialy     - pola startowe";
    case 9:
        return "  zielony   - pola gracza";
    case 10:
        return "  niebieski - aktywne pole";
    default:
        return "";
    }
}

void printHelpLine(int row)
{
    std::string line = helpLine(row);

    if (line.empty())
    {
        return;
    }

    if (line == "Sterowanie:" || line == "Kolory:")
    {
        std::cout << HELP_TITLE_COLOR << line << RESET_COLOR;
    }
    else
    {
        std::cout << HELP_TEXT_COLOR << line << RESET_COLOR;
    }
}
}

ConsoleUI::ConsoleUI()
    : selectedRow(0),
      selectedCol(0),
      statusMessage("Strzalki: ruch | 1-9: wpisz | 0/Backspace/Delete: wyczysc | q: wyjscie")
{
}

void ConsoleUI::render() const
{
    clearScreen();

    const Board& board = game.getBoard();

    std::cout << TITLE_COLOR << "Sudoku" << RESET_COLOR << std::endl;
    std::cout << STATUS_COLOR << statusMessage << RESET_COLOR << std::endl;
    std::cout << std::endl;

    int helpRow = 0;

    for (int row = 0; row < Board::SIZE; row++)
    {
        if (row % Board::BOX_SIZE == 0 && row != 0)
        {
            std::cout << STATUS_COLOR << "------+-------+------" << RESET_COLOR << "   ";
            printHelpLine(helpRow);
            std::cout << std::endl;
            helpRow++;
        }

        for (int col = 0; col < Board::SIZE; col++)
        {
            if (col % Board::BOX_SIZE == 0 && col != 0)
            {
                std::cout << STATUS_COLOR << "| " << RESET_COLOR;
            }

            bool selected = row == selectedRow && col == selectedCol;
            bool fixed = board.isFixed(row, col);
            int value = board.getValue(row, col);

            if (selected)
            {
                std::cout << SELECTED_CELL_COLOR;
            }
            else if (fixed)
            {
                std::cout << FIXED_CELL_COLOR;
            }
            else if (value == 0)
            {
                std::cout << EMPTY_CELL_COLOR;
            }
            else
            {
                std::cout << PLAYER_CELL_COLOR;
            }

            if (value == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << value << " ";
            }

            std::cout << RESET_COLOR;
        }

        std::cout << "   ";
        printHelpLine(helpRow);
        std::cout << std::endl;
        helpRow++;
    }

    std::cout << std::endl;
}

void ConsoleUI::moveSelection(int rowDelta, int colDelta)
{
    selectedRow = (selectedRow + rowDelta + Board::SIZE) % Board::SIZE;
    selectedCol = (selectedCol + colDelta + Board::SIZE) % Board::SIZE;
}

void ConsoleUI::enterValue(int value)
{
    if (game.makeMove(selectedRow, selectedCol, value))
    {
        statusMessage = "Wpisano wartosc.";
    }
    else
    {
        statusMessage = "Nie mozna wpisac tej wartosci w wybrane pole.";
    }
}

void ConsoleUI::clearSelectedCell()
{
    if (game.clearCell(selectedRow, selectedCol))
    {
        statusMessage = "Pole wyczyszczone.";
    }
    else
    {
        statusMessage = "Nie mozna wyczyscic pola startowego.";
    }
}

void ConsoleUI::run()
{
    RawTerminalMode rawMode;
    game.newGame(40);

    bool running = true;

    while (running && !game.isCompleted())
    {
        render();

        Key key = readKey();
        int value = keyToValue(key);

        if (value > 0)
        {
            enterValue(value);
            continue;
        }

        switch (key)
        {
        case Key::Up:
            moveSelection(-1, 0);
            break;
        case Key::Down:
            moveSelection(1, 0);
            break;
        case Key::Left:
            moveSelection(0, -1);
            break;
        case Key::Right:
            moveSelection(0, 1);
            break;
        case Key::Digit0:
        case Key::Backspace:
        case Key::Delete:
            clearSelectedCell();
            break;
        case Key::Quit:
            running = false;
            break;
        default:
            statusMessage = "Nieznany klawisz.";
            break;
        }
    }

    render();

    if (game.isCompleted())
    {
        std::cout << "Gratulacje, plansza zostala poprawnie rozwiazana." << std::endl;
    }
    else
    {
        std::cout << "Koniec gry." << std::endl;
    }
}

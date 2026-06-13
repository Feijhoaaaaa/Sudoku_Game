#include "ConsoleUI.h"

#include "LargeSudokuMode.h"
#include "SaveManager.h"
#include "StandardSudokuMode.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

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
    Enter,
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
    Save,
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

    if (character == '\n' || character == '\r')
    {
        return Key::Enter;
    }

    if (character == 'q' || character == 'Q')
    {
        return Key::Quit;
    }

    if (character == 's' || character == 'S')
    {
        return Key::Save;
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

std::string modeNameForBoxSize(int boxSize)
{
    if (boxSize == 4)
    {
        return "4x4 bloki, plansza 16x16";
    }

    return "3x3 bloki, plansza 9x9";
}

std::string menuOptionText(int option, Difficulty difficulty, int boxSize)
{
    switch (option)
    {
    case 0:
        return "Nowa gra";
    case 1:
        return "Wczytaj zapis";
    case 2:
        return "Poziom trudnosci: " + difficultyToString(difficulty);
    case 3:
        return "Tryb gry: " + modeNameForBoxSize(boxSize);
    case 4:
        return "Wyjscie";
    default:
        return "";
    }
}

Difficulty nextDifficulty(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        return Difficulty::Medium;
    case Difficulty::Medium:
        return Difficulty::Hard;
    case Difficulty::Hard:
        return Difficulty::Easy;
    }

    return Difficulty::Medium;
}

std::string formatValue(int value)
{
    if (value == 0)
    {
        return ".";
    }

    return std::to_string(value);
}

std::string separatorLine(int size, int boxSize, int cellWidth)
{
    std::string line;

    for (int col = 0; col < size; col++)
    {
        if (col % boxSize == 0 && col != 0)
        {
            line += "+";
        }

        line += std::string(cellWidth + 1, '-');
    }

    return line;
}

std::string helpLine(int row, int maxValue)
{
    switch (row)
    {
    case 0:
        return "Sterowanie:";
    case 1:
        return "  Strzalki     - ruch kursorem";
    case 2:
        return maxValue > 9 ? "  1-9          - wpisz 1-9" : "  1-9          - wpisz cyfre";
    case 3:
        return maxValue > 9 ? "  1 potem 0    - wpisz 10" : "  0            - wyczysc pole";
    case 4:
        return maxValue > 9 ? "  1 potem 1    - wpisz 11" : "  Backspace    - wyczysc pole";
    case 5:
        return maxValue > 9 ? "  1 potem 2-6  - wpisz 12-16" : "  Delete       - wyczysc pole";
    case 6:
        return maxValue > 9 ? "  1 + Enter    - wpisz 1" : "  s            - zapisz gre";
    case 7:
        return maxValue > 9 ? "  0/Del        - wyczysc pole" : "  q            - powrot do menu";
    case 8:
        return maxValue > 9 ? "  s            - zapisz gre" : "Kolory:";
    case 9:
        return maxValue > 9 ? "  q            - powrot do menu" : "  bialy        - pola startowe";
    case 10:
        return maxValue > 9 ? "Kolory:" : "  zielony      - pola gracza";
    case 11:
        return maxValue > 9 ? "  bialy        - pola startowe" : "  niebieski    - aktywne pole";
    case 12:
        return maxValue > 9 ? "  zielony      - pola gracza" : "";
    case 13:
        return maxValue > 9 ? "  niebieski    - aktywne pole" : "";
    default:
        return "";
    }
}

void printHelpLine(int row, int maxValue)
{
    std::string line = helpLine(row, maxValue);

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
    : selectedPosition(0, 0),
      statusMessage("Wybierz opcje z menu."),
      selectedDifficulty(Difficulty::Medium),
      selectedBoxSize(3),
      pendingLeadingDigit(-1)
{
}

std::unique_ptr<GameMode> ConsoleUI::createSelectedMode() const
{
    if (selectedBoxSize == 4)
    {
        return std::make_unique<LargeSudokuMode>();
    }

    return std::make_unique<StandardSudokuMode>();
}

void ConsoleUI::renderMenu(int selectedOption) const
{
    clearScreen();

    std::cout << TITLE_COLOR << "Sudoku" << RESET_COLOR << std::endl;
    std::cout << STATUS_COLOR << statusMessage << RESET_COLOR << std::endl;
    std::cout << std::endl;

    for (int option = 0; option < 5; option++)
    {
        if (option == selectedOption)
        {
            std::cout << SELECTED_CELL_COLOR << "> " << menuOptionText(option, selectedDifficulty, selectedBoxSize)
                      << RESET_COLOR << std::endl;
        }
        else
        {
            std::cout << "  " << menuOptionText(option, selectedDifficulty, selectedBoxSize) << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << HELP_TEXT_COLOR << "Strzalki: wybor | Enter: zatwierdz | 1-5: szybki wybor | q: wyjscie"
              << RESET_COLOR << std::endl;
}

void ConsoleUI::runMenu()
{
    int selectedOption = 0;
    bool running = true;

    while (running)
    {
        renderMenu(selectedOption);

        Key key = readKey();
        int digit = keyToValue(key);
        int chosenOption = -1;

        if (digit >= 1 && digit <= 5)
        {
            chosenOption = digit - 1;
        }

        switch (key)
        {
        case Key::Up:
            selectedOption = (selectedOption + 4) % 5;
            break;
        case Key::Down:
            selectedOption = (selectedOption + 1) % 5;
            break;
        case Key::Enter:
            chosenOption = selectedOption;
            break;
        case Key::Quit:
            running = false;
            break;
        default:
            break;
        }

        if (chosenOption == 0)
        {
            startNewGame();
            runGame();
        }
        else if (chosenOption == 1)
        {
            if (loadSavedGame())
            {
                runGame();
            }
        }
        else if (chosenOption == 2)
        {
            selectedDifficulty = nextDifficulty(selectedDifficulty);
            statusMessage = "Zmieniono poziom trudnosci.";
        }
        else if (chosenOption == 3)
        {
            selectedBoxSize = selectedBoxSize == 3 ? 4 : 3;
            statusMessage = "Zmieniono tryb gry.";
        }
        else if (chosenOption == 4)
        {
            running = false;
        }
    }
}

void ConsoleUI::renderGame() const
{
    clearScreen();

    if (!game)
    {
        return;
    }

    int size = game->getSize();
    int boxSize = game->getBoxSize();
    int cellWidth = game->getMaxValue() > 9 ? 2 : 1;
    int helpRow = 0;

    std::cout << TITLE_COLOR << game->getName() << RESET_COLOR << std::endl;
    std::cout << STATUS_COLOR << "Trudnosc: " << difficultyToString(game->getDifficulty()) << " | "
              << statusMessage << RESET_COLOR << std::endl;
    std::cout << std::endl;

    for (int row = 0; row < size; row++)
    {
        if (row % boxSize == 0 && row != 0)
        {
            std::cout << STATUS_COLOR << separatorLine(size, boxSize, cellWidth) << RESET_COLOR << "   ";
            printHelpLine(helpRow, game->getMaxValue());
            std::cout << std::endl;
            helpRow++;
        }

        for (int col = 0; col < size; col++)
        {
            if (col % boxSize == 0 && col != 0)
            {
                std::cout << STATUS_COLOR << "| " << RESET_COLOR;
            }

            Position currentPosition(row, col);
            bool selected = currentPosition == selectedPosition;
            bool fixed = game->isFixed(row, col);
            int value = game->getValue(row, col);

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

            std::cout << std::setw(cellWidth) << formatValue(value) << " " << RESET_COLOR;
        }

        std::cout << "   ";
        printHelpLine(helpRow, game->getMaxValue());
        std::cout << std::endl;
        helpRow++;
    }

    std::cout << std::endl;
}

void ConsoleUI::runGame()
{
    if (!game)
    {
        return;
    }

    bool playing = true;

    while (playing && !game->isCompleted())
    {
        renderGame();

        Key key = readKey();
        int value = keyToValue(key);

        if (value >= 0)
        {
            handleDigit(value);
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
        case Key::Enter:
            if (pendingLeadingDigit == 1)
            {
                enterValue(1);
                pendingLeadingDigit = -1;
            }
            break;
        case Key::Backspace:
            if (pendingLeadingDigit != -1)
            {
                pendingLeadingDigit = -1;
                statusMessage = "Anulowano wpisywanie wartosci dwucyfrowej.";
            }
            else
            {
                clearSelectedCell();
            }
            break;
        case Key::Delete:
            clearSelectedCell();
            break;
        case Key::Save:
            saveCurrentGame();
            break;
        case Key::Quit:
            pendingLeadingDigit = -1;
            statusMessage = "Powrot do menu.";
            playing = false;
            break;
        default:
            pendingLeadingDigit = -1;
            statusMessage = "Nieznany klawisz.";
            break;
        }
    }

    if (game && game->isCompleted())
    {
        renderGame();
        std::cout << "Gratulacje, plansza zostala poprawnie rozwiazana." << std::endl;
        readKey();
    }
}

void ConsoleUI::moveSelection(int rowDelta, int colDelta)
{
    if (!game)
    {
        return;
    }

    int size = game->getSize();
    int newRow = (selectedPosition.getRow() + rowDelta + size) % size;
    int newCol = (selectedPosition.getCol() + colDelta + size) % size;

    selectedPosition.set(newRow, newCol);
    pendingLeadingDigit = -1;
}

void ConsoleUI::handleDigit(int value)
{
    if (!game)
    {
        return;
    }

    if (game->getMaxValue() <= 9)
    {
        if (value == 0)
        {
            clearSelectedCell();
        }
        else
        {
            enterValue(value);
        }

        return;
    }

    if (pendingLeadingDigit == 1)
    {
        int twoDigitValue = 10 + value;
        pendingLeadingDigit = -1;

        if (twoDigitValue <= game->getMaxValue())
        {
            enterValue(twoDigitValue);
        }
        else
        {
            statusMessage = "W trybie 4x4 dostepne sa wartosci od 1 do 16.";
        }

        return;
    }

    if (value == 0)
    {
        clearSelectedCell();
    }
    else if (value == 1)
    {
        pendingLeadingDigit = 1;
        statusMessage = "Nacisnij 0-6 dla 10-16 albo Enter dla 1.";
    }
    else
    {
        enterValue(value);
    }
}

void ConsoleUI::enterValue(int value)
{
    if (!game)
    {
        return;
    }

    if (game->makeMove(selectedPosition.getRow(), selectedPosition.getCol(), value))
    {
        std::ostringstream stream;
        stream << "Wpisano " << value << " w polu " << selectedPosition << ".";
        statusMessage = stream.str();
    }
    else
    {
        statusMessage = "Nie mozna wpisac tej wartosci w wybrane pole.";
    }
}

void ConsoleUI::clearSelectedCell()
{
    if (!game)
    {
        return;
    }

    pendingLeadingDigit = -1;

    if (game->clearCell(selectedPosition.getRow(), selectedPosition.getCol()))
    {
        statusMessage = "Pole wyczyszczone.";
    }
    else
    {
        statusMessage = "Nie mozna wyczyscic pola startowego.";
    }
}

void ConsoleUI::saveCurrentGame()
{
    if (!game)
    {
        return;
    }

    if (SaveManager::save(*game))
    {
        statusMessage = "Zapisano gre do pliku sudoku_save.txt.";
    }
    else
    {
        statusMessage = "Nie udalo sie zapisac gry.";
    }
}

void ConsoleUI::startNewGame()
{
    game = createSelectedMode();
    game->startNew(selectedDifficulty);
    selectedPosition.set(0, 0);
    pendingLeadingDigit = -1;
    statusMessage = "Nowa gra uruchomiona.";
}

bool ConsoleUI::loadSavedGame()
{
    std::unique_ptr<GameMode> loadedGame = SaveManager::load();

    if (!loadedGame)
    {
        statusMessage = "Nie udalo sie wczytac zapisu.";
        return false;
    }

    selectedDifficulty = loadedGame->getDifficulty();
    selectedBoxSize = loadedGame->getBoxSize();
    selectedPosition.set(0, 0);
    pendingLeadingDigit = -1;
    game = std::move(loadedGame);
    statusMessage = "Wczytano zapis gry.";

    return true;
}

void ConsoleUI::run()
{
    RawTerminalMode rawMode;
    runMenu();
    clearScreen();
    std::cout << "Koniec programu." << std::endl;
}

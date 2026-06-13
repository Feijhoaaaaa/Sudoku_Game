#include "GameMode.h"

std::string difficultyToString(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        return "latwy";
    case Difficulty::Medium:
        return "sredni";
    case Difficulty::Hard:
        return "trudny";
    }

    return "sredni";
}

Difficulty difficultyFromString(const std::string& text)
{
    if (text == "latwy")
    {
        return Difficulty::Easy;
    }

    if (text == "trudny")
    {
        return Difficulty::Hard;
    }

    return Difficulty::Medium;
}

# Sudoku Game

Konsolowa gra Sudoku 9x9 w C++.

## Funkcje

- generowanie losowej planszy Sudoku,
- sprawdzanie zasad Sudoku,
- rozwiązywanie planszy algorytmem backtrackingu,
- interaktywna gra w terminalu,
- sterowanie strzałkami,
- wpisywanie cyfr `1-9`,
- czyszczenie pola przez `0`, Backspace albo Delete,
- zakończenie gry przez `q`.

## Budowanie

```bash
cmake -S . -B build/Desktop-Debug
cmake --build build/Desktop-Debug
```

## Uruchamianie

```bash
./build/Desktop-Debug/Sudoku_Game
```

Program powinien być uruchamiany w prawdziwym terminalu, ponieważ korzysta
z bezpośredniej obsługi klawiatury i sekwencji ANSI.

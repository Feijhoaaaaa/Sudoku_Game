# Sudoku Game

Konsolowa gra Sudoku napisana w C++17. Projekt pokazuje programowanie
obiektowe: klasy, hermetyzację, konstruktory, destruktory, operatory, funkcję
zaprzyjaźnioną, dziedziczenie, klasę abstrakcyjną i polimorfizm.

## Funkcje

- generowanie plansz Sudoku,
- tryb klasyczny 9x9 oraz większy tryb 16x16,
- wybór poziomu trudności,
- sprawdzanie zasad Sudoku przy wpisywaniu wartości,
- rozwiązywanie planszy algorytmem backtrackingu,
- interaktywna gra w terminalu,
- sterowanie strzałkami,
- zapis i odczyt gry z pliku `sudoku_save.txt`,
- kolorowy interfejs terminalowy,
- obsługa Linuksa i Windows.

## Budowanie

Build lokalny:

```bash
cmake -S . -B build
cmake --build build
```

Build pliku `.exe` dla Windows z poziomu Linuksa:

```bash
cmake -S . -B build/windows-x64-static \
  -DCMAKE_SYSTEM_NAME=Windows \
  -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
  -DCMAKE_BUILD_TYPE=Release \
  "-DCMAKE_EXE_LINKER_FLAGS=-static -static-libgcc -static-libstdc++"

cmake --build build/windows-x64-static --parallel
```

## Uruchamianie

Linux:

```bash
./build/Sudoku_Game
```

Windows:

```powershell
.\Sudoku_Game.exe
```

Program powinien być uruchamiany w prawdziwym terminalu, ponieważ korzysta
z bezpośredniej obsługi klawiatury i sekwencji ANSI.

## Sterowanie

- strzałki: ruch po menu i planszy,
- `Enter`: zatwierdzenie opcji,
- `1-9`: wpisywanie wartości,
- `0`, Backspace, Delete: czyszczenie pola gracza,
- `s`: zapis gry,
- `q`: powrót do menu albo wyjście z programu.

W trybie 16x16 wartości 10-16 wpisuje się jako dwie cyfry, np. `1` potem `6`
daje wartość 16. Aby wpisać samo 1, należy nacisnąć `1`, a potem `Enter`.

## Dokumentacja

- instrukcja użytkownika: `docs/user_manual.pdf`,
- opis użytych narzędzi: `docs/tools_used.pdf`,
- dokumentacja Doxygen HTML: `html/index.html`,
- dokumentacja Doxygen PDF: `latex/refman.pdf`,
- diagram klas: `uml/sudoku_class_diagram.png`.

Źródła dokumentacji użytkownika znajdują się w katalogu `docs`.

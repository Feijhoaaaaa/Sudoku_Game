cmake_minimum_required(VERSION 3.16)

project(Sudoku_Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sudoku_Game main.cpp
    core/Cell.h core/Cell.cpp
    core/Board.h core/Board.cpp
    core/Sudokurules.h core/Sudokurules.cpp
    core/Solver.h core/Solver.cpp
    core/Generator.h core/Generator.cpp
    core/SudokuGame.h core/SudokuGame.cpp
    core/ConsoleUI.h core/ConsoleUI.cpp)

include(GNUInstallDirs)
install(TARGETS Sudoku_Game
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

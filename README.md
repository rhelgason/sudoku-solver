# sudoku-solver
Solves for a valid solution to any 9x9 Sudoku puzzle using a variety of optimization techniques.

## How to Play
Sudoku is a classic logic puzzle in which the player is provided a 9x9 grid subdivided into 9 separate 3x3 subgrids. The player's objective is to fill each of the board's 81 squares with a digit so that each row, each column, and each subgrid contain all of the digits from 1 to 9. Subsequently, no digit may be repeated within a row, column, or subgrid. Before the game begins, some of the squares should already be filled with digits to give the player hints towards the correct solution.

## Usage
The program must be provided with a `board.txt` file to correctly operate. This file should contain the unsolved Sudoku board for the program to complete. Each square should contain a digit, separated from surrounding squares with whitespace. Any squares that do not have any starting digits should contain a period (".") for preprocessing. Any example of an unsolved Sudoku board is below:

<p align="center">
  <img src="https://github.com/rhelgason/sudoku-solver/blob/master/img/board-example.PNG" alt="example board"/>
<p>

It is not necessary that subgrids are divided with extra space as shown above, but it is helpful to view the board this way. Within the `example-boards/` directory, five unsolved boards have been provided for testing purposes. A blank board has also been provided for ease of creating your own unsolved board. To use any board with the program, simply move the desired file to the top directory and rename it to `board.txt`.

A Makefile has been included in the top directory. To use the Makefile, the make utility must be available. The program can be compiled and ran using any of the commands detailed below under "How the Algorithms Work". This will create and run executable files for use by the C++ runtime. To remove all of the executable files created during compilation, run the `make clean` command. If the make utility is not available, all executable files can be cleaned using `rm -f *.exe`.

## How the Algorithms Work

### Backtracking
The simplest of all the algorithms is backtracking, a type of brute force search. It is a depth-first search algorithm because it follows a potential solution as far as it can until it is considered impossible. The algorithm begins with the upper left square, placing the digit "1". It then proceeds to the next square, recursively attmepting all possible digits in each square until a solution is located. If no solution is found, the algorithm returns to the first square and replaces the digit with a "2". The algorithm repeats in this manner until a solution is found.

The strength of this algorithm lies in its simplicity. As long as a solution exists, it is guaranteed to be found. The haphazardness of the algorithm ensures that running time is largely unrelated to puzzle's difficulty. This could be beneficial with difficult puzzles, but it may also be limiting with relatively simple puzzles. The backtracking algorithm is ultimately inefficient because it cannot guarantee a quick solution to any Sudoku puzzle.

With the make utility, the backtracking algorithm can be compiled and ran with the `make backtrack` command. If the make utility is not available, the program can still be ran using C++ commands. Compile all of the files with `g++ -std=c++11 -o backtrack src/backtrack.cpp src/Grid.cpp src/Box.cpp` and run the program with `./backtrack board.txt`.

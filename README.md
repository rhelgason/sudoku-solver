# sudoku-solver
Solves for a valid solution to any Sudoku puzzle using a variety of optimization techniques.

## How to Play
Sudoku is a classic logic puzzle in which the player is provided a 9x9 grid subdivided into 9 separate 3x3 subgrids. The player's objective is to fill each of the board's 81 squares with a digit so that each row, each column, and each subgrid contain all of the digits from 1 to 9. Subsequently, no digit may be repeated within a row, column, or subgrid. Before the game begins, some of the squares should already be filled with digits to give the player hints towards the correct solution.

In this implementation, the user is allowed to use any size Sudoku board up to 16, so long as it follows the basic rules of Sudoku. That is, each cell has a number (between 1 and the board dimension), each row contains one of each number, each column contains one of each number, and each subgrid contains one of each number. For boards with irregular shapes, grids will have to be subdivided into logically sized subgrids. For example, a board of size 10 must be separated into subgrids of either 2x5 or 5x2. The board may have multiple valid solutions, but the program will only return the first solution it finds.

## Usage
The program must be provided with a `board.txt` file to correctly operate. At the top of this file should be a section defining the dimensions of the board. On the first line, the dimension of the board is input. The following line has the height and width of each subgrid, respectively, separated by whitespace. The following line should then contain three dashes ("---") for the program to ensure the dimensions have been input adequately.

This file should next contain the unsolved Sudoku board for the program to complete. Each square should contain a digit, separated from surrounding squares with whitespace. Any squares that do not have any starting digits should contain a period (".") for preprocessing. Any example of an unsolved Sudoku board is below:

<p align="center">
  <img src="https://github.com/rhelgason/sudoku-solver/blob/master/img/board-example.PNG" alt="example board"/>
<p>

It is not necessary that subgrids are divided with extra space as shown above, but it is helpful to view the board this way. Within the `example-boards/` directory, unsolved boards of a variety of sizes have been provided for testing purposes. Blank boards have also been provided for ease of creating your own unsolved boards. For proof of concept, some extra Sudoku puzzles with no possible solution have been included. To use any board with the program, simply move the desired file to the top directory and rename it to `board.txt`.

Some boards will have irregular shapes. This can be treated the same way during the creation process, so long as the above rules have been followed. Note that when the dimension rises about 9, boards will use hexadecimal digits to maintain a better visual format. Numbers 10 through 15 can instead be replaced by the characters A through F, in that order. If the board is of size 16, then a 0 can be used to represent the 16th number. An irregular board of size 10 has been included below for reference:

<p align="center">
  <img src="https://github.com/rhelgason/sudoku-solver/blob/master/img/board-example-10.PNG" alt="example board size 10"/>
<p>

A Makefile has been included in the top directory. To use the Makefile, the make utility must be available. The program can be compiled and ran using any of the commands detailed below under "How the Algorithms Work". This will create and run executable files for use by the C++ runtime. To remove all of the executable files created during compilation, run the `make clean` command. If the make utility is not available, all executable files can be cleaned using `rm -f *.exe`.

## How the Algorithms Work

### Backtracking
The simplest of all the algorithms is backtracking, a type of brute force search. It is a depth-first search algorithm because it follows a potential solution as far as it can until it is considered impossible. The algorithm begins with the upper left square, placing the digit "1". It then proceeds to the next square, recursively attmepting all possible digits in each square until a solution is located. If no solution is found, the algorithm returns to the first square and replaces the digit with a "2". The algorithm repeats in this manner until a solution is found.

The strength of this algorithm lies in its simplicity. The algorithm is not very complex to implement, allowing for it to be applied much more easily. The haphazardness of the algorithm ensures that running time is largely unrelated to puzzle's difficulty. This could be beneficial with difficult puzzles, but it may also be limiting with relatively simple puzzles. The backtracking algorithm is ultimately inefficient because it cannot guarantee a quick solution to any Sudoku puzzle.

With the make utility, the backtracking algorithm can be compiled and ran with the `make backtrack` command. If the make utility is not available, the program can still be ran using C++ commands. Compile all of the files with `g++ -std=c++11 -Wall -o backtrack src/Backtrack.cpp src/Grid.cpp src/Box.cpp src/Node.cpp` and run the program with `./backtrack board.txt`.

### Algorithm X
The second algorithm is another type of depth-first search. The basis of Algorithm X is exact cover problems. Given a matrix of bit values (0s and 1s), an exact cover is a selection of rows so that each column contains a single 1 between all the selected rows. Donald Knuth developed Algorithm X as a recursive method of finding a solution to any exact cover problem. Although this algorithm also implements a little bit of backtracking, it does so in a much more efficient manner. The best explanation of this complex algorithm that I have been able to find comes from [Zendoku](https://garethrees.org/2007/06/10/zendoku-generation/#section-4).

Conveniently, Sudoku puzzles can be implemented as exact cover problems. The rows represent all possible placements of digits (placing a 1 in the first square, placing a 2 in the first square, and so on). Like any other exact cover problem, the columns represent the constraints. For Sudoku, the constraints are that each cell has a number, each row contains one of each number, each column contains one of each number, and each subgrid contains one of each number. A mockup of an exact cover matrix for a 9x9 Sudoku can be viewed [here](https://www.stolaf.edu/people/hansonr/sudoku/exactcovermatrix.htm). After creating the cover matrix with a fair bit of math, the puzzle can be recursively solved much quicker than with backtracking.

With the make utility, Algorithm X can be compiled and ran with the `make algorithmX` command. If the make utility is not available, the program can still be ran using C++ commands. Compile all of the files with `g++ -std=c++11 -Wall -o algorithmX src/AlgorithmX.cpp src/Grid.cpp src/Box.cpp src/Node.cpp` and run the program with `./algorithmX board.txt`.

### Dancing Links
The third algorithm is a further expansion on Algorithm X. This algorithm is very similar to Algorithm X, except that it is implemented using a matrix of doubly linked circular lists. Each node in the exact cover matrix contains a pointer to its right, left, upwards, and downwards nodes in the matrix. The process of removing and reinserting columns from the matrix is extremely simple using these linked lists, so the algorithm can run much more quickly than with the arrays from Algorithm X.

For obvious reasons, this is a little more confusing to implement. However, the improved efficiency is very clear to see. Even with size 16 Sudoku boards, this algorithm is almost always able to return a solution within a single second of runtime. In comparison, Algorithm X was unable to return a solution on some size 16 Sudoku boards in a reasonable amount of time (think upwards of 24 hours). Despite the similarities between these algorithms, Dancing Links proves the usefulness of intelligent data structures. Donald Knuth explains his Dancing Links algorithm best in his [research paper](https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf).

With the make utility, Dancing Links can be compiled and ran with the `make dancingLinks` command. If the make utility is not available, the program can still be ran using C++ commands. Compile all of the files with `g++ -std=c++11 -Wall -o dancingLinks src/DancingLinks.cpp src/Grid.cpp src/Box.cpp src/Node.cpp` and run the program with `./dancingLinks board.txt`.
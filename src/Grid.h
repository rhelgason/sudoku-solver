#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <unordered_set>
#include "Box.h"
using namespace std;

// class representing the entire board for the Sudoku puzzle.
class Grid {
    private:
        int dim;
        Box*** board;

    public:
        // basic constructor for the Grid
        Grid(int dim, int** inBoard);

        // returns a string version of the Grid for output
        string toString();
};

#endif
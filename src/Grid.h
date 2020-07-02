#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <set>
#include "Box.h"
using namespace std;

// class representing the entire board for the Sudoku puzzle.
class Grid {
    private:
        int dim;
        Box*** board;
        set<int>* rows;
        set<int>* cols;
        set<int>** divs;

    public:
        // basic constructor for the Grid
        Grid(int dim, int** inBoard);

        // determine if a number is valid in a position
        bool valid(int row, int col, int num);

        // place a number in the tracking sets
        void track(int row, int col, int num);

        // remove a number from the tracking sets
        void untrack(int row, int col, int num);

        // returns a string version of the Grid for output
        string toString();

        // recursive function for solving board
        bool solve(int row, int col);

        // destructor for Grid class
        ~Grid();
};

#endif
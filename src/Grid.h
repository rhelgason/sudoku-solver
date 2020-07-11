#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include "Box.h"
using namespace std;

// class representing the entire board for the Sudoku puzzle.
class Grid {
    private:
        int dim;
        int subHeight;
        int subWidth;
        bool** rows;
        bool** cols;
        bool*** divs;
        Box*** board;

        // algorithm x data structures
        bool** matrix;
        int* cand;
        bool* validRow;
        bool* validCol;

    public:
        // basic constructor for the Grid
        Grid(ifstream& inFile, int**& inBoard, int& dim);
        
        // determine if a number is valid in a position
        bool valid(int row, int col, int num);

        // place a number in the tracking sets
        void track(int row, int col, int num);

        // remove a number from the tracking sets
        void untrack(int row, int col, int num);

        // recursive function for solving with backtracking
        bool solveBacktrack(int row, int col);

        // constructor helper for algorithm x method
        void algorithmX(int** inBoard);

        // add a row to the matrix
        void matrixRow(int index, int row, int col, int num);

        // recursive function for solving with algorithm x
        bool solveAlgorithmX();

        // returns a string version of the Grid for output
        string toString();

        // destructor for Grid class
        ~Grid();

        // destructor helper for algorithm x
        void destructAlgorithmX();
};

#endif
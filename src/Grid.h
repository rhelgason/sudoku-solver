#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "Box.h"
using namespace std;

// class representing the entire board for the Sudoku puzzle.
class Grid {
    private:
        int dim;
        bool** rows;
        bool** cols;
        bool*** divs;
        Box*** board;

        // algorithm x data structures
        bool** matrix;
        int* cand;
        bool* valCand;

    public:
        // basic constructor for the Grid
        Grid(int dim, ifstream& inFile, int** inBoard);
        
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

        //void printMatrix();

        // returns a string version of the Grid for output
        string toString();

        // destructor for Grid class
        ~Grid();

        // destructor helper for algorithm x
        void destructAlgorithmX();
};

#endif
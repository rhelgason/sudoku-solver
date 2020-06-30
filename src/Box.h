#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <unordered_set>
using namespace std;

// class representing a single square of the Sudoku puzzle.
class Box {
    private:
        int value;
        unordered_set<int> choices;
    
    public:
        // basic constructor for initializing an unknown Box.
        Box(int dim);
        
        // constructor for initializing a known Box.
        Box(int dim, int val);

        // get the value of the Box
        getValue();
};

#endif
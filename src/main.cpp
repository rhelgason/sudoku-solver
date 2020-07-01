#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Grid.h"
#include "Box.h"

int main(int argc, char* argv[]) {
    // initialize variables
    const int dim = 9;
    int** inBoard = new int*[dim];
    for (int i = 0; i < dim; i++) inBoard[i] = new int[dim];
    string curr;
    ifstream inFile(argv[1]);
    if (!inFile.is_open()) throw runtime_error("\nError: could not open file.\n");

    // read the board contents
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            try {
                // error checking for single input
                if (inFile.peek() == EOF) throw invalid_argument("");
                inFile >> curr;
                int temp = stoi(curr);
                if (temp > dim || temp < 0) throw out_of_range("");
                inBoard[i][j] = temp;
            } catch (invalid_argument const &e) {
                cout << "\nError: some input in the board was invalid.\n";
                return 1;
            } catch (out_of_range const &e) {
                cout << "\nError: inputs must be between 1 and " << dim << ", inclusive.\n";
                return 1;
            }
        }
    }

    // initialize game board
    Grid* grid;
    try {
        grid = new Grid(dim, inBoard);
    } catch (exception const &e) {
        cout << "\nError: the input board is not valid.\n";
        return 1;
    }
    for (int i = 0; i < dim; i++) {
        delete[] inBoard[i];
    }
    delete[] inBoard;
    inBoard = NULL;

    // solve the board
    cout << "\nSolving this board:\n\n" << grid->toString() << "\n\nWorking..." << endl;
    if (grid->solve(0, 0)) {
        cout << "Board has been solved:\n\n" << grid->toString() << "\n";
    } else {
        cout << "The board could not be solved.\n";
    }
    delete grid;
    grid = NULL;
}
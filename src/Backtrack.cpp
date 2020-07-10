#include <iostream>
#include <fstream>
#include <chrono>
#include "Grid.h"
#include "Box.h"

int main(int argc, char* argv[]) {
    // initialize variables
    const int dim = 9;
    ifstream inFile(argv[1]);
    if (!inFile.is_open()) throw runtime_error("\nError: could not open file.\n");
    int** inBoard = new int*[dim];
    for (int i = 0; i < dim; i++) inBoard[i] = new int[dim];

    // initialize game board
    Grid* grid;
    try {
        grid = new Grid(dim, inFile, inBoard);
    } catch (invalid_argument const &e) {
        cout << "\nError: some input in the board was invalid.\n";
        return 1;
    } catch (out_of_range const &e) {
        cout << "\nError: inputs must be between 1 and " << dim << ", inclusive.\n";
        return 1;
    } catch (exception const &e) {
        cout << "\nError: the input board is not valid.\n";
        return 1;
    }
    inFile.close();
    for (int i = 0; i < dim; i++) {
        delete[] inBoard[i];
    }
    delete[] inBoard;
    inBoard = NULL;

    // solve the board
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    cout << "\nSolving this board:\n\n" << grid->toString() << "\n\nWorking..." << endl;
    if (grid->solveBacktrack(0, 0)) {
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Board has been solved in " << (chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0);
        cout << " seconds:\n\n" << grid->toString() << "\n";
    } else {
        cout << "\nThe board could not be solved.\n";
    }
    delete grid;
    grid = NULL;
}

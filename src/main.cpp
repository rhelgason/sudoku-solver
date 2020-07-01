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
    string currLine;
    ifstream inFile(argv[1]);
    if (!inFile.is_open()) throw runtime_error("Error: could not open file.");

    // read the board contents
    for (int i = 0; i < dim; i++) {
        getline(inFile, currLine);
        unsigned int k = 0;
        for (int j = 0; j < dim; j++) {
            unsigned int len = 0;

            // read integer for a single box
            while ((k + len) < currLine.length() && isdigit(currLine[k + len])) len++;
            if ((k + len) != currLine.length() && currLine[k + len] != ',') {
                cout << "Error: the board contained invalid input." << endl;
                return 1;
            }
            if (len == 0) {
                inBoard[i][j] = 0;
            } else {
                // error checking for integer conversion
                try {
                    int temp = stoi(currLine.substr(k, len));
                    if (temp > dim || temp <= 0) {
                        cout << "Error: inputs must be between 1 and " << dim << ", inclusive." << endl;
                        return 1;
                    }
                    inBoard[i][j] = temp;
                } catch (out_of_range const &e) {
                    cout << "Error: some input was out of range." << endl;
                    return 1;
                }
            }
            k += len + 1;
        }
    }

    // initialize game board
    Grid* grid = new Grid(dim, inBoard);
    for (int i = 0; i < dim; i++) {
        delete[] inBoard[i];
    }
    delete[] inBoard;
    inBoard = NULL;

    // solve the board
    cout << "\nSolving this board:\n\n" << grid->toString() << "\n\nWorking...\n";
    //grid->solve(0, 0);
    delete grid;
    grid = NULL;
}
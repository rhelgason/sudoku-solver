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
            if ((k + len) != currLine.length() && currLine[k + len] != ',') throw new runtime_error("Error: the board contained invalid input.");
            if (len == 0) {
                inBoard[i][j] = 0;
            } else {
                try {
                    inBoard[i][j] = stoi(currLine.substr(k, len));
                } catch (out_of_range const &e) {
                    cout << "Error: some input was out of range.";
                    return 1;
                }
            }
            k += len + 1;
        }
    }
    Grid* grid = new Grid(dim, inBoard);
}
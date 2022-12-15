#include <iostream>
#include <fstream>
#include <chrono>
#include "Grid.h"
#include "Box.h"

int main(int argc, char* argv[]) {
    // initialize game board
    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cout << "\nError: could not open file." << endl;
        return 1;
    }
    Grid* grid;
    int** inBoard = NULL;
    int dim = 0;
    try {
        grid = new Grid(inFile, inBoard, dim);
        grid->algorithmX(inBoard);
    } catch (invalid_argument const &e) {
        cout << endl << e.what() << endl;
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
    if (grid->solveAlgorithmX()) {
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        auto duration = (chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0);
        double seconds = static_cast<double>(duration);
        if (seconds < 60) {
            cout << "Board has been solved in " << seconds << " seconds:\n\n" << grid->toString() << endl;
        } else  {
            int minutes = seconds / 60;
            seconds = seconds - (minutes * 60);
            cout << "Board has been solved in " << minutes << " minute" << (minutes == 1 ? "" : "s") <<
                " and " << seconds << " seconds:\n\n" << grid->toString() << endl << endl;
        }
    } else {
        cout << "\nThe board could not be solved." << endl << endl;
    }
    grid->destructAlgorithmX();
    delete grid;
    grid = NULL;
}

#include "Grid.h"

Grid::Grid(int dim, int** inBoard) {
    this->dim = dim;
    board = new Box**[dim];
    for (int i = 0; i < dim; i++) {
        board[i] = new Box*[dim];

        for (int j = 0; j < dim; j++) {
            if (inBoard[i][j] == 0) {
                board[i][j] = new Box(dim);
            } else {
                board[i][j] = new Box(dim, inBoard[i][j]);
            }
        }
    }
}

string Grid::toString() {
    string out = "";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            out += to_string(board[i][j]->getValue());
            if (j != dim) out += " ";
            if ((j + 1) % 3 == 0 && j + 1 != dim) out += " ";
        }
        if (i != dim) out += "\n";
        if ((i + 1) % 3 == 0 && i + 1 != dim) out += "\n";
    }
    return out;
}
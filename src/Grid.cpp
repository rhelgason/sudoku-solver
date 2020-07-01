#include "Grid.h"

Grid::Grid(int dim, int** inBoard) {
    // initialize tracking sets
    this->dim = dim;
    rows = new unordered_set<int>[dim];
    cols = new unordered_set<int>[dim];
    divs = new unordered_set<int>*[dim / 3];
    for (int i = 0; i < dim / 3; i++) {
        divs[i] = new unordered_set<int>[dim / 3];
    }

    // initialize game board
    board = new Box**[dim];
    for (int i = 0; i < dim; i++) {
        board[i] = new Box*[dim];

        for (int j = 0; j < dim; j++) {
            if (inBoard[i][j] == 0) {
                board[i][j] = new Box(dim);
            } else {
                if (valid(i, j, inBoard[i][j])) {
                    board[i][j] = new Box(dim, inBoard[i][j]);
                    track(i, j, inBoard[i][j]);
                } else {
                    throw exception();
                }
            }
        }
    }

    // empty tracking sets
    for (int i = 0; i < dim; i++) {
        rows[i].clear();
        cols[i].clear();
        if (i < dim / 3) {
            for (int j = 0; j < dim / 3; j++) {
                divs[i][j].clear();
            }
        }
    }
}

bool Grid::valid(int row, int col, int num) {
    // check if already used
    if (rows[row].find(num) != rows[row].end()) return false;
    if (cols[col].find(num) != cols[col].end()) return false;
    if (divs[row / 3][col / 3].find(num) != divs[row / 3][col / 3].end()) return false;
    return true;
}

void Grid::track(int row, int col, int num) {
    rows[row].insert(num);
    cols[col].insert(num);
    divs[row / 3][col / 3].insert(num);
}

void Grid::untrack(int row, int col, int num) {
    rows[row].erase(num);
    cols[col].erase(num);
    divs[row / 3][col / 3].erase(num);
}

string Grid::toString() {
    string out = "";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            out += to_string(board[i][j]->getValue());
            if (j != dim - 1) out += " ";
            if ((j + 1) % 3 == 0 && j + 1 != dim) out += " ";
        }
        if (i != dim - 1) out += "\n";
        if ((i + 1) % 3 == 0 && i + 1 != dim) out += "\n";
    }
    return out;
}

bool Grid::solve(int row, int col) {
    // increment row and column
    if (col == dim) {
        col = 0;
        row++;
    }

    // base case
    if (row == dim) return true;

    // try all possibilities
    unordered_set<int> choices = board[row][col]->getChoices();
    while (choices.size() > 0) {
        int curr = *choices.begin();
        choices.erase(choices.begin());
        if (valid(row, col, curr)) {
            track(row, col, curr);
            if (solve(row, col + 1)) {
                board[row][col]->setValue(curr);
                return true;
            } else {
                untrack(row, col, curr);
            }
        }
    }

    // not possible to solve
    return false;
}

Grid::~Grid() {
    // destruct tracking sets
    delete[] rows;
    delete[] cols;
    for (int i = 0; i < dim / 3; i++) {
        delete[] divs[i];
    }
    delete[] divs;

    // destruct game board
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}
#include "Grid.h"

Grid::Grid(int dim, ifstream& inFile, int** inBoard) {
    // read the board contents
    this->dim = dim;
    string curr;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            // error checking for single input
            if (inFile.peek() == EOF) throw invalid_argument("");
            inFile >> curr;
            if (curr == ".") {
                inBoard[i][j] = 0;
            }
            else {
                int temp = stoi(curr);
                if (temp > dim || temp < 1) throw out_of_range("");
                inBoard[i][j] = temp;
            }
        }
    }

    // initialize tracking sets
    rows = new bool*[dim];
    cols = new bool*[dim];
    divs = new bool**[dim / 3];
    for (int i = 0; i < dim; i++) {
        rows[i] = new bool[dim];
        cols[i] = new bool[dim];
        for (int j = 0; j < dim; j++) {
            rows[i][j] = false;
            cols[i][j] = false;
        }
    }
    for (int i = 0; i < dim / 3; i++) {
        divs[i] = new bool*[dim / 3];
        for (int j = 0; j < dim / 3; j++) {
            divs[i][j] = new bool[dim];
            for (int k = 0; k < dim; k++) {
                divs[i][j][k] = false;
            }
        }
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
        for (int j = 0; j < dim; j++) {
            rows[i][j] = false;
            cols[i][j] = false;
        }
    }
    for (int i = 0; i < dim / 3; i++) {
        for (int j = 0; j < dim / 3; j++) {
            for (int k = 0; k < dim; k++) {
                divs[i][j][k] = false;
            }
        }
    }
}

bool Grid::valid(int row, int col, int num) {
    // check if already used
    if (rows[row][num - 1]) return false;
    if (cols[col][num - 1]) return false;
    if (divs[row / 3][col / 3][num - 1]) return false;
    return true;
}

void Grid::track(int row, int col, int num) {
    rows[row][num - 1] = true;
    cols[col][num - 1] = true;
    divs[row / 3][col / 3][num - 1] = true;
}

void Grid::untrack(int row, int col, int num) {
    rows[row][num - 1] = false;
    cols[col][num - 1] = false;
    divs[row / 3][col / 3][num - 1] = false;
}

bool Grid::solveBacktrack(int row, int col) {
    // increment row and column
    if (col == dim) {
        col = 0;
        row++;
    }

    // base case
    if (row == dim) return true;

    // try all possibilities
    set<int> choices = board[row][col]->getChoices();
    while (choices.size() > 0) {
        int curr = *choices.begin();
        choices.erase(choices.begin());
        if (valid(row, col, curr)) {
            track(row, col, curr);
            if (solveBacktrack(row, col + 1)) {
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

void Grid::algorithmX(int** inBoard) {
    // candidate arrays
    valCand = new bool[dim * dim * dim];
    cand = new int[dim * dim * 4];
    for (int i = 0; i < (dim * dim * 4); i++) {
        cand[i] = 0;
    }

    // initialize matrix
    matrix = new bool*[dim * dim * dim];
    for (int i = 0; i < (dim * dim * dim); i++) {
        matrix[i] = new bool[dim * dim * 4];

        // determine if box is known
        int row = i / (dim * dim);
        int col = (i % (dim * dim)) / dim;
        int num = ((i % (dim * dim)) % dim) + 1;
        if (inBoard[row][col] != 0 && inBoard[row][col] != num) {
            valCand[i] = false;
            matrixRow(i, row, col, -1);
        } else {
            valCand[i] = true;
            matrixRow(i, row, col, num);
        }
    }
}

void Grid::matrixRow(int index, int row, int col, int num) {
    // make all false
    bool* arr = matrix[index];
    for (int i = 0; i < (dim * dim * 4); i++) {
        arr[i] = false;
    }
    if (num == -1) return;

    // cell constraint
    int i = (row * dim) + col;
    arr[i] = true;
    cand[i]++;

    // row constraint
    i = (dim * dim) + (row * dim) + (num - 1);
    arr[i] = true;
    cand[i]++;

    // column constraint
    i = (dim * dim * 2) + (col * dim) + (num - 1);
    arr[i] = true;
    cand[i]++;

    // subgrid constraint
    int box = (col / 3) + (row / 3) * 3;
    i = (dim * dim * 3) + (box * dim) + (num - 1);
    arr[i] = true;
    cand[i]++;
}

bool Grid::solveAlgorithmX() {
    return true;
}

/*
void Grid::printMatrix() {
    ofstream outFile;
    outFile.open("matrix.txt");
    for (int i = 0; i < (dim * dim * dim); i++) {
        for (int j = 0; j < (dim * dim * 4); j++) {
            if (matrix[i][j]) outFile << "1";
            else outFile << " ";
            if ((j + 1) % (dim * dim) == 0) outFile << "|";
        }
        outFile << endl;
        if ((i + 1) % dim == 0) {
            for (int j = 0; j < (dim * dim * 4); j++) {
                outFile << "-";
                if ((j + 1) % (dim * dim * 4) == 0) outFile << "+";
            }
            outFile << endl;
        }
    }
    outFile.close();
}
*/

string Grid::toString() {
    string out = "";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int val = board[i][j]->getValue();
            out += val == 0 ? "." : to_string(val);
            if (j != dim - 1) out += " ";
            if ((j + 1) % 3 == 0 && j + 1 != dim) out += "| ";
        }
        if (i != dim - 1) out += "\n";
        if ((i + 1) % 3 == 0 && i + 1 != dim) {
            for (int j = 0; j < dim; j++) {
            out += "-";
            if (j != dim - 1) out += "-";
            if ((j + 1) % 3 == 0 && j + 1 != dim) out += "+-";
            }
            out += "\n";
        }
    }
    return out;
}

Grid::~Grid() {
    // destruct tracking sets
    for (int i = 0; i < dim; i++) {
        delete[] rows[i];
        delete[] cols[i];
    }
    delete[] rows;
    delete[] cols;
    for (int i = 0; i < dim / 3; i++) {
        for (int j = 0; j < dim / 3; j++) {
            delete[] divs[i][j];
        }
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

void Grid::destructAlgorithmX() {
    // destruct candidate arrays
    delete[] valCand;
    delete[] cand;

    // destruct matrix
    for (int i = 0; i < (dim * dim * dim); i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
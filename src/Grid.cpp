#include "Grid.h"

Grid::Grid(ifstream& inFile, int**& inBoard, int& dim) {
    string curr;
    try {
        inFile >> curr;
        dim = stoi(curr);
        if (dim > 16) throw out_of_range("");
        this->dim = dim;
        inFile >> curr;
        subHeight = stoi(curr);
        inFile >> curr;
        subWidth = stoi(curr);
        inFile >> curr;
        if (curr != "---") throw invalid_argument("");
        if (dim < 1 || subHeight < 1 || subWidth < 1 || subHeight * subWidth != dim) throw out_of_range("");
    } catch (invalid_argument const &e) {
        throw invalid_argument("Error: there was a mistake in the dimension input.");
    } catch (out_of_range const &e) {
        throw invalid_argument("Error: the input dimensions are not valid.");
    }

    // read the board contents
    inBoard = new int*[dim];
    for (int i = 0; i < dim; i++) inBoard[i] = new int[dim];
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            // error checking for single input
            if (!(inFile >> curr)) throw invalid_argument("Error: the input board did not contain enough information.");
            if (curr == ".") {
                inBoard[i][j] = -1;
            }
            else {
                int temp;
                try {
                    temp = stoi(curr, 0, 16);
                } catch (out_of_range const &e) {
                    throw invalid_argument("Error: inputs must be between 1 and " + to_string(dim) + ", inclusive.");
                } catch (invalid_argument const &e) {
                    throw invalid_argument("Error: some input in the board was invalid.");
                }
                if (dim == 16) {
                    if (temp > dim || temp < 0) throw invalid_argument("Error: inputs must be between 0 and " + to_string(dim) + ", inclusive.");
                } else {
                    if (temp > dim || temp < 1) throw invalid_argument("Error: inputs must be between 1 and " + to_string(dim) + ", inclusive.");
                }
                inBoard[i][j] = temp;
            }
        }
    }
    if (inFile >> curr) throw invalid_argument("Error: the input file contained too much information.");

    // initialize tracking sets
    rows = new bool*[dim];
    cols = new bool*[dim];
    divs = new bool**[subWidth];
    for (int i = 0; i < dim; i++) {
        rows[i] = new bool[dim];
        cols[i] = new bool[dim];
        for (int j = 0; j < dim; j++) {
            rows[i][j] = false;
            cols[i][j] = false;
        }
    }
    for (int i = 0; i < subWidth; i++) {
        divs[i] = new bool*[subHeight];
        for (int j = 0; j < subHeight; j++) {
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
            if (inBoard[i][j] == -1) {
                board[i][j] = new Box(dim);
            } else {
                if (valid(i, j, inBoard[i][j])) {
                    board[i][j] = new Box(dim, inBoard[i][j]);
                    track(i, j, inBoard[i][j]);
                } else {
                    throw invalid_argument("Error: the input board was not valid.");
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
    for (int i = 0; i < subWidth; i++) {
        for (int j = 0; j < subHeight; j++) {
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
    if (divs[row / subHeight][col / subWidth][num - 1]) return false;
    return true;
}

void Grid::track(int row, int col, int num) {
    rows[row][num - 1] = true;
    cols[col][num - 1] = true;
    divs[row / subHeight][col / subWidth][num - 1] = true;
}

void Grid::untrack(int row, int col, int num) {
    rows[row][num - 1] = false;
    cols[col][num - 1] = false;
    divs[row / subHeight][col / subWidth][num - 1] = false;
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
    validRow = new bool[dim * dim * dim];
    validCol = new bool[dim * dim * 4];
    cand = new int[dim * dim * 4];
    for (int i = 0; i < (dim * dim * 4); i++) {
        validCol[i] = true;
        cand[i] = 0;
    }

    // initialize matrix
    matrix = new bool*[dim * dim * dim];
    for (int i = 0; i < (dim * dim * dim); i++) {
        matrix[i] = new bool[dim * dim * 4];
        validRow[i] = true;

        // determine if value is known
        int row = i / (dim * dim);
        int col = (i % (dim * dim)) / dim;
        int num = ((i % (dim * dim)) % dim) + 1;
        if (inBoard[row][col] != -1 && inBoard[row][col] != num) {
            matrixRow(i, row, col, -1);
        } else {
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

    // cell, row, column, and subgrid constraints
    int box = (col / subWidth) + (row / subHeight) * subHeight;
    int pos[4] = { (row * dim) + col,
                   (dim * dim) + (row * dim) + (num - 1),
                   (dim * dim * 2) + (col * dim) + (num - 1),
                   (dim * dim * 3) + (box * dim) + (num - 1) };
    for (int i = 0; i < 4; i++) {
        arr[pos[i]] = true;
        cand[pos[i]]++;
    }
}

bool Grid::solveAlgorithmX() {
    // deterministically select column
    int low = -1;
    for (int i = 0; i < (dim * dim * 4); i++) {
        if (!validCol[i]) continue;
        if (cand[i] < cand[low] || low == -1) low = i;
    }
    if (low == -1) return true;

    // nondeterministically try rows
    vector<int> rows;
    for (int i = 0; i < (dim * dim * dim); i++) {
        if (matrix[i][low] && validRow[i]) rows.push_back(i);
    }
    for (int r : rows) {
        // eliminate rows for partial solution
        vector<int> delCol;
        vector<int> delRow;
        for (int j = 0; j < (dim * dim * 4); j++) {
            if (!matrix[r][j] || !validCol[j]) continue;
            for (int i = 0; i < (dim * dim * dim); i++) {
                if (!matrix[i][j] || !validRow[i]) continue;
                validRow[i] = false;
                delRow.push_back(i);
            }
            validCol[j] = false;
            delCol.push_back(j);
        }

        if (solveAlgorithmX()) {
            // add valid solution to grid
            int row = r / (dim * dim);
            int col = (r % (dim * dim)) / dim;
            int num = ((r % (dim * dim)) % dim) + 1;
            board[row][col]->setValue(num);
            return true;
        } else {
            // reset and continue search
            for (int i : delRow) validRow[i] = true;
            for (int j : delCol) validCol[j] = true;
            validRow[r] = true;
        }
    }

    // no solution was found
    return false;
}

string Grid::toString() {
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    string out = "";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int val = board[i][j]->getValue();
            out += (val == -1) ? '.' : hex[val];
            if (j != dim - 1) out += " ";
            else break;
            if ((j + 1) % subWidth == 0) out += "| ";
        }
        if (i != dim - 1) out += "\n";
        if ((i + 1) % subHeight == 0 && i + 1 != dim) {
            for (int j = 0; j < dim; j++) {
                out += '-';
                if (j != dim - 1) out += "-";
                else break;
                if ((j + 1) % subWidth == 0) out += "+-";
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
    for (int i = 0; i < subWidth; i++) {
        for (int j = 0; j < subHeight; j++) {
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
    delete[] validRow;
    delete[] validCol;
    delete[] cand;

    // destruct matrix
    for (int i = 0; i < (dim * dim * dim); i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
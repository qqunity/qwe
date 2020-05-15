#include "TicTacToe.h"

TicTacToe::TicTacToe(unsigned int gridSize) {
    this->gridSize = gridSize;
    this->cntMoves = 0;
    unsigned int shape[] = {this->gridSize, this->gridSize};
    this->grid.setShape(shape);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            grid[i][j] = this->symbols.blank;
        }
    }
}

void TicTacToe::printGrid() {
    std::cout << grid;
}

void TicTacToe::setSymbol(unsigned int i, unsigned int j, char symbol) {
    if (this->grid[i][j] == this->symbols.blank) {
        this->grid[i][j] = symbol;
        ++this->cntMoves;
    } else {
        throw Exception("The cage is occupied", __LINE__, __FILE__);
    }
}

char TicTacToe::getSymbol(unsigned int i, unsigned int j) {
    return this->grid[i][j];
}

bool TicTacToe::checkDraw() {
    return this->cntMoves == this->gridSize * this->gridSize;
}

bool TicTacToe::checkWin() {
    char buffSym;
    bool win;
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        win = true;
        buffSym = this->grid[i][0];
        for (unsigned int j = 1; j < this->gridSize; ++j) {
            if (this->grid[i][j] != buffSym || buffSym == this->symbols.blank) {
                win = false;
                break;
            }
        }
        if (win) {
            return true;
        }
    }
    for (unsigned int j = 0; j < this->gridSize; ++j) {
        win = true;
        buffSym = this->grid[0][j];
        for (unsigned int i = 1; i < this->gridSize; ++i) {
            if (this->grid[i][j] != buffSym || buffSym == this->symbols.blank) {
                win = false;
                break;
            }
        }
        if (win) {
            return true;
        }
    }
    win = true;
    buffSym = this->grid[0][0];
    for (unsigned int i = 1; i < this->gridSize; ++i) {
        if (this->grid[i][i] != buffSym || buffSym == this->symbols.blank) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    win = true;
    buffSym = this->grid[0][this->gridSize - 1];
    for (unsigned int k = 1; k < this->gridSize; ++k) {
        if (this->grid[k][this->gridSize - 1 - k] != buffSym || buffSym == this->symbols.blank) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    return false;
}

bool TicTacToe::checkFieldFullness(unsigned int i, unsigned int j) {
    return this->grid[i][j] == this->symbols.blank;
}

TicTacToe::TicTacToe() {
    this->gridSize = 0;
    this->cntMoves = 0;
}

void TicTacToe::setGridSize(unsigned int size) {
    this->gridSize = size;
    unsigned int shape[] = {this->gridSize, this->gridSize};
    this->grid.setShape(shape);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            grid[i][j] = this->symbols.blank;
        }
    }
}

void TicTacToe::restart() {
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            grid[i][j] = this->symbols.blank;
        }
    }
    this->cntMoves = 0;
}

TicTacToe::~TicTacToe() = default;

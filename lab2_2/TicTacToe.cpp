#include "TicTacToe.hpp"

TicTacToe::TicTacToe(unsigned int gridSize) {
    this->gridSize = gridSize;
    this->cntMoves = 0;
    this->grid.setShape(std::make_pair(this->gridSize, this->gridSize));
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            this->grid[i][j] = this->symbols.blank;
        }
    }
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        this->gameBranch.push_back(' ');
    }
}

void TicTacToe::printGrid() {
    std::cout << "---------\n";
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        std::cout << "| ";
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            std::cout << this->grid[i][j] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "---------\n";
}

void TicTacToe::setSymbol(unsigned int i, unsigned int j, char symbol) {
    if (this->grid[i][j] == this->symbols.blank) {
        this->grid[i][j] = symbol;
        this->gameBranch[i * this->gridSize + j] = symbol;
        ++this->cntMoves;
    } else {
        throw exceptions::GameException("The cage is occupied", __LINE__, __FILE__);
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

bool TicTacToe::checkWin(char symbol) {
    char buffSym;
    bool win;
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        win = true;
        buffSym = symbol;
        for (unsigned int j = 0; j < this->gridSize; ++j) {
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
        buffSym = symbol;
        for (unsigned int i = 0; i < this->gridSize; ++i) {
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
    buffSym = symbol;
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        if (this->grid[i][i] != buffSym || buffSym == this->symbols.blank) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
    win = true;
    buffSym = symbol;
    for (unsigned int k = 0; k < this->gridSize; ++k) {
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
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        this->gameBranch.push_back(' ');
    }
}

void TicTacToe::setGridSize(unsigned int size) {
    this->gridSize = size;
    this->grid.setShape(std::make_pair(this->gridSize, this->gridSize));
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            grid[i][j] = this->symbols.blank;
        }
    }
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        this->gameBranch.push_back(' ');
    }
}

void TicTacToe::restart() {
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            grid[i][j] = this->symbols.blank;
        }
    }
    this->cntMoves = 0;
    this->gameBranch.clear();
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        this->gameBranch.push_back(' ');
    }
}

matrix::Matrix<char> TicTacToe::getGameGrid() {
    return this->grid;
}

unsigned int TicTacToe::getCntMoves() {
    return this->cntMoves;
}

std::string TicTacToe::getGameBranch() {
    std::string buffS;
    for (unsigned int i = 0; i < this->gameBranch.size(); ++i) {
        buffS += this->gameBranch[i];
    }
    return buffS;
}

void TicTacToe::setGameGrid(matrix::Matrix<char> mat) {
    this->gridSize = mat.shape().first;
    this->cntMoves = 0;
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            this->grid[i][j] = this->symbols.blank;
        }
    }
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        this->gameBranch.push_back(' ');
    }
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            if (mat[i][j] != this->symbols.blank) {
                this->setSymbol(i, j, mat[i][j]);
            }
        }
    }
}

TicTacToe::~TicTacToe() = default;
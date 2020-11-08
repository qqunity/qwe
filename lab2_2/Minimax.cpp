#include "Minimax.hpp"
#include <random>

std::vector<unsigned int> Minimax::getAvailSpots(matrix::Matrix<char> mat) {
    std::vector<unsigned int> buffVec;
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            if (mat[i][j] == this->symbols.blank) {
                buffVec.push_back(i * this->gridSize + j);
            }
        }
    }
    return buffVec;
}

char Minimax::getOppositeSymbol(char symbol) {
    return symbol == this->symbols.x ? this->symbols.o : this->symbols.x;
}

Minimax::Minimax(char playerSymbol, unsigned int gridSize) {
    this->gridSize = gridSize;
    this->playerSymbol = playerSymbol;
    this->game.setGridSize(gridSize);
}

int Minimax::minimax(matrix::Matrix<char> mat, char symbol) {
    this->game.restart();
    this->game.setGameGrid(mat);
    if (this->game.checkWin(this->playerSymbol)) {
        return 10;
    } else if (this->game.checkWin(this->getOppositeSymbol(this->playerSymbol))) {
        return -10;
    } else if (this->game.checkDraw()) {
        return 0;
    }
    std::vector<unsigned int> availSpots = this->getAvailSpots(mat);
    int bestScore;
    if (symbol == this->playerSymbol) {
        bestScore = - INT32_MAX;
        for (unsigned int availPos : availSpots) {
            unsigned int i = availPos / this->gridSize;
            unsigned int j = availPos % this->gridSize;
            mat[i][j] = symbol;
            int score = this->minimax(mat, this->getOppositeSymbol(symbol));
            mat[i][j] = this->symbols.blank;
            bestScore = std::max(bestScore, score);
        }
    }
    else {
        bestScore = INT32_MAX;
        for (unsigned int availPos : availSpots) {
            unsigned int i = availPos / this->gridSize;
            unsigned int j = availPos % this->gridSize;
            mat[i][j] = symbol;
            int score = this->minimax(mat, this->getOppositeSymbol(symbol));
            mat[i][j] = this->symbols.blank;
            bestScore = std::min(bestScore, score);
        }
    }
    return bestScore;
}

unsigned int Minimax::getBestMove(matrix::Matrix<char> mat) {
    std::vector<unsigned int> availSpots = this->getAvailSpots(mat);
    unsigned int move = 0;
    int bestScore = - INT32_MAX;
    for (unsigned int availPos : availSpots) {
        unsigned int i = availPos / this->gridSize;
        unsigned int j = availPos % this->gridSize;
        mat[i][j] = this->playerSymbol;
        int score = this->minimax(mat, this->getOppositeSymbol(this->playerSymbol));
        mat[i][j] = this->symbols.blank;
        if (score > bestScore) {
            bestScore = score;
            move = availPos;
        }
    }
    return move;
}

Minimax::~Minimax() = default;
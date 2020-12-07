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

int Minimax::minimax(matrix::Matrix<char> mat, char symbol, unsigned int previousPos) {
    this->game.restart();
    this->game.setGameGrid(mat);
    if (this->game.checkWin(this->playerSymbol)) {
        return 10;
    } else if (this->game.checkWin(this->getOppositeSymbol(this->playerSymbol))) {
        return -10;
    } else if (this->game.checkDraw()) {
        return 0;
    }
    std::vector<unsigned int> availSpots;
    if (this->gridSize != 3) {
        std::vector<unsigned int> rawAvailSpots = this->getAvailSpots(mat);
        std::vector<unsigned int> availSpotsByPos = this->getAvailSpotsWithConstraint(previousPos);
        for (unsigned int rawAvailSpot : rawAvailSpots) {
            if (std::find(availSpotsByPos.begin(), availSpotsByPos.end(), rawAvailSpot) != availSpotsByPos.end()) {
                availSpots.push_back(rawAvailSpot);
            }
        }
    } else {
        availSpots = this->getAvailSpots(mat);
    }
    int bestScore;
    if (symbol == this->playerSymbol) {
        bestScore = - INT32_MAX;
        for (unsigned int availPos : availSpots) {
            unsigned int i = availPos / this->gridSize;
            unsigned int j = availPos % this->gridSize;
            mat[i][j] = symbol;
            int score = this->minimax(mat, this->getOppositeSymbol(symbol), availPos);
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
            int score = this->minimax(mat, this->getOppositeSymbol(symbol), availPos);
            mat[i][j] = this->symbols.blank;
            bestScore = std::min(bestScore, score);
        }
    }
    return bestScore;
}

unsigned int Minimax::getBestMove(matrix::Matrix<char> mat, unsigned int previousPos) {
    if (this->gridSize == 3) {
        previousPos = 4;
    }
    std::vector<unsigned int> availSpots;
    if (this->gridSize != 3) {
        std::vector<unsigned int> rawAvailSpots = this->getAvailSpots(mat);

        std::vector<unsigned int> availSpotsByPos = this->getAvailSpotsWithConstraint(previousPos);
        for (unsigned int rawAvailSpot : rawAvailSpots) {
            if (std::find(availSpotsByPos.begin(), availSpotsByPos.end(), rawAvailSpot) != availSpotsByPos.end()) {
                availSpots.push_back(rawAvailSpot);
            }
        }
    } else {
        availSpots = this->getAvailSpots(mat);
    }
    unsigned int move = 0;
    int bestScore = - INT32_MAX;
    for (unsigned int availPos : availSpots) {
        unsigned int i = availPos / this->gridSize;
        unsigned int j = availPos % this->gridSize;
        mat[i][j] = this->playerSymbol;
        int score = this->minimax(mat, this->getOppositeSymbol(this->playerSymbol), availPos);
        mat[i][j] = this->symbols.blank;
        if (score > bestScore) {
            bestScore = score;
            move = availPos;
        }
    }
    return move;
}

std::vector<unsigned int> Minimax::getAvailSpots(unsigned int pos) {
    std::vector<unsigned int> availSpots;
    unsigned int i = pos / this->gridSize;
    unsigned int j = pos % this->gridSize;
    if (i == j) {
        for (unsigned int k = 0; k < this->gridSize; ++k) {
            availSpots.push_back(k * this->gridSize + k);
        }
    }
    if (i + j == this->gridSize) {
        for (unsigned int k = 0; k < this->gridSize; ++k) {
            availSpots.push_back(k * this->gridSize + this->gridSize - 1 - k);
        }
    }
    for (unsigned int k = 0; k < this->gridSize; ++k) {
        availSpots.push_back(i * this->gridSize + k);
        availSpots.push_back(k * this->gridSize + j);
    }
    return availSpots;
}

std::vector<unsigned int> Minimax::getAvailSpotsWithConstraint(unsigned int pos) {
    std::vector<unsigned int> availSpots;
    unsigned int i = pos / this->gridSize;
    unsigned int j = pos % this->gridSize;
    if (i == j) {
        for (unsigned int k = i - 1; k <= i + 1; ++k) {
            availSpots.push_back(k * this->gridSize + k);
        }
    }
    if (i + j == this->gridSize) {
            availSpots.push_back((i - 1)* this->gridSize + j + 1);
            availSpots.push_back((i + 1)* this->gridSize + j - 1);

    }
    availSpots.push_back((i - 1)* this->gridSize + j);
    availSpots.push_back((i + 1)* this->gridSize + j);
    availSpots.push_back((i)* this->gridSize + j - 1);
    availSpots.push_back((i)* this->gridSize + j + 1);
    return availSpots;
}

Minimax::~Minimax() = default;
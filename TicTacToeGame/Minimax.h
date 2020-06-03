#ifndef TICTACTOEGAME_MINIMAX_H
#define TICTACTOEGAME_MINIMAX_H

#include "Matrix.h"
#include <vector>
#include "TicTacToe.h"


class Minimax {
private:
    Symbols symbols;
    unsigned int gridSize;
    TicTacToe game;
    char playerSymbol;
public:
    Minimax(char playerSymbol, unsigned int gridSize);
    std::vector<unsigned int> getAvailSpots(Matrix<char> mat);
    char getOppositeSymbol(char symbol);
    int minimax(Matrix<char> mat, char symbol);
    unsigned int getBestMove(Matrix<char> mat);
    ~Minimax();
};


#endif

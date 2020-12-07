#ifndef LAB_2_MINIMAX_HPP
#define LAB_2_MINIMAX_HPP


#include "Matrix.hpp"
#include <vector>
#include "TicTacToe.hpp"


class Minimax {
private:
    Symbols symbols;
    unsigned int gridSize;
    TicTacToe game;
    char playerSymbol;
public:


    Minimax(char playerSymbol, unsigned int gridSize);

    std::vector<unsigned int> getAvailSpots(matrix::Matrix<char> mat);

    std::vector<unsigned int> getAvailSpots(unsigned int pos);

    std::vector<unsigned int> getAvailSpotsWithConstraint(unsigned int pos);

    char getOppositeSymbol(char symbol);

    int minimax(matrix::Matrix<char> mat, char symbol, unsigned int previousPos);

    unsigned int getBestMove(matrix::Matrix<char> mat, unsigned int previousPos);

    ~Minimax();
};


#endif

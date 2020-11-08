#ifndef LAB_2_TICTACTOE_HPP
#define LAB_2_TICTACTOE_HPP


#include "Matrix.hpp"
#include <vector>
#include "Exceptions.hpp"

struct Symbols {
    const char x = 120;
    const char o = 111;
    const char blank = 45;
};

class TicTacToe {
private:
    unsigned int gridSize;
    matrix::Matrix<char> grid;
    unsigned int cntMoves;
    Symbols symbols;
    std::vector<char> gameBranch;
public:
    TicTacToe();

    TicTacToe(unsigned int gridSize);

    void setSymbol(unsigned int i, unsigned int j, char symbol);

    bool checkFieldFullness(unsigned int i, unsigned int j);

    char getSymbol(unsigned int i, unsigned int j);

    bool checkDraw();

    bool checkWin();

    bool checkWin(char symbol);

    void setGameGrid(matrix::Matrix<char> mat);

    void printGrid();

    std::string getGameBranch();

    unsigned int getCntMoves();

    matrix::Matrix<char> getGameGrid();

    void setGridSize(unsigned int size);

    void restart();

    ~TicTacToe();
};


#endif

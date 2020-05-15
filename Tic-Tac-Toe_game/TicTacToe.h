#ifndef TIC_TAC_TOE_GAME_TICTACTOE_H
#define TIC_TAC_TOE_GAME_TICTACTOE_H

#include "Matrix.h"

struct {
    const char x = 120;
    const char o = 111;
    const  char blank = 95;
} typedef Symbols;

class TicTacToe {
private:
    unsigned int gridSize;
    Matrix<char> grid;
    unsigned int cntMoves;
    Symbols symbols;
public:
    TicTacToe();
    TicTacToe(unsigned int gridSize);
    void setSymbol(unsigned int i, unsigned int j, char symbol);
    bool checkFieldFullness(unsigned int i, unsigned int j);
    char getSymbol(unsigned int i, unsigned int j);
    bool checkDraw();
    bool checkWin();
    void printGrid();
    void setGridSize(unsigned int size);
    void restart();
    ~TicTacToe();
};


#endif

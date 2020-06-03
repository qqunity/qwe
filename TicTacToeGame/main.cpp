#include <iostream>
#include "Minimax.h"

int main() {
    TicTacToe game(3);
    Minimax minimax('x', 3);
    while (!game.checkDraw() || !game.checkWin()) {
        game.printGrid();
        unsigned int pPos;
        std::cin >> pPos;
        game.setSymbol(pPos / 3, pPos % 3, 'o');
        if (game.checkDraw()) {
            std::cout << "draw";
            break;
        }
        if (game.checkWin()) {
            std::cout << "win";
            break;
        }
        game.printGrid();
        unsigned int pos = minimax.getBestMove(game.getGameGrid());
        game.setSymbol(pos / 3, pos % 3, 'x');
    }
    return 0;
}

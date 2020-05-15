#include <iostream>
#include "TicTacToe.h"
#include "TreeX.h"
#include <string>
#include "GameIntelligence.h"

int main() {
//    TicTacToe game(3);
//    game.printGrid();
//    Symbols s;
//    game.setSymbol(0, 2, s.x);
//    game.setSymbol(1, 1, s.x);
//    game.setSymbol(2, 2, s.x);
//    std::cout << game.checkWin() << '\n';
//    game.printGrid();
//    TreeX<std::string, char> tree("0,0");
//    tree.addNode("1,0");
//    tree.addNode("1,1");
//    tree.addNode("2,0");
//    tree.addEdge("0,0", "1,1", 'x', "red");
//    tree.addEdge("0,0", "1,0", 'o', "green");
//    tree.addEdge("1,1", "2,0", 'x', "");
//    outPutFile << tree;
    std::string filePath = "/media/qunity/Workspace/CPP_projects/qwe/Tic-Tac-Toe_game/graphStruct.txt";
    GameIntelligence ai(2, 'x');
//    ai.setDecisionTree();
    ai.genTreeStruct(filePath);
    return 0;
}

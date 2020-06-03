#ifndef TICTACTOEGAME_GAMEDECISIONTREEX_H
#define TICTACTOEGAME_GAMEDECISIONTREEX_H

#include "TreeX.h"
#include "TicTacToe.h"
#include "Utils.h"

class GameDecisionTreeX {
private:
    TreeX<std::string, std::string> decisionTreeX;
    std::vector<NodeX<std::string> *> lastNodes;
    TicTacToe game;
    NodeX<std::string> *cursor;
    char startSymbol;
    char aiSymbol;
    unsigned int gridSize;
    Symbols symbols;
public:
    GameDecisionTreeX(unsigned int gridSize, char startSymbol, char aiSymbol);
    std::string convertIndexToString(unsigned int i, unsigned int j);
    std::pair<unsigned int, unsigned int> convertStringToIndex(std::string value);
    char getNextSymbol(char symbol);
    unsigned int getPosFromLabel(std::string label);
    char getSymbolFromLabel(std::string label);
    std::string convertGameMatrixToGameBranch(Matrix<char> mat);
    std::pair<unsigned int, unsigned int> convertPosToIndex(unsigned int pos);
    void genDecisionTreeX(NodeX<std::string> *pNode, char cSymbol);
    void fillDecisionTreeX();
    bool checkNodeWin(NodeX<std::string> *node);
    bool checkNodeDraw(NodeX<std::string> *node);
    NodeX<std::string> *getCursor();
    unsigned int getBestGameMove(NodeX<std::string> *node, unsigned int pos);
    std::string genLabel(std::string label, unsigned int pos);
    friend std::ofstream &operator<<(std::ofstream &fout, GameDecisionTreeX gDecTree);
    ~GameDecisionTreeX();
};


#endif

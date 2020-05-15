#ifndef TIC_TAC_TOE_GAME_GAMEINTELLIGENCE_H
#define TIC_TAC_TOE_GAME_GAMEINTELLIGENCE_H

#include "TreeX.h"
#include "TicTacToe.h"
#include <cmath>
#include <set>

class GameIntelligence {
private:
    TreeX<std::string, std::string> decisionTree;
    unsigned int gridSize;
    Symbols symbols;
    TicTacToe game;
public:
    GameIntelligence(unsigned int gridSize, char startSymbol);

    std::string getValueFromInt(unsigned int i, unsigned int j);

    void genDecisionTree(unsigned int i, unsigned int j, char symbol, std::string label,
                         std::map<std::pair<unsigned int, unsigned int>, bool> &grid);

    char getNextSymbol(char symbol);

    std::string getLabelFromInt(unsigned int i, unsigned int j);

    std::pair<unsigned int, unsigned int> getPairFromLabel(std::string label);

    void genTreeStruct(std::string filePath);

    TreeX<std::string, std::string> *getDecisionTree();

    char getSymbolFromLabel(std::string label);

    std::string getMoveFromLabel(std::string label);

    void setDecisionTree();

    void subSetDecisionTree(NodeX<std::string> *pNode);
};


#endif

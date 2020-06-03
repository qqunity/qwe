#ifndef TIC_TAC_TOE_GAME_GAMEINTELLIGENCE_H
#define TIC_TAC_TOE_GAME_GAMEINTELLIGENCE_H

#include "TreeX.h"
#include "TicTacToe.h"
#include "Utils.h"
#include <cmath>
#include <set>

struct {
    unsigned int draw = 0;
    unsigned int winX = 1;
    unsigned int win0 = 2;
} typedef GameOutcome;

class GameIntelligence {
private:
    TreeX<std::string, std::string> decisionTree;
    char startSymbol;
    unsigned int gridSize;
    Symbols symbols;
    GameOutcome gameOutcome;
    std::vector<std::string> gameBranches;
    TicTacToe game;
public:
    GameIntelligence();
    void setup(unsigned int gridSize, char startSymbol);
    GameIntelligence(unsigned int gridSize, char startSymbol);
    char getNextSymbol(char symbol, unsigned int numberOfTimes);
    std::string convertIndexToString(unsigned int i, unsigned int j);
    std::pair<unsigned int, unsigned int> convertStringToIndex(std::string value);
    std::string getLabel(unsigned int positionOnField, char symbol);
    unsigned int getPosFromLabel(std::string label);
    char getSymbolFromLabel(std::string label);
    void genDecisionTree();
    std::string convertMatrixToGameBranch(Matrix<char> mat);
    std::vector<unsigned int> getGameBranchesIndexesFromMatrix(Matrix<char> mat);
    std::vector<unsigned int> getGameBranchesIndexesFromBranch(std::string branch);
    std::vector<std::string> getGameBranches();
    char convertGameOutcomeToSymbol(unsigned int gOutcome);
    Matrix<char> convertGameTrackToMatrix(unsigned int index, unsigned int cntMoves);
    unsigned int getGameOutcome(unsigned int index);
    std::vector<std::pair<unsigned int, char>> getBestGameTrack(Matrix<char> mat, char symbol, std::string branch);
    std::vector<std::pair<unsigned int, char>> convertGameTrackToSteps(unsigned int index, unsigned int cntMoves);
    std::pair<unsigned int, unsigned int> convertPosToIndex(unsigned int pos);
    friend std::ofstream &operator<<(std::ofstream &fout, const GameIntelligence gI);
    ~GameIntelligence();
};


#endif

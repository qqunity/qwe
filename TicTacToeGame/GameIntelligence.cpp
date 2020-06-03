#include "GameIntelligence.h"

GameIntelligence::GameIntelligence(unsigned int gridSize, char startSymbol) {
    this->gridSize = gridSize;
    this->startSymbol = startSymbol;
    this->game.setGridSize(gridSize);
}

char GameIntelligence::getNextSymbol(char symbol, unsigned int numberOfTimes) {
    for (unsigned int i = 0; i < numberOfTimes; ++i) {
        symbol = symbol == this->symbols.x ? this->symbols.o : this->symbols.x;
    }
    return symbol;
}

std::string GameIntelligence::convertIndexToString(unsigned int i, unsigned int j) {
    return std::string(std::to_string(i) + "," + std::to_string(j));
}

std::pair<unsigned int, unsigned int> GameIntelligence::convertStringToIndex(std::string value) {
    unsigned int sepPos = value.find(',');
    std::string iS;
    for (unsigned int i = 0; i < sepPos; ++i) {
        iS += value[i];
    }
    std::string jS;
    for (unsigned int j = sepPos + 1; j < value.length(); ++j) {
        jS += value[j];
    }
    return std::make_pair(abs(std::stoi(iS)), abs(std::stoi(jS)));
}

std::string GameIntelligence::getLabel(unsigned int positionOnField, char symbol) {
    return std::string(std::to_string(positionOnField) + '/' + symbol);
}

unsigned int GameIntelligence::getPosFromLabel(std::string label) {
    unsigned int sepPos = label.find('/');
    std::string pos;
    for (unsigned int i = 0; i < sepPos; ++i) {
        pos += label[i];
    }
    return abs(std::stoi(pos));
}

char GameIntelligence::getSymbolFromLabel(std::string label) {
    return label[label.length() - 1];
}

void GameIntelligence::genDecisionTree() {
    this->decisionTree.setRoot("0,0");
    std::vector<unsigned int> permVec;
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        permVec.push_back(i);
    }
    unsigned int j = 0;
    do {
        this->game.restart();
        bool endGame = false;
        std::string buffBranches;
        for (unsigned int k = 0; k < this->gridSize * this->gridSize; ++k) {
            buffBranches.push_back(' ');
        }
        for (unsigned int i = 1; i <= this->gridSize * this->gridSize; ++i) {
            std::string color;
            this->decisionTree.addNode(this->convertIndexToString(i, j));
            if (i == 1) {
                buffBranches[permVec[i - 1]] = startSymbol;
                this->game.setSymbol(this->convertPosToIndex(permVec[i - 1]).first, this->convertPosToIndex(permVec[i - 1]).second, startSymbol);
                if (this->game.checkWin() && !endGame) {
                    endGame = true;
                    color = "green";
                }
                if (this->game.checkDraw() && !endGame) {
                    endGame = true;
                    color = "red";
                }
                this->decisionTree.addEdge(this->convertIndexToString(0, 0), this->convertIndexToString(i, j), this->getLabel(permVec[i - 1], startSymbol), color);
            } else {
                buffBranches[permVec[i - 1]] = this->getNextSymbol(startSymbol, i - 1);
                this->game.setSymbol(this->convertPosToIndex(permVec[i - 1]).first, this->convertPosToIndex(permVec[i - 1]).second, this->getNextSymbol(startSymbol, i - 1));
                if (this->game.checkWin() && !endGame) {
                    endGame = true;
                    color = "green";
                }
                if (this->game.checkDraw() && !endGame) {
                    endGame = true;
                    color = "red";
                }
                this->decisionTree.addEdge(this->convertIndexToString(i - 1, j), this->convertIndexToString(i, j), this->getLabel(permVec[i - 1], this->getNextSymbol(startSymbol, i - 1)), color);
            }
        }
        this->gameBranches.push_back(buffBranches);
        ++j;
    } while (std::next_permutation(permVec.begin(), permVec.end()));
}

std::ofstream &operator<<(std::ofstream &fout, const GameIntelligence gI) {
    fout << gI.decisionTree;
    return fout;
}

std::pair<unsigned int, unsigned int> GameIntelligence::convertPosToIndex(unsigned int pos) {
    return std::make_pair(pos / this->gridSize, pos % this->gridSize);
}

Matrix<char> GameIntelligence::convertGameTrackToMatrix(unsigned int index, unsigned int cntMoves) {
    Matrix<char> mat(this->gridSize, this->gridSize);
    for (unsigned int i = 0; i < this->gridSize; ++i) {
        for (unsigned int j = 0; j < this->gridSize; ++j) {
            mat[i][j] = this->symbols.blank;
        }
    }
    for (auto node: this->decisionTree.getRoot()->getlinksToChildren()) {
        if (this->convertStringToIndex(node.first).second == index) {
            unsigned int pos = this->getPosFromLabel(this->decisionTree.getLabel(this->decisionTree.getRoot()->getValue(), node.second->getValue()));
            char symbol = this->getSymbolFromLabel(this->decisionTree.getLabel(this->decisionTree.getRoot()->getValue(), node.second->getValue()));
            mat[this->convertPosToIndex(pos).first][this->convertPosToIndex(pos).second] = symbol;
            NodeX<std::string> *buffNode = node.second;
            for (unsigned int i = 0; i < this->gridSize * this->gridSize - 1; ++i) {
                unsigned int iNode = this->convertStringToIndex(buffNode->getValue()).first;
                unsigned int jNode = this->convertStringToIndex(buffNode->getValue()).second;
                std::string buffNodeVal = buffNode->getValue();
                buffNode = buffNode->getChild(this->convertIndexToString(iNode + 1, jNode));
                pos = this->getPosFromLabel(this->decisionTree.getLabel(buffNodeVal, buffNode->getValue()));
                symbol = this->getSymbolFromLabel(this->decisionTree.getLabel(buffNodeVal, buffNode->getValue()));
                std::string color = this->decisionTree.getColor(buffNodeVal, buffNode->getValue());
                mat[this->convertPosToIndex(pos).first][this->convertPosToIndex(pos).second] = symbol;
                if (color != "" || i == cntMoves - 2) {
                    break;
                }
            }
        }
    }
    return mat;
}

std::vector<std::pair<unsigned int, char>> GameIntelligence::convertGameTrackToSteps(unsigned int index, unsigned int cntMoves) {
    std::vector<std::pair<unsigned int, char>> stepsVec;
    for (auto node: this->decisionTree.getRoot()->getlinksToChildren()) {
        if (this->convertStringToIndex(node.first).second == index) {
            unsigned int pos = this->getPosFromLabel(this->decisionTree.getLabel(this->decisionTree.getRoot()->getValue(), node.second->getValue()));
            char symbol = this->getSymbolFromLabel(this->decisionTree.getLabel(this->decisionTree.getRoot()->getValue(), node.second->getValue()));
            stepsVec.push_back(std::make_pair(pos, symbol));
            NodeX<std::string> *buffNode = node.second;
            for (unsigned int i = 0; i < this->gridSize * this->gridSize - 1; ++i) {
                unsigned int iNode = this->convertStringToIndex(buffNode->getValue()).first;
                unsigned int jNode = this->convertStringToIndex(buffNode->getValue()).second;
                std::string buffNodeVal = buffNode->getValue();
                buffNode = buffNode->getChild(this->convertIndexToString(iNode + 1, jNode));
                pos = this->getPosFromLabel(this->decisionTree.getLabel(buffNodeVal, buffNode->getValue()));
                symbol = this->getSymbolFromLabel(this->decisionTree.getLabel(buffNodeVal, buffNode->getValue()));
                stepsVec.push_back(std::make_pair(pos, symbol));
                if (i == cntMoves - 2) {
                    break;
                }
            }
        }
    }
    return stepsVec;
}

unsigned int GameIntelligence::getGameOutcome(unsigned int index) {
    std::string color;
    for (auto node: this->decisionTree.getRoot()->getlinksToChildren()) {
        if (this->convertStringToIndex(node.first).second == index) {
            NodeX<std::string> *buffNode = node.second;
            for (unsigned int i = 0; i < this->gridSize * this->gridSize - 1; ++i) {
                unsigned int iNode = this->convertStringToIndex(buffNode->getValue()).first;
                unsigned int jNode = this->convertStringToIndex(buffNode->getValue()).second;
                std::string buffNodeVal = buffNode->getValue();
                buffNode = buffNode->getChild(this->convertIndexToString(iNode + 1, jNode));
                char symbol = this->getSymbolFromLabel(this->decisionTree.getLabel(buffNodeVal, buffNode->getValue()));
                color = this->decisionTree.getColor(buffNodeVal, buffNode->getValue());
                if (color != "") {
                    if (color == "red") {
                        return this->gameOutcome.draw;
                    }
                    else {
                        if (symbol == this->symbols.x) {
                            return this->gameOutcome.winX;
                        }
                        else {
                            return this->gameOutcome.win0;
                        }
                    }
                    break;
                }
            }
        }
    }
}

std::vector<std::pair<unsigned int, char>> GameIntelligence::getBestGameTrack(Matrix<char> mat, char symbol, std::string branch) {
    unsigned int cntMoves = 0;
    for (unsigned int i = 0; i < mat.shape().first; ++i) {
        for (unsigned int j = 0; j < mat.shape().second; ++j) {
            if (mat[i][j] != this->symbols.blank) {
                ++cntMoves;
            }
        }
    }
    for (unsigned int i : this->getGameBranchesIndexesFromBranch(branch)) {
        if (this->convertGameTrackToMatrix(i, cntMoves) == mat){
            if (this->convertGameOutcomeToSymbol(this->getGameOutcome(i)) == symbol) {
                return this->convertGameTrackToSteps(i, this->gridSize * this->gridSize);
            }
        }
    }
    for (unsigned int i : this->getGameBranchesIndexesFromBranch(branch)) {
        if (this->convertGameTrackToMatrix(i, cntMoves) == mat){
            if (this->convertGameOutcomeToSymbol(this->getGameOutcome(i)) == ' ') {
                return this->convertGameTrackToSteps(i, this->gridSize * this->gridSize);
            }
        }
    }
}

char GameIntelligence::convertGameOutcomeToSymbol(unsigned int gOutcome) {
    if (gOutcome == this->gameOutcome.win0) {
        return this->symbols.o;
    }
    else if (gOutcome == this->gameOutcome.winX) {
        return this->symbols.x;
    }
    else {
        return ' ';
    }
}

GameIntelligence::GameIntelligence() {
    this->gridSize = 0;
    this->startSymbol = ' ';
}

void GameIntelligence::setup(unsigned int gridSize, char startSymbol) {
    this->gridSize = gridSize;
    this->startSymbol = startSymbol;
    this->game.setGridSize(gridSize);
}

std::vector<std::string> GameIntelligence::getGameBranches() {
    return this->gameBranches;
}

std::string GameIntelligence::convertMatrixToGameBranch(Matrix<char> mat) {
    std::string buffS;
    for (unsigned int i = 0; i < mat.shape().first; ++i) {
        for (unsigned int j = 0; j < mat.shape().second; ++j) {
            if (mat[i][j] != this->symbols.blank) {
                buffS += mat[i][j];
            }
        }
    }
    return buffS;
}

std::vector<unsigned int> GameIntelligence::getGameBranchesIndexesFromMatrix(Matrix<char> mat) {
    std::string matBranch = this->convertMatrixToGameBranch(mat);
    std::vector<unsigned int> indexes;
    for (unsigned int i = 0; i < this->gameBranches.size(); ++i) {
        if (this->gameBranches[i] == matBranch) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

std::vector<unsigned int> GameIntelligence::getGameBranchesIndexesFromBranch(std::string branch) {
    std::vector<unsigned int> indexes;
    for (unsigned int i = 0; i < this->gameBranches.size(); ++i) {
        bool satisfy = true;
        for (unsigned int j = 0; j < branch.length(); ++j) {
            if (branch[j] != ' ') {
                if (branch[j] != this->gameBranches[i][j]) {
                    satisfy = false;
                    break;
                }
            }
        }
        if (satisfy) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

GameIntelligence::~GameIntelligence() = default;



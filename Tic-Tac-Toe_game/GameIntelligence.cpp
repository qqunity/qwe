//
// Created by qunity on 15.05.2020.
//

#include "GameIntelligence.h"

GameIntelligence::GameIntelligence(unsigned int gridSize, char startSymbol) {
    this->decisionTree.setRoot(this->getValueFromInt(0, 0));
    this->gridSize = gridSize * gridSize;
    this->game.setGridSize(gridSize);
    std::map<std::pair<unsigned int, unsigned int>, bool> grid;
    for (unsigned int i = 0; i < gridSize; ++i) {
        for (unsigned int j = 0; j < gridSize; ++j) {
            grid[std::make_pair(i, j)] = false;
        }
    }
    this->genDecisionTree(0, 0, startSymbol, "root", grid);
}

std::string GameIntelligence::getValueFromInt(unsigned int i, unsigned int j) {
    return std::string(std::to_string(i) + "," + std::to_string(j));
}

void GameIntelligence::genDecisionTree(unsigned int i, unsigned int j, char symbol, std::string label,
                                       std::map<std::pair<unsigned int, unsigned int>, bool> &grid) {
    if (i == 0 && j == 0) {
        this->decisionTree.setRoot(this->getValueFromInt(0, 0));
        std::map<std::pair<unsigned int, unsigned int>, bool> s_grid;
        for (unsigned int k = 0; k < sqrt(this->gridSize); ++k) {
            for (unsigned int t = 0; t < sqrt(this->gridSize); ++t) {
                s_grid[std::make_pair(k, t)] = false;
            }
        }
        for (unsigned int k = 0; k < this->gridSize - i; ++k) {
            for (std::pair<std::pair<unsigned int, unsigned int>, bool> p: s_grid) {
                if (!p.second) {
                    label = this->getLabelFromInt(p.first.first, p.first.second);
                    break;
                }
            }
            s_grid[this->getPairFromLabel(label)] = true;
            this->decisionTree.addNode(this->getValueFromInt(i + 1, k + j * (this->gridSize - i)));
            this->decisionTree.addEdge(this->getValueFromInt(i, j),
                                       this->getValueFromInt(i + 1, k + j * (this->gridSize - i)), symbol + label, "");
            grid[this->getPairFromLabel(label)] = true;
            this->genDecisionTree(i + 1, k + j * (this->gridSize - i), this->getNextSymbol(symbol), label, grid);
            grid[this->getPairFromLabel(label)] = false;
        }
    } else if (i == this->gridSize - 2) {
        this->decisionTree.addNode(this->getValueFromInt(i + 1, j));
        for (std::pair<std::pair<unsigned int, unsigned int>, bool> p: grid) {
            if (!p.second) {
                label = this->getLabelFromInt(p.first.first, p.first.second);
                break;
            }
        }
        grid[this->getPairFromLabel(label)] = true;
        this->decisionTree.addEdge(this->getValueFromInt(i, j), this->getValueFromInt(i + 1, j), symbol + label, "");
        this->genDecisionTree(i + 1, j, this->getNextSymbol(symbol), label, grid);
        grid[this->getPairFromLabel(label)] = false;
    } else if (i == this->gridSize - 1) {
        this->decisionTree.addNode(this->getValueFromInt(i + 1, j));
        for (std::pair<std::pair<unsigned int, unsigned int>, bool> p: grid) {
            if (!p.second) {
                label = this->getLabelFromInt(p.first.first, p.first.second);
                break;
            }
        }
        this->decisionTree.addEdge(this->getValueFromInt(i, j), this->getValueFromInt(i + 1, j), symbol + label, "");
    } else {
        for (unsigned int k = 0; k < this->gridSize - i; ++k) {
            this->decisionTree.addNode(this->getValueFromInt(i + 1, k + (j * (this->gridSize - i))));
            for (std::pair<std::pair<unsigned int, unsigned int>, bool> p: grid) {
                if (!p.second) {
                    label = this->getLabelFromInt(p.first.first, p.first.second);
                    break;
                }
            }
            grid[this->getPairFromLabel(label)] = true;
            this->decisionTree.addEdge(this->getValueFromInt(i, j),
                                       this->getValueFromInt(i + 1, k + (j * (this->gridSize - i))), symbol + label,
                                       "");
            this->genDecisionTree(i + 1, k + (j * (this->gridSize - i)), this->getNextSymbol(symbol), label, grid);
            grid[this->getPairFromLabel(label)] = false;
        }
    }
}

char GameIntelligence::getNextSymbol(char symbol) {
    return (symbol == this->symbols.x) ? this->symbols.o : this->symbols.x;
}

void GameIntelligence::genTreeStruct(std::string filePath) {
    std::ofstream outPutFile;
    outPutFile.open(filePath);
    outPutFile << this->decisionTree;
}

TreeX<std::string, std::string> *GameIntelligence::getDecisionTree() {
    return &this->decisionTree;
}

std::string GameIntelligence::getLabelFromInt(unsigned int i, unsigned int j) {
    return std::string("|" + std::to_string(i) + "/" + std::to_string(j));
}

std::pair<unsigned int, unsigned int> GameIntelligence::getPairFromLabel(std::string label) {
    unsigned int pos1 = label.find('|');
    std::string buffS1;
    std::string buffS2;
    unsigned int pos2 = label.find('/');
    for (unsigned int i = pos1 + 1; i < pos2; ++i) {
        buffS1 += label[i];
    }
    for (unsigned int j = pos2 + 1; j < label.length(); ++j) {
        buffS2 += label[j];
    }
    return std::make_pair(abs(std::stoi(buffS1)), abs(std::stoi(buffS2)));
}

char GameIntelligence::getSymbolFromLabel(std::string label) {
    return label[0];
}

std::string GameIntelligence::getMoveFromLabel(std::string label) {
    std::string buffS;
    unsigned int pos = label.find('|');
    for (unsigned int i = pos + 1; i < label.length(); ++i) {
        buffS += label[i];
    }
    return buffS;
}

void GameIntelligence::setDecisionTree() {
    this->game.restart();
    this->subSetDecisionTree(this->decisionTree.getRoot());
}

void GameIntelligence::subSetDecisionTree(NodeX<std::string> *pNode) {
    if ()
}

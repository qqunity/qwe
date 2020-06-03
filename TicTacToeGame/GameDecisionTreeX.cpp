#include "GameDecisionTreeX.h"

GameDecisionTreeX::GameDecisionTreeX(unsigned int gridSize, char startSymbol, char aiSymbol) {
    this->gridSize = gridSize;
    this->startSymbol = startSymbol;
    this->aiSymbol = aiSymbol;
    this->decisionTreeX.setRoot("0,0");
    this->game.setGridSize(gridSize);
    this->genDecisionTreeX(this->decisionTreeX.getRoot(), startSymbol);
    this->fillDecisionTreeX();
    this->cursor = this->decisionTreeX.getRoot();
}

void GameDecisionTreeX::genDecisionTreeX(NodeX<std::string> *pNode, char cSymbol) {
    std::string symbol;
    symbol += cSymbol;
    unsigned int pI = this->convertStringToIndex(pNode->getValue()).first;
    unsigned int pJ = this->convertStringToIndex(pNode->getValue()).second;
    for (unsigned int j = 0; j < this->gridSize * this->gridSize - pI; ++j) {
        if (pI == this->gridSize * this->gridSize - 1) {
            auto cNode = this->decisionTreeX.addNode(this->convertIndexToString(pI + 1, pJ));
            this->decisionTreeX.addEdge(this->convertIndexToString(pI, pJ), this->convertIndexToString(pI + 1, pJ), symbol, "");
            this->decisionTreeX.addEdge(this->convertIndexToString(pI + 1, pJ), this->convertIndexToString(pI, pJ), symbol, "");
            this->lastNodes.push_back(cNode);
        } else{
            auto cNode = this->decisionTreeX.addNode(this->convertIndexToString(pI + 1, j + pJ * (this->gridSize * this->gridSize - pI)));
            this->decisionTreeX.addEdge(this->convertIndexToString(pI, pJ), this->convertIndexToString(pI + 1, j + pJ * (this->gridSize * this->gridSize - pI)), symbol, "");
            this->decisionTreeX.addEdge(this->convertIndexToString(pI + 1, j + pJ * (this->gridSize * this->gridSize - pI)), this->convertIndexToString(pI, pJ), symbol, "");
            this->genDecisionTreeX(cNode, this->getNextSymbol(cSymbol));
        }
    }
}

std::string GameDecisionTreeX::convertIndexToString(unsigned int i, unsigned int j) {
    return std::string(std::to_string(i) + "," + std::to_string(j));
}

std::pair<unsigned int, unsigned int> GameDecisionTreeX::convertStringToIndex(std::string value) {
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

char GameDecisionTreeX::getNextSymbol(char symbol) {
    return symbol == this->symbols.x ? this->symbols.o : this->symbols.x;
}

std::ofstream &operator<<(std::ofstream &fout, GameDecisionTreeX gDecTree) {
    fout << gDecTree.decisionTreeX;
    return fout;
}
std::string color;
void GameDecisionTreeX::fillDecisionTreeX() {
    std::vector<unsigned int> permVec;
    for (unsigned int i = 0; i < this->gridSize * this->gridSize; ++i) {
        permVec.push_back(i);
    }
    unsigned int i = 0;
    do {
        auto node = this->lastNodes[i];
        this->game.restart();
        char symbol = this->getNextSymbol(this->startSymbol);
        unsigned int gamePos = 0;
        color = "";
        for (unsigned int k : permVec) {
            this->game.setSymbol(this->convertPosToIndex(k).first, this->convertPosToIndex(k).second, this->getNextSymbol(symbol));
            if (this->game.checkWin()) {
                gamePos = k;
                color = "green";
                break;
            } else if (this->game.checkDraw()) {
                gamePos = k;
                color = "red";
                break;
            }
            symbol = this->getNextSymbol(symbol);
        }
        if (color.empty()) {
            gamePos = permVec[permVec.size() - 1];
            color = "red";
        }
        unsigned int j = this->gridSize * this->gridSize - 1;
        while (node->getValue() != this->decisionTreeX.getRoot()->getValue()) {
            for (auto pNode : node->getlinksToChildren()) {
                if (this->convertStringToIndex(pNode.first).first < this->convertStringToIndex(node->getValue()).first) {
                    if (this->decisionTreeX.getLabel(pNode.first, node->getValue()).length() == 1) {
                        this->decisionTreeX.setLabel(pNode.first, node->getValue(), this->genLabel(
                                this->decisionTreeX.getLabel(pNode.first, node->getValue()), permVec[j]));
                        if (permVec[j] == gamePos) {
                            this->decisionTreeX.setColor(pNode.first, node->getValue(), color);
                        }
                    }
                    node = pNode.second;
                    break;
                }
            }
            --j;
        }
        ++i;
        this->game.restart();
    } while (std::next_permutation(permVec.begin(), permVec.end()));
    for (i = 0; i < factorial(this->gridSize * this->gridSize); ++i) {
        auto node = this->lastNodes[i];
        unsigned int j = 0;
        while (node->getValue() != this->decisionTreeX.getRoot()->getValue() && j < this->gridSize * this->gridSize) {
            for (auto pNode : node->getlinksToChildren()) {
                if (this->convertStringToIndex(pNode.first).first < this->convertStringToIndex(node->getValue()).first) {
                    this->decisionTreeX.delEdge(node->getValue(), pNode.first);
                    node = pNode.second;
                    break;
                }
            }
            ++j;
        }
    }
}

std::string GameDecisionTreeX::genLabel(std::string label, unsigned int pos) {
    return std::string(label + "/" + std::to_string(pos));
}

std::pair<unsigned int, unsigned int> GameDecisionTreeX::convertPosToIndex(unsigned int pos) {
    return std::make_pair(pos / this->gridSize, pos % this->gridSize);
}

unsigned int GameDecisionTreeX::getPosFromLabel(std::string label) {
    unsigned int sepPos = label.find('/');
    std::string pos;
    for (unsigned int i = sepPos + 1; i < label.length(); ++i) {
        pos += label[i];
    }
    return abs(std::stoi(pos));
}

char GameDecisionTreeX::getSymbolFromLabel(std::string label) {
    return label[0];
}

std::string GameDecisionTreeX::convertGameMatrixToGameBranch(Matrix<char> mat) {
    std::string buffS;
    for (unsigned int i = 0; i < mat.shape().first; ++i) {
        for (unsigned int j = 0; j < mat.shape().second; ++j) {
            if (mat[i][j] != this->symbols.blank) {
                buffS += mat[i][j];
            }
            else {
                buffS += ' ';
            }
        }
    }
    return buffS;
}

unsigned int GameDecisionTreeX::getBestGameMove(NodeX<std::string> *node, unsigned int pos) {
    std::cout << "\ncursor:" << node->getValue() << '\n';
    for (auto cNode: node->getlinksToChildren()) {
        if (this->getPosFromLabel(this->decisionTreeX.getLabel(node->getValue(), cNode.first)) == pos){
            node = cNode.second;
            break;
        }
    }
    for (auto cNode: node->getlinksToChildren()) {
        if (this->checkNodeWin(cNode.second) && this->checkNodeDraw(cNode.second)) {
            this->cursor = cNode.second;
            std::cout << "\ncursor:" << this->cursor->getValue() << '\n';
            return this->getPosFromLabel(this->decisionTreeX.getLabel(node->getValue(), cNode.first));
        }
    }
    for (auto cNode: node->getlinksToChildren()) {
        if (this->checkNodeDraw(cNode.second)) {
            this->cursor = cNode.second;
            std::cout << "\ncursor:" << this->cursor->getValue() << '\n';
            return this->getPosFromLabel(this->decisionTreeX.getLabel(node->getValue(), cNode.first));
        }
    }
    for (auto cNode: node->getlinksToChildren()) {
        this->cursor = cNode.second;
        std::cout << "\ncursor:" << this->cursor->getValue() << '\n';
        return this->getPosFromLabel(this->decisionTreeX.getLabel(node->getValue(), cNode.first));
    }
}


bool GameDecisionTreeX::checkNodeWin(NodeX<std::string> *node) {
    if (this->convertStringToIndex(node->getValue()).first != this->gridSize * this->gridSize) {
        unsigned int cI = this->convertStringToIndex(node->getValue()).first + 1;
        for (unsigned int j = 0; j < this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first; ++j) {
            unsigned int cJ = j + this->convertStringToIndex(node->getValue()).second * (this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first);
            if (this->decisionTreeX.getColor(node->getValue(), this->convertIndexToString(cI, cJ)) == "green" && this->getSymbolFromLabel(
                    this->decisionTreeX.getLabel(node->getValue(), this->convertIndexToString(cI, cJ))) == this->aiSymbol) {
                return true;
            }
        }
        for (unsigned int j = 0; j < this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first; ++j) {
            unsigned int cJ = j + this->convertStringToIndex(node->getValue()).second * (this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first);
            return this->checkNodeWin(this->decisionTreeX.getNode(this->convertIndexToString(cI, cJ)));
        }
    } else {
        return false;
    }
}

bool GameDecisionTreeX::checkNodeDraw(NodeX<std::string> *node) {
    if (this->convertStringToIndex(node->getValue()).first != this->gridSize * this->gridSize) {
        unsigned int cI = this->convertStringToIndex(node->getValue()).first + 1;
        for (unsigned int j = 0; j < this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first; ++j) {
            unsigned int cJ = j + this->convertStringToIndex(node->getValue()).second * (this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first);
            if (this->decisionTreeX.getColor(node->getValue(), this->convertIndexToString(cI, cJ)) == "red" && this->getSymbolFromLabel(
                    this->decisionTreeX.getLabel(node->getValue(), this->convertIndexToString(cI, cJ))) == this->aiSymbol) {
                return true;
            }
        }
        for (unsigned int j = 0; j < this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first; ++j) {
            unsigned int cJ = j + this->convertStringToIndex(node->getValue()).second * (this->gridSize * this->gridSize - this->convertStringToIndex(node->getValue()).first);
            return this->checkNodeDraw(this->decisionTreeX.getNode(this->convertIndexToString(cI, cJ)));
        }
    } else {
        return false;
    }
}

NodeX<std::string> *GameDecisionTreeX::getCursor() {
    return this->cursor;
}

GameDecisionTreeX::~GameDecisionTreeX() = default;

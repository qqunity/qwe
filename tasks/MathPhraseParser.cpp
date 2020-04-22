#include "MathPhraseParser.h"

void MathPhraseParser::firstStageParser() {
    bool outOfBrackets = false;
    while (!outOfBrackets) {
        bool flag = false;
        int i = 0;
        while (i < this->phrase.length()) {
            if (this->phrase[i] == '(') {
                flag = true;
                while (this->phrase[i] == '(') {
                    ++i;
                }
                std::string buffS = "";
                int j = i;
                while (this->phrase[j] != ')') {
                    buffS.push_back(this->phrase[j]);
                    if (this->phrase[j] == '(') {
                        buffS = "";
                        i = j + 1;
                    }
                    ++j;
                }
                int pos = i - 1;
                int cnt = j - i + 2;
                std::string buffPhrase;
                buffPhrase = this->phrase;
                this->phrase = buffS;
//                std::cout << "Do" << std::endl << this->phrase << std::endl;
                firstStageParser();
                secondStageParser();
                thirdStageParser();
//                std::cout << "Posle" << std::endl << this->phrase << std::endl;
                buffPhrase.replace(pos, cnt, this->phrase);
                this->phrase = buffPhrase;
            } else {
                ++i;
            }
        }
        if (!flag) {
            outOfBrackets = true;
        }
    }
}

MathPhraseParser::MathPhraseParser(std::string phrase) {
    this->phrase = phrase;
}

void MathPhraseParser::parse() {
    firstStageParser();
//    std::cout << this->phrase << std::endl;
    secondStageParser();
//    std::cout << this->phrase << std::endl;
    thirdStageParser();
//    std::cout << this->phrase << std::endl;
    this->phrase.erase(0, 1);
    this->phrase.erase(this->phrase.length() - 1, 1);
    this->headIndex = std::stoi(this->phrase);
}

void MathPhraseParser::secondStageParser() {
    int i = 0;
    std::string sign;
    while (i < this->phrase.length()) {
        if (this->phrase[i] == '*' || this->phrase[i] == '/') {
            sign = this->phrase[i];
            int j = i - 1;
            std::string numS1;
            while (this->phrase[j] != '*' && this->phrase[j] != '/' && this->phrase[j] != '+' && this->phrase[j] != '-' && j >= 0) {
                numS1.push_back(this->phrase[j]);
                --j;
            }
            int pos = j + 1;
            std::reverse(numS1.begin(), numS1.end());
            j = i + 1;
            std::string numS2;
            while (this->phrase[j] != '*' && this->phrase[j] != '/' && this->phrase[j] != '+' && this->phrase[j] != '-') {
                numS2.push_back(this->phrase[j]);
                ++j;
            }
            this->phrase.erase(pos, j - pos);
            this->phrase.insert(pos, "[" + std::to_string(this->subTrees.size()) + "]");
            auto signNode = new TreeNode();
            signNode->setSign(sign);
            if (numS1[0] != '[') {
                auto num1Node = new TreeNode();
                float num1 = std::stof(numS1);
                num1Node->setNumber(num1);
                signNode->setLeftNodePtr(num1Node);
            }
            else {
                numS1.erase(0,1);
                numS1.erase(numS1.length() - 1, 1);
                int index = std::stoi(numS1);
                signNode->setLeftNodePtr(this->subTrees[index]);
            }
            if (numS2[0] != '[') {
                auto num2Node = new TreeNode();
                float num2 = std::stof(numS2);
                num2Node->setNumber(num2);
                signNode->setRightNodePtr(num2Node);
            }
            else {
                numS2.erase(0,1);
                numS2.erase(numS2.length() - 1, 1);
                int index = std::stoi(numS2);
                signNode->setRightNodePtr(this->subTrees[index]);
            }
            this->subTrees.push_back(signNode);
        }
        else {
            ++i;
        }
    }
}

void MathPhraseParser::thirdStageParser() {
    int i = 0;
    std::string sign;
    while (i < this->phrase.length()) {
        if (this->phrase[i] == '-' || this->phrase[i] == '+') {
            sign = this->phrase[i];
            int j = i - 1;
            std::string numS1;
            while (this->phrase[j] != '+' && this->phrase[j] != '-' && j >= 0) {
                numS1.push_back(this->phrase[j]);
                --j;
            }
            int pos = j + 1;
            std::reverse(numS1.begin(), numS1.end());
            j = i + 1;
            std::string numS2;
            while (this->phrase[j] != '*' && this->phrase[j] != '/' && this->phrase[j] != '+' && this->phrase[j] != '-') {
                numS2.push_back(this->phrase[j]);
                ++j;
            }
            this->phrase.erase(pos, j - pos);
            this->phrase.insert(pos, "[" + std::to_string(this->subTrees.size()) + "]");
            auto signNode = new TreeNode();
            signNode->setSign(sign);
            if (numS1[0] != '[') {
                auto num1Node = new TreeNode();
                float num1 = std::stof(numS1);
                num1Node->setNumber(num1);
                signNode->setLeftNodePtr(num1Node);
            }
            else {
                numS1.erase(0,1);
                numS1.erase(numS1.length() - 1, 1);
                int index = std::stoi(numS1);
                signNode->setLeftNodePtr(this->subTrees[index]);
            }
            if (numS2[0] != '[') {
                auto num2Node = new TreeNode();
                float num2 = std::stof(numS2);
                num2Node->setNumber(num2);
                signNode->setRightNodePtr(num2Node);
            }
            else {
                numS2.erase(0,1);
                numS2.erase(numS2.length() - 1, 1);
                int index = std::stoi(numS2);
                signNode->setRightNodePtr(this->subTrees[index]);
            }
            this->subTrees.push_back(signNode);
        }
        else {
            ++i;
        }
    }
}

void MathPhraseParser::printPhraseTree() {
    std::cout << *this->subTrees[headIndex];
}

void MathPhraseParser::calculate() {
    this->answer =  subCalculate(this->subTrees[headIndex]);
}

float MathPhraseParser::subCalculate(TreeNode *node) {
    if (node->isSign()) {
        if (node->getSign() == "-") {
            return subCalculate(node->getLeftNodePtr()) - subCalculate(node->getRightNodePtr());
        }
        else if (node->getSign() == "+") {
            return subCalculate(node->getLeftNodePtr()) + subCalculate(node->getRightNodePtr());
        }
        else if (node->getSign() == "*") {
            return subCalculate(node->getLeftNodePtr()) * subCalculate(node->getRightNodePtr());
        }
        else if (node->getSign() == "/") {
            return subCalculate(node->getLeftNodePtr()) / subCalculate(node->getRightNodePtr());
        }
    } else {
        return node->getNumber();
    }
}

float MathPhraseParser::getAnswer() {
    return this->answer;
}

MathPhraseParser::~MathPhraseParser() = default;

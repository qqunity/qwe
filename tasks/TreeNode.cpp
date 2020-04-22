#include "TreeNode.h"
#include "Exceptions.h"

TreeNode::TreeNode() {
    this->leftNodePtr = nullptr;
    this->rightNodePtr = nullptr;
    this->_isNumber = false;
    this->_isSign = false;
}

void TreeNode::setNumber(float number) {
    if (!this->_isSign){
        this->number = number;
        this->_isNumber = true;
    }
    else {
        throw TreeNodeException("Error | Line: " + std::to_string(__LINE__) + " | File: " + __FILE__ + " | Description: " + "This node is sign!");
    }
}

float TreeNode::getNumber() {
    if (this->_isNumber){
        return this->number;
    }
    else {
        throw TreeNodeException("Error | Line: " + std::to_string(__LINE__) + " | File: " + __FILE__ + " | Description: " + "This node isn't number!");
    }
}

void TreeNode::setSign(std::string sign) {
    if (!this->_isNumber) {
        this->sign = sign;
        this->_isSign = true;
    }
    else {
        throw TreeNodeException("Error | Line: " + std::to_string(__LINE__) + " | File: " + __FILE__ + " | Description: " + "This node is number!");
    }
}

std::string TreeNode::getSign() {
    if (this->_isSign) {
        return sign;
    }
    else {
        throw TreeNodeException("Error | Line: " + std::to_string(__LINE__) + " | File: " + __FILE__ + " | Description: " + "This node isn't sign!");
    }
}

void TreeNode::setLeftNodePtr(TreeNode *ptr) {
    this->leftNodePtr = ptr;
}

void TreeNode::setRightNodePtr(TreeNode *ptr) {
    this->rightNodePtr = ptr;
}

TreeNode *TreeNode::getLeftNodePtr() {
    return this->leftNodePtr;
}

TreeNode *TreeNode::getRightNodePtr() {
    return this->rightNodePtr;
}

std::ostream &operator<<(std::ostream &out, const TreeNode &tNode) {
    if (tNode._isSign) {
        out << tNode.sign << std::endl;
        out << "/ \\" << std::endl;
        out << *tNode.leftNodePtr << " " << *tNode.rightNodePtr << std::endl;
    }
    else {
        out << tNode.number << " ";
    }
    return out;
}

bool TreeNode::isSign() {
    return this->_isSign;
}

bool TreeNode::isNumber() {
    return this->_isNumber;
}

TreeNode::~TreeNode() = default;

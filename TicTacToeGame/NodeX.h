#ifndef TIC_TAC_TOE_GAME_NODEX_H
#define TIC_TAC_TOE_GAME_NODEX_H

#include <map>
#include "Optional.h"

template<typename T>
class NodeX {
private:
    Optional<T> value;
    std::map<T, NodeX<T> *> linksToChildren;
    unsigned int cntChildren;
public:
    NodeX();

    NodeX(T val);

    NodeX(const NodeX<T> &node);

    void addChild(NodeX<T> *pNode);

    NodeX<T> *getChild(T val);

    void setChild(T val, NodeX<T> *pNode);

    void setValue(T val);

    T getValue();

    operator T();

    NodeX<T> &operator=(NodeX<T> &node);

    NodeX<T> &operator=(T val);

    NodeX<T> *operator[](T val);

    void delChild(T val);

    unsigned int getCntChildren();

    std::map<T, NodeX<T> *> getlinksToChildren();

    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, const NodeX<T1> &node);
};

template<typename T>
NodeX<T>::NodeX() {
    this->cntChildren = 0;
}

template<typename T>
NodeX<T>::NodeX(T val) {
    this->value = val;
    this->cntChildren = 0;
}

template<typename T>
NodeX<T>::NodeX(const NodeX<T> &node) {
    this->value = node.value;
    this->cntChildren = node.cntChildren;
    this->linksToChildren = node.linksToChildren;
}

template<typename T>
void NodeX<T>::addChild(NodeX<T> *pNode) {
    this->linksToChildren[pNode->getValue()] = pNode;
    ++this->cntChildren;
}

template<typename T>
NodeX<T> *NodeX<T>::getChild(T val) {
    return this->linksToChildren[val];
}

template<typename T>
void NodeX<T>::setChild(T val, NodeX<T> *pNode) {
    if (val == pNode->getValue()) {
        this->linksToChildren[val] = pNode;
    } else {
        throw Exception("You can not change value of node!", __LINE__, __FILE__);
    }
}

template<typename T>
void NodeX<T>::setValue(T val) {
    this->value = val;
}

template<typename T>
T NodeX<T>::getValue() {
    return this->value;
}

template<typename T>
NodeX<T> &NodeX<T>::operator=(NodeX<T> &node) {
    if (this == &node) {
        return *this;
    }
    this->value = node.value;
    this->linksToChildren = node.linksToChildren;
    this->cntChildren = node.cntChildren;
}

template<typename T>
void NodeX<T>::delChild(T val) {
    auto child = this->linksToChildren.find(val);
    this->linksToChildren.erase(child);
    --this->cntChildren;
}

template<typename T>
unsigned int NodeX<T>::getCntChildren() {
    return this->cntChildren;
}

template<typename T>
NodeX<T> &NodeX<T>::operator=(T val) {
    this->value = val;
    return *this;
}

template<typename T>
NodeX<T> *NodeX<T>::operator[](T val) {
    return this->getChild(val);
}

template<typename T1>
std::ostream &operator<<(std::ostream &out, const NodeX<T1> &node) {
    out << "----------\n";
    if (node.cntChildren != 0) {
        out << "Node: " << node.value << '\n' << "Children: ";
        for (std::pair<T1, NodeX<T1> *> p: node.linksToChildren) {
            out << p.second->getValue() << " ";
        }
    } else {
        out << "Node: " << node.value;
    }
    out << "\n----------\n";
    for (std::pair<T1, NodeX<T1> *> p: node.linksToChildren) {
        out << *p.second;
    }
    return out;
}

template<typename T>
NodeX<T>::operator T() {
    return this->value;
}

template<typename T>
std::map<T, NodeX<T> *> NodeX<T>::getlinksToChildren() {
    return this->linksToChildren;
}

#endif

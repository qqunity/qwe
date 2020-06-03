#ifndef TIC_TAC_TOE_GAME_TREEX_H
#define TIC_TAC_TOE_GAME_TREEX_H

#include <fstream>
#include "NodeX.h"
#include <map>
#include <vector>
#include <queue>
#include <typeinfo>

template<typename T, typename L>
class TreeX {
private:
    NodeX<T> *root;
    unsigned int cntNodes;
    std::map<std::pair<T, T>, L> labels;
    std::map<std::pair<T, T>, std::string> colors;
    std::map<T, NodeX<T> *> nodes;
public:
    TreeX();

    TreeX(T val);

    TreeX(NodeX<T> *pNode);

    void setRoot(NodeX<T> *pNode);

    void setRoot(T val);

    NodeX<T> *getRoot();

    NodeX<T> *addNode(T val);

    NodeX<T> *getNode(T val);

    void setNode(T val, NodeX<T> *pNode);

    void setLabel(T val1, T val2, L label);

    void setColor(T val1, T val2, std::string color);

    L getLabel(T val1, T val2);

    std::string getColor(T val1, T val2);

    void delNode(T val);

    void inOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data);

    void preOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data);

    void breadthOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data);

    void addEdge(T val1, T val2, L label, std::string color);

    void delEdge(T val1, T val2);

    template<typename T1, typename L1>
    friend std::ostream &operator<<(std::ostream &out, const TreeX<T1, L1> tree);

    template<typename T1, typename L1>
    friend std::ofstream &operator<<(std::ofstream &fout, const TreeX<T1, L1> tree);
};

template<typename T, typename L>
TreeX<T, L>::TreeX(NodeX<T> *pNode) {
    this->cntNode = 0;
    this->root = pNode;
}

template<typename T, typename L>
void TreeX<T, L>::setRoot(NodeX<T> *pNode) {
    this->root = pNode;
}

template<typename T, typename L>
NodeX<T> *TreeX<T, L>::addNode(T val) {
    auto pNode = new NodeX<T>(val);
    this->nodes[val] = pNode;
    ++this->cntNodes;
    return pNode;
}

template<typename T, typename L>
void TreeX<T, L>::setNode(T val, NodeX<T> *pNode) {
    if (val == pNode->getValue()) {
        this->nodes[val] = pNode;
    } else {
        throw Exception("You can not change value of node!", __LINE__, __FILE__);
    }
}

template<typename T, typename L>
void TreeX<T, L>::delNode(T val) {
    auto node = this->nodes.find(val);
    this->nodes.erase(node);
    --this->cntNodes;
}

template<typename T, typename L>
void TreeX<T, L>::addEdge(T val1, T val2, L label, std::string color) {
    this->labels[std::make_pair(val1, val2)] = label;
    this->colors[std::make_pair(val1, val2)] = color;
    if (val1 == this->root->getValue()) {
        this->root->addChild(this->nodes[val2]);
    } else {
        if (val2 == this->root->getValue()) {
            this->nodes[val1]->addChild(this->root);
        } else {
            this->nodes[val1]->addChild(this->nodes[val2]);
        }
    }
}

template<typename T, typename L>
void TreeX<T, L>::delEdge(T val1, T val2) {
    if (val1 == this->root->getValue()) {
        this->root->delChild(val2);
    } else {
        this->nodes[val1]->delChild(val2);
    }
    auto color = this->colors.find(std::make_pair(val1, val2));
    auto label = this->labels.find(std::make_pair(val1, val2));
    this->colors.erase(color);
    this->labels.erase(label);
}

template<typename T1, typename L1>
std::ostream &operator<<(std::ostream &out, const TreeX<T1, L1> tree) {
    out << *tree.root;
    return out;
}

template<typename T, typename L>
TreeX<T, L>::TreeX(T val) {
    this->root = new NodeX<T>(val);
    this->cntNodes = 0;
}

template<typename T, typename L>
void TreeX<T, L>::setLabel(T val1, T val2, L label) {
    this->labels[std::make_pair(val1, val2)] = label;
}

template<typename T1, typename L1>
std::ofstream &operator<<(std::ofstream &fout, const TreeX<T1, L1> tree) {
    std::vector<std::string> buffStrs;
    for (std::pair<std::pair<T1, T1>, L1> label: tree.labels) {
        buffStrs.push_back(label.first.first + "-" + label.first.second + ":" + label.second + ":");
    }
    unsigned int i = 0;
    for (std::pair<std::pair<T1, T1>, std::string> color: tree.colors) {
        buffStrs[i] += color.second;
        ++i;
    }
    for (std::string s: buffStrs) {
        fout << s << '\n';
    }
    return fout;
}

template<typename T, typename L>
void TreeX<T, L>::setRoot(T val) {
    this->root = new NodeX<T>(val);
    this->cntNodes = 0;
}

template<typename T, typename L>
TreeX<T, L>::TreeX() {
    this->root = nullptr;
    this->cntNodes = 0;
}

template<typename T, typename L>
void TreeX<T, L>::inOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data) {
    for (std::pair<T, NodeX<T> *> child: pNode->getlinksToChildren()) {
        this->inOrder(child.second, data);
    }
    data.push_back(pNode);
}

template<typename T, typename L>
NodeX<T> *TreeX<T, L>::getRoot() {
    return this->root;
}

template<typename T, typename L>
void TreeX<T, L>::preOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data) {
    data.push_back(pNode);
    for (std::pair<T, NodeX<T> *> child: pNode->getlinksToChildren()) {
        this->preOrder(child.second, data);
    }
}

template<typename T, typename L>
void TreeX<T, L>::breadthOrder(NodeX<T> *pNode, std::vector<NodeX<T> *> &data) {
    std::queue<NodeX<T> *> q;
    q.push(pNode);
    while (!q.empty()) {
        NodeX<T> *tmpNode = q.front();
        data.push_back(tmpNode);
        for (std::pair<T, NodeX<T> *> child: tmpNode->getlinksToChildren()) {
            q.push(child.second);
        }
        q.pop();
    }
}

template<typename T, typename L>
L TreeX<T, L>::getLabel(T val1, T val2) {
    return this->labels[std::make_pair(val1, val2)];
}

template<typename T, typename L>
void TreeX<T, L>::setColor(T val1, T val2, std::string color) {
    this->colors[std::make_pair(val1, val2)] = color;
}

template<typename T, typename L>
std::string TreeX<T, L>::getColor(T val1, T val2) {
    return this->colors[std::make_pair(val1, val2)];
}

template<typename T, typename L>
NodeX<T> *TreeX<T, L>::getNode(T val) {
    return this->nodes[val];
}


#endif
#ifndef LAB_2_BTREE_HPP
#define LAB_2_BTREE_HPP

#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "Exceptions.hpp"
#include <string>
#include <iostream>

namespace tree {
    template<typename T>
    struct BNode {
        sequence::Sequence<T> *keys;
        sequence::Sequence<BNode<T> *> *childrenPointers;
        BNode<T> *parentPtr;
        unsigned int keysQuantity;
        unsigned int childrenQuantity;
        bool isLeaf;
    };

    template<typename T>
    class BTree {
    private:
        BNode<T> *rootPtr;
        unsigned int t{};
        std::string sequenceType;
        T defaultKey;

    protected:

        void deleteNode(BNode<T> *node);

        void sort(BNode<T> *node);

        void insertToNode(T key, BNode<T> *node);

        void restructuring(BNode<T> *node);

        void printSubTreeRecurrently(BNode<T> *node);

        T &searchKey(T key, BNode<T> *node);

        void removeFromNode(T key, BNode<T> *node);

        void leftConnection(BNode<T> *node, BNode<T> *otherNode);

        void repair(BNode<T> *node);

        void removeFromLeaf(T key, BNode<T> *node);

        void remove(T key, BNode<T> *node);

    public:
        BTree(unsigned int t, const std::string& sequenceType, T defaultKey);

        void insert(T key);

        void printTree();

        T &search(T key);

        void remove(T key);

        ~BTree();
    };

    template<typename T>
    BTree<T>::BTree(unsigned int t, const std::string& sequenceType, T defaultKey) {
        this->t = t;
        this->defaultKey = defaultKey;
        this->rootPtr = nullptr;
        if (sequenceType != "ArraySequence" && sequenceType != "LinkedListSequence") {
            throw exceptions::BTreeException("Invalid sequence type", __LINE__, __FILE__);
        } else {
            this->sequenceType = sequenceType;
        }
    }

    template<typename T>
    void BTree<T>::deleteNode(BNode<T> *node) {
        if (node != nullptr) {
            for (unsigned int i = 0; i <= (2 * this->t - 1); ++i) {
                if ((*node->childrenPointers)[i]->getValue() != nullptr) {
                    this->deleteNode((*node->childrenPointers)[i]->getValue());
                } else {
                    delete node;
                    break;
                }
            }
        }
    }

    template<typename T>
    BTree<T>::~BTree() {
        if (this->rootPtr != nullptr) {
            this->deleteNode(this->rootPtr);
        }
    }

    template<typename T>
    void BTree<T>::sort(BNode<T> *node) {
        T buff;
        for (unsigned int i = 0; i < (2 * this->t - 1); ++i) {
            for (unsigned int j = i + 1; j <= 2 * this->t - 1; ++j) {
                if (((*node->keys)[i]->getValue() != this->defaultKey) &&
                    ((*node->keys)[j]->getValue() != this->defaultKey)) {
                    if ((*node->keys)[i]->getValue() > (*node->keys)[j]->getValue()) {
                        buff = (*node->keys)[i]->getValue();
                        (*node->keys)[i]->setValue((*node->keys)[j]->getValue());
                        (*node->keys)[j]->setValue(buff);
                    }
                } else {
                    break;
                }
            }
        }
    }

    template<typename T>
    void BTree<T>::insertToNode(T key, BNode<T> *node) {
        node->keys->insert(node->keysQuantity, key);
        ++node->keysQuantity;
        this->sort(node);
    }

    template<typename T>
    void BTree<T>::insert(T key) {
        if (this->rootPtr == nullptr) {
            auto *newRootPtr = new BNode<T>;
            if (this->sequenceType == "ArraySequence") {
                newRootPtr->keys = new array::ArraySequence<T>();
                newRootPtr->childrenPointers = new array::ArraySequence<BNode<T> *>();
            } else {
                newRootPtr->keys = new list::LinkedListSequence<T>();
                newRootPtr->childrenPointers = new list::LinkedListSequence<BNode<T> *>();
            }
            for (unsigned int i = 0; i < 2 * this->t; ++i) {
                newRootPtr->keys->append(this->defaultKey);
            }
            for (unsigned int i = 0; i < 2 * this->t + 1; ++i) {
                newRootPtr->childrenPointers->append(nullptr);
            }
            (*newRootPtr->keys)[0]->setValue(key);
            for (unsigned int j = 1; j <= (2 * this->t - 1); ++j) {
                (*newRootPtr->keys)[j]->setValue(this->defaultKey);
            }
            for (unsigned int i = 0; i < (2 * this->t); ++i) {
                (*newRootPtr->childrenPointers)[i]->setValue(nullptr);
            }
            newRootPtr->keysQuantity = 1;
            newRootPtr->childrenQuantity = 0;
            newRootPtr->isLeaf = true;
            newRootPtr->parentPtr = nullptr;
            this->rootPtr = newRootPtr;
        } else {
            BNode<T> *ptr = this->rootPtr;
            while (!ptr->isLeaf) {
                for (unsigned int i = 0; i <= (2 * this->t - 1); ++i) {
                    if ((*ptr->keys)[i]->getValue() != this->defaultKey) {
                        if (key < (*ptr->keys)[i]->getValue()) {
                            ptr = (*ptr->childrenPointers)[i]->getValue();
                            break;
                        }
                        if ((*ptr->keys)[i + 1]->getValue() == this->defaultKey && key > (*ptr->keys)[i]->getValue()) {
                            ptr = (*ptr->childrenPointers)[i + 1]->getValue();
                            break;
                        }
                    } else {
                        break;
                    }
                }
            }
            this->insertToNode(key, ptr);
            while (ptr->keysQuantity == 2 * this->t) {
                if (ptr == this->rootPtr) {
                    this->restructuring(ptr);
                    break;
                } else {
                    this->restructuring(ptr);
                    ptr = ptr->parentPtr;
                }
            }
        }
    }

    template<typename T>
    void BTree<T>::restructuring(BNode<T> *node) {
        if (node->keysQuantity < (2 * this->t - 1)) {
            return;
        }
        auto *child1 = new BNode<T>;
        if (this->sequenceType == "ArraySequence") {
            child1->keys = new array::ArraySequence<T>();
            child1->childrenPointers = new array::ArraySequence<BNode<T> *>();
        } else {
            child1->keys = new list::LinkedListSequence<T>();
            child1->childrenPointers = new list::LinkedListSequence<BNode<T> *>();
        }
        for (unsigned int i = 0; i < 2 * this->t; ++i) {
            child1->keys->append(this->defaultKey);
        }
        for (unsigned int i = 0; i < 2 * this->t + 1; ++i) {
            child1->childrenPointers->append(nullptr);
        }
        for (unsigned int j = 0; j <= this->t - 2; ++j) {
            (*child1->keys)[j]->setValue((*node->keys)[j]->getValue());
        }
        for (unsigned int j = this->t - 1; j <= 2 * this->t - 1; ++j) {
            (*child1->keys)[j]->setValue(this->defaultKey);
        }
        child1->keysQuantity = this->t - 1;
        if (node->childrenQuantity != 0) {
            for (unsigned int i = 0; i <= this->t - 1; ++i) {
                (*child1->childrenPointers)[i]->setValue((*node->childrenPointers)[i]->getValue());
                (*child1->childrenPointers)[i]->getValue()->parentPtr = child1;
            }
            for (unsigned int i = this->t; i <= 2 * this->t; ++i) {
                (*child1->childrenPointers)[i]->setValue(nullptr);
            }
            child1->isLeaf = false;
            child1->childrenQuantity = this->t - 1;
        } else {
            child1->isLeaf = true;
            child1->childrenQuantity = 0;
            for (unsigned int i = 0; i <= 2 * this->t; ++i) {
                (*child1->childrenPointers)[i]->setValue(nullptr);
            }
        }

        auto *child2 = new BNode<T>;
        if (this->sequenceType == "ArraySequence") {
            child2->keys = new array::ArraySequence<T>();
            child2->childrenPointers = new array::ArraySequence<BNode<T> *>();
        } else {
            child2->keys = new list::LinkedListSequence<T>();
            child2->childrenPointers = new list::LinkedListSequence<BNode<T> *>();
        }
        for (unsigned int i = 0; i < 2 * this->t; ++i) {
            child2->keys->append(this->defaultKey);
        }
        for (unsigned int i = 0; i < 2 * this->t + 1; ++i) {
            child2->childrenPointers->append(nullptr);
        }
        for (unsigned int j = 0; j <= this->t - 1; ++j) {
            (*child2->keys)[j]->setValue((*node->keys)[j + this->t]->getValue());
        }
        for (unsigned int j = this->t; j <= 2 * this->t - 1; ++j) {
            (*child2->keys)[j]->setValue(this->defaultKey);
        }
        child2->keysQuantity = this->t;
        if (node->childrenQuantity != 0) {
            for (unsigned int i = 0; i <= this->t; ++i) {
                (*child2->childrenPointers)[i]->setValue((*node->childrenPointers)[i + this->t]->getValue());
                (*child2->childrenPointers)[i]->getValue()->parentPtr = child2;
            }
            for (unsigned int i = this->t + 1; i <= 2 * this->t; ++i) {
                (*child2->childrenPointers)[i]->setValue(nullptr);
            }
            child2->isLeaf = false;
            child2->childrenQuantity = this->t;
        } else {
            child2->isLeaf = true;
            child2->childrenQuantity = 0;
            for (unsigned int i = 0; i <= 2 * this->t; ++i) {
                (*child2->childrenPointers)[i]->setValue(nullptr);
            }
        }

        if (node->parentPtr == nullptr) {
            (*node->keys)[0]->setValue((*node->keys)[this->t - 1]->getValue());
            for (unsigned int j = 1; j < 2 * this->t - 1; ++j) {
                (*node->keys)[j]->setValue(this->defaultKey);
            }
            (*node->childrenPointers)[0]->setValue(child1);
            (*node->childrenPointers)[1]->setValue(child2);
            for (unsigned int i = 2; i < (2 * this->t); ++i) {
                (*node->childrenPointers)[i]->setValue(nullptr);
            }
            node->parentPtr = nullptr;
            node->isLeaf = false;
            node->keysQuantity = 1;
            node->childrenQuantity = 2;
            child1->parentPtr = node;
            child2->parentPtr = node;
        } else {
            this->insertToNode((*node->keys)[this->t - 1]->getValue(), node->parentPtr);
            for (unsigned int i = 0; i <= 2 * this->t; ++i) {
                if ((*node->parentPtr->childrenPointers)[i]->getValue() == node) {
                    (*node->parentPtr->childrenPointers)[i]->setValue(nullptr);
                }
            }
            for (unsigned int i = 0; i < 2 * this->t; ++i) {
                if ((*node->parentPtr->childrenPointers)[i]->getValue() == nullptr) {
                    for (unsigned int j = 2 * this->t; j > i + 1; --j) {
                        (*node->parentPtr->childrenPointers)[j]->setValue(
                                (*node->parentPtr->childrenPointers)[j - 1]->getValue());
                    }
                    (*node->parentPtr->childrenPointers)[i + 1]->setValue(child2);
                    (*node->parentPtr->childrenPointers)[i]->setValue(child1);
                    break;
                }
            }
            child1->parentPtr = node->parentPtr;
            child2->parentPtr = node->parentPtr;
            node->parentPtr->isLeaf = false;
            delete node;
        }
    }

    template<typename T>
    void BTree<T>::printSubTreeRecurrently(BNode<T> *node) {
        if (node != nullptr) {
            if (node->parentPtr == nullptr) {
                std::cout << "root\n";
            }
            std::cout << "\nkeys: \n";
            for (unsigned int i = 0; i < node->keysQuantity; ++i) {
                std::cout << (*node->keys)[i]->getValue() << " ";
            }
            std::cout << "\n";
            for (unsigned int i = 0; i < 2 * this->t + 1; ++i) {
                if (i < node->childrenPointers->length() && (*node->childrenPointers)[i]->checkValue()) {
                    this->printSubTreeRecurrently((*node->childrenPointers)[i]->getValue());
                }
            }
        }
    }

    template<typename T>
    void BTree<T>::printTree() {
        this->printSubTreeRecurrently(this->rootPtr);
    }

    template<typename T>
    T &BTree<T>::searchKey(T key, BNode<T> *node) {
        if (node != nullptr) {
            if (!node->isLeaf) {
                unsigned int i;
                for (i = 0; i <= 2 * this->t - 1; ++i) {
                    if ((*node->keys)[i]->getValue() != this->defaultKey) {
                        if (key == (*node->keys)[i]->getValue()) {
                            return (*node->keys)[i]->getValue();
                        }
                        if (key < (*node->keys)[i]->getValue()) {
                            return this->searchKey(key, (*node->childrenPointers)[i]->getValue());
                        }
                    } else {
                        break;
                    }
                }
                return this->searchKey(key, (*node->childrenPointers)[i]->getValue());
            } else {
                for (unsigned int j = 0; j <= (2 * this->t - 1); ++j) {
                    if (key == (*node->keys)[j]->getValue()) {
                        return (*node->keys)[j]->getValue();
                    }
                }
                return this->defaultKey;
            }
        } else {
            return this->defaultKey;
        }
    }

    template<typename T>
    T &BTree<T>::search(T key) {
        return this->searchKey(key, this->rootPtr);
    }

    template<typename T>
    void BTree<T>::removeFromNode(T key, BNode<T> *node) {
        for (unsigned int i = 0; i < node->keysQuantity; ++i) {
            if ((*node->keys)[i]->getValue() == key) {
                for (unsigned int j = i; j < node->keysQuantity; ++j) {
                    (*node->keys)[j]->setValue((*node->keys)[j + 1]->getValue());
                    (*node->childrenPointers)[j]->setValue((*node->childrenPointers)[j + 1]->getValue());
                }
                (*node->keys)[node->keysQuantity - 1]->setValue(this->defaultKey);
                (*node->childrenPointers)[node->keysQuantity - 1]->setValue(
                        (*node->childrenPointers)[node->keysQuantity]->getValue());
                (*node->childrenPointers)[node->keysQuantity]->setValue(nullptr);
                break;
            }
        }
        --node->keysQuantity;
    }

    template<typename T>
    void BTree<T>::leftConnection(BNode<T> *node, BNode<T> *otherNode) {
        if (node == nullptr) {
            return;
        }
        if (node->childrenQuantity == 0) {
            for (unsigned int i = 0; i < 2 * this->t + 1; ++i) {
                node->childrenPointers->append(nullptr);
            }
        }
        if (otherNode->keysQuantity != 0) {
            for (unsigned int i = 0; i <= otherNode->keysQuantity - 1; ++i) {
                node->keys->insert(node->keysQuantity, (*otherNode->keys)[i]->getValue());
                (*node->childrenPointers)[node->keysQuantity]->setValue((*otherNode->childrenPointers)[i]->getValue());
                ++node->keysQuantity;
            }
        }
        (*node->childrenPointers)[node->keysQuantity]->setValue(
                (*otherNode->childrenPointers)[otherNode->keysQuantity]->getValue());
        for (unsigned int j = 0; j <= node->keysQuantity; ++j) {
            if ((*node->childrenPointers)[j]->getValue() == nullptr) {
                break;
            }
            (*node->childrenPointers)[j]->getValue()->parentPtr = node;
        }
        delete otherNode;
    }

    template<typename T>
    void BTree<T>::repair(BNode<T> *node) {
        if (node == this->rootPtr && node->keysQuantity == 0) {
            if ((*this->rootPtr->childrenPointers)[0]->getValue() != nullptr) {
                (*this->rootPtr->childrenPointers)[0]->getValue()->parentPtr = nullptr;
                this->rootPtr = (*this->rootPtr->childrenPointers)[0]->getValue();
            } else {
                delete this->rootPtr;
            }
            return;
        }
        BNode<T> *ptr = node;
        unsigned int positionSon;
        BNode<T> *parent = ptr->parentPtr;
        for (unsigned int j = 0; j <= parent->keysQuantity; ++j) {
            if ((*parent->childrenPointers)[j]->getValue() == ptr) {
                positionSon = j;
                break;
            }
        }
        if (positionSon == 0) {
            this->insertToNode((*parent->keys)[positionSon]->getValue(), ptr);
            this->leftConnection(ptr, (*parent->childrenPointers)[positionSon + 1]->getValue());
            (*parent->childrenPointers)[positionSon + 1]->setValue(ptr);
            (*parent->childrenPointers)[positionSon]->setValue(nullptr);
            this->removeFromNode((*parent->keys)[positionSon]->getValue(), parent);
            if (ptr->keysQuantity == 2 * this->t) {
                while (ptr->keysQuantity == 2 * this->t) {
                    if (ptr == this->rootPtr) {
                        this->restructuring(ptr);
                        break;
                    } else {
                        this->restructuring(ptr);
                        ptr = ptr->parentPtr;
                    }
                }
            } else {
                if (parent->keysQuantity <= this->t - 2) {
                    this->repair(parent);
                }
            }
        } else {
            if (positionSon == parent->keysQuantity) {
                this->insertToNode((*parent->keys)[positionSon - 1]->getValue(),
                                   (*parent->childrenPointers)[positionSon - 1]->getValue());
                this->leftConnection((*parent->childrenPointers)[positionSon - 1]->getValue(), ptr);
                (*parent->childrenPointers)[positionSon]->setValue(
                        (*parent->childrenPointers)[positionSon - 1]->getValue());
                (*parent->childrenPointers)[positionSon - 1]->setValue(nullptr);
                this->removeFromNode((*parent->keys)[positionSon - 1]->getValue(), parent);
                BNode<T> *temp = (*parent->childrenPointers)[positionSon]->getValue();
                if (ptr->keysQuantity == 2 * this->t) {
                    while (temp->keysQuantity == 2 * this->t) {
                        if (temp == this->rootPtr) {
                            this->restructuring(temp);
                            break;
                        } else {
                            this->restructuring(temp);
                            temp = temp->parentPtr;
                        }
                    }
                } else {
                    if (parent->childrenQuantity <= this->t - 2) {
                        this->repair(parent);
                    }
                }
            } else {
                this->insertToNode((*parent->keys)[positionSon]->getValue(), ptr);
                this->leftConnection(ptr, (*parent->childrenPointers)[positionSon + 1]->getValue());
                (*parent->childrenPointers)[positionSon + 1]->setValue(ptr);
                (*parent->childrenPointers)[positionSon]->setValue(nullptr);
                this->removeFromNode((*parent->keys)[positionSon]->getValue(), parent);
                if (ptr->keysQuantity == 2 * this->t) {
                    while (ptr->keysQuantity == 2 * this->t) {
                        if (ptr == this->rootPtr) {
                            this->restructuring(ptr);
                            break;
                        } else {
                            this->restructuring(ptr);
                            ptr = ptr->parentPtr;
                        }
                    }
                } else {
                    if (parent->keysQuantity <= this->t - 2) {
                        this->repair(parent);
                    }
                }
            }
        }
    }

    template<typename T>
    void BTree<T>::removeFromLeaf(T key, BNode<T> *node) {
        if (node == this->rootPtr && node->keysQuantity == 1) {
            this->removeFromNode(key, node);
            (*this->rootPtr->childrenPointers)[0]->setValue(nullptr);
            delete this->rootPtr;
            this->rootPtr = nullptr;
            return;
        }
        if (node == this->rootPtr) {
            this->removeFromNode(key, node);
            return;
        }
        if (node->keysQuantity > this->t - 1) {
            this->removeFromNode(key, node);
            return;
        }
        BNode<T> *ptr = node;
        T k1;
        T k2;
        unsigned int positionSon = 0;
        BNode<T> *parent = ptr->parentPtr;
        for (unsigned int j = 0; j < parent->keysQuantity; ++j) {
            if ((*parent->childrenPointers)[j]->getValue() == ptr) {
                positionSon = j;
                break;
            }
        }
        if (positionSon == 0) {
            if ((*parent->childrenPointers)[positionSon + 1]->getValue()->keysQuantity > this->t - 1) {
                k1 = (*((*parent->childrenPointers)[positionSon + 1]->getValue())->keys)[0]->getValue();
                k2 = (*parent->keys)[positionSon]->getValue();
                this->insertToNode(k2, ptr);
                this->removeFromNode(key, ptr);
                (*parent->keys)[positionSon]->setValue(k1);
                this->removeFromNode(k1, (*parent->childrenPointers)[positionSon + 1]->getValue());
            } else {
                this->removeFromNode(key, ptr);
                if (ptr->keysQuantity <= this->t - 2) {
                    this->repair(ptr);
                }
            }
        } else {
            if (positionSon == parent->keysQuantity) {
                if ((*parent->childrenPointers)[positionSon - 1]->getValue()->keysQuantity > this->t - 1) {
                    BNode<T> *temp = (*parent->childrenPointers)[positionSon - 1]->getValue();
                    k1 = (*temp->keys)[temp->keysQuantity - 1]->getValue();
                    k2 = (*parent->keys)[positionSon - 1]->getValue();
                    this->insertToNode(k2, ptr);
                    this->removeFromNode(key, ptr);
                    (*parent->keys)[positionSon - 1]->setValue(k1);
                    this->removeFromNode(k1, temp);
                } else {
                    this->removeFromNode(key, ptr);
                    if (ptr->keysQuantity <= this->t - 2) {
                        this->repair(ptr);
                    }
                }
            } else {
                if ((*parent->childrenPointers)[positionSon - 1]->getValue()->keysQuantity > this->t - 1) {
                    BNode<T> *temp = (*parent->childrenPointers)[positionSon - 1]->getValue();
                    k1 = (*temp->keys)[temp->keysQuantity - 1]->getValue();
                    k2 = (*parent->keys)[positionSon - 1]->getValue();
                    this->insertToNode(k2, ptr);
                    this->removeFromNode(key, ptr);
                    (*parent->keys)[positionSon - 1]->setValue(k1);
                    this->removeFromNode(k1, temp);
                } else {
                    this->removeFromNode(key, ptr);
                    if (ptr->keysQuantity <= this->t - 2) {
                        this->repair(ptr);
                    }
                }
            }
        }
    }

    template<typename T>
    void BTree<T>::remove(T key, BNode<T> *node) {
        BNode<T> *ptr = node;
        unsigned int position;
        for (unsigned int i = 0; i <= node->keysQuantity - 1; ++i) {
            if (key == (*node->keys)[i]->getValue()) {
                position = i;
                break;
            }
        }
        if (ptr->parentPtr != nullptr) {
            for (unsigned int i = 0; i <= ptr->parentPtr->keysQuantity; ++i) {
                if ((*ptr->childrenPointers)[i]->getValue() == ptr) {
                    break;
                }
            }
        }

        ptr = (*ptr->childrenPointers)[position + 1]->getValue();
        T newKey = (*ptr->keys)[0]->getValue();
        while (!ptr->isLeaf) {
            ptr = (*ptr->childrenPointers)[0]->getValue();
        }
        if (ptr->childrenQuantity > this->t - 1) {
            newKey = (*ptr->keys)[0]->getValue();
            this->removeFromNode(newKey, ptr);
            (*node->keys)[position]->setValue(newKey);
        } else {
            ptr = node;
            ptr = (*ptr->childrenPointers)[position]->getValue();
            newKey = (*ptr->keys)[ptr->keysQuantity - 1]->getValue();
            while (!ptr->isLeaf) {
                ptr = (*ptr->childrenPointers)[ptr->childrenQuantity]->getValue();
            }
            (*node->keys)[position]->setValue(newKey);
            if (ptr->keysQuantity > this->t - 1) {
                this->removeFromNode(newKey, ptr);
            } else {
                this->removeFromLeaf(newKey, ptr);
            }
        }
    }

    template<typename T>
    void BTree<T>::remove(T key) {
        BNode<T> *ptr = this->rootPtr;
        int i;
        if (this->searchKey(key, ptr) == this->defaultKey) {
            return;
        } else {
            for (i = 0; i <= ptr->keysQuantity - 1; ++i) {
                if ((*ptr->keys)[i]->getValue() != this->defaultKey) {
                    if (key == (*ptr->keys)[i]->getValue()) {
                        break;
                    } else {
                        if (key < (*ptr->keys)[i]->getValue()) {
                            ptr = (*ptr->childrenPointers)[i]->getValue();
                            i = -1;
                        } else {
                            if (i == ptr->keysQuantity - 1) {
                                ptr = (*ptr->childrenPointers)[i + 1]->getValue();
                                i = -1;
                            }
                        }
                    }
                } else {
                    break;
                }
            }
            if (ptr->isLeaf) {
                if (ptr->keysQuantity > this->t - 1) {
                    this->removeFromNode(key, ptr);
                } else {
                    this->removeFromLeaf(key, ptr);
                }
            } else {
                this->remove(key, ptr);
            }
        }
    }
}

#endif

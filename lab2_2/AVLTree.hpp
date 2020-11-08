#ifndef LAB_2_AVLTREE_HPP
#define LAB_2_AVLTREE_HPP

#include <iostream>

namespace tree {
    template<typename T>
    struct Node {
        T key;
        unsigned int height{};
        Node<T> *leftPtr;
        Node<T> *rightPtr;

        Node<T>(T key);
    };

    template<typename T>
    Node<T>::Node(T key) {
        this->key = key;
        this->leftPtr = nullptr;
        this->rightPtr = nullptr;
        this->height = 1;
    }

    template<typename T>
    class AVLTree {
    private:
        Node<T> *rootPtr;
        T defaultKey;
    protected:
        unsigned int height(Node<T> *node);

        int bfactor(Node<T> *node);

        void fixHeight(Node<T> *node);

        Node<T> *rotateRight(Node<T> *node);

        Node<T> *rotateLeft(Node<T> *node);

        Node<T> *balance(Node<T> *node);

        Node<T> *insert(Node<T> *node, T key);

        void printSubTreeRecurrently(Node<T> *node);

        void removeSubTree(Node<T> *node);

        Node<T> *findMin(Node<T> *node);

        Node<T> *removeMin(Node<T> *node);

        Node<T> *remove(Node<T> *node, T key);

        T &find(Node<T> *node, T key);

    public:
        AVLTree(T defaultKey);

        void insert(T key);

        void printTree();

        void remove(T key);

        T &search(T key);

        ~AVLTree();
    };

    template<typename T>
    unsigned int AVLTree<T>::height(Node<T> *node) {
        return node != nullptr ? node->height : 0;
    }

    template<typename T>
    int AVLTree<T>::bfactor(Node<T> *node) {
        return this->height(node->rightPtr) - this->height(node->leftPtr);
    }

    template<typename T>
    void AVLTree<T>::fixHeight(Node<T> *node) {
        unsigned int hl = this->height(node->leftPtr);
        unsigned int hr = this->height(node->rightPtr);
        node->height = (hl > hr ? hl : hr) + 1;
    }

    template<typename T>
    Node<T> *AVLTree<T>::rotateRight(Node<T> *node) {
        Node<T> *newNode = node->leftPtr;
        node->leftPtr = newNode->rightPtr;
        newNode->rightPtr = node;
        this->fixHeight(node);
        this->fixHeight(newNode);
        return newNode;
    }

    template<typename T>
    Node<T> *AVLTree<T>::rotateLeft(Node<T> *node) {
        Node<T> *newNode = node->rightPtr;
        node->rightPtr = newNode->leftPtr;
        newNode->leftPtr = node;
        this->fixHeight(node);
        this->fixHeight(newNode);
        return newNode;
    }

    template<typename T>
    Node<T> *AVLTree<T>::balance(Node<T> *node) {
        this->fixHeight(node);
        if (this->bfactor(node) == 2) {
            if (this->bfactor(node->rightPtr) < 0) {
                node->rightPtr = this->rotateRight(node->rightPtr);
            }
            return this->rotateLeft(node);
        }
        if (this->bfactor(node) == -2) {
            if (this->bfactor(node->leftPtr) > 0) {
                node->leftPtr = this->rotateLeft(node->leftPtr);
            }
            return this->rotateRight(node);
        }
        return node;
    }

    template<typename T>
    Node<T> *AVLTree<T>::insert(Node<T> *node, T key) {
        if (node == nullptr) {
            return new Node<T>(key);
        }
        if (key < node->key) {
            node->leftPtr = this->insert(node->leftPtr, key);
        } else {
            node->rightPtr = this->insert(node->rightPtr, key);
        }
        return this->balance(node);
    }

    template<typename T>
    AVLTree<T>::AVLTree(T defaultKey) {
        this->defaultKey = defaultKey;
        this->rootPtr = nullptr;
    }

    template<typename T>
    void AVLTree<T>::printSubTreeRecurrently(Node<T> *node) {
        if (node != nullptr) {
            std::cout << "  " << node->key << '\n';
            if (node->leftPtr != nullptr) {
                std::cout << "/\t\\ \n";
                std::cout << node->leftPtr->key;
            }
            if (node->rightPtr != nullptr) {
                std::cout << '\t' << node->rightPtr->key;
            }
            std::cout << '\n';
            this->printSubTreeRecurrently(node->leftPtr);
            this->printSubTreeRecurrently(node->rightPtr);
        }
    }

    template<typename T>
    AVLTree<T>::~AVLTree() {
        this->removeSubTree(this->rootPtr);
    }

    template<typename T>
    void AVLTree<T>::removeSubTree(Node<T> *node) {
        if (node != nullptr) {
            this->removeSubTree(node->leftPtr);
            this->removeSubTree(node->rightPtr);
            delete node;
        }
    }

    template<typename T>
    void AVLTree<T>::insert(T key) {
        this->rootPtr = this->insert(this->rootPtr, key);
    }

    template<typename T>
    void AVLTree<T>::printTree() {
        this->printSubTreeRecurrently(this->rootPtr);
    }

    template<typename T>
    Node<T> *AVLTree<T>::findMin(Node<T> *node) {
        return node->leftPtr != nullptr ? this->findMin(node->leftPtr) : node;
    }

    template<typename T>
    Node<T> *AVLTree<T>::removeMin(Node<T> *node) {
        if (node->leftPtr == nullptr) {
            return node->rightPtr;
        }
        node->leftPtr = this->removeMin(node->leftPtr);
        return this->balance(node);
    }

    template<typename T>
    Node<T> *AVLTree<T>::remove(Node<T> *node, T key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->leftPtr = this->remove(node->leftPtr, key);
        } else if (key > node->key) {
            node->rightPtr = this->remove(node->rightPtr, key);
        } else {
            Node<T> *q = node->leftPtr;
            Node<T> *r = node->rightPtr;
            delete node;
            if (r == nullptr) {
                return q;
            }
            Node<T> *min = this->findMin(r);
            min->rightPtr = this->removeMin(r);
            min->leftPtr = q;
            return this->balance(min);
        }
        return this->balance(node);
    }

    template<typename T>
    T &AVLTree<T>::find(Node<T> *node, T key) {
        if (node == nullptr) {
            return this->defaultKey;
        }
        if (key == node->key) {
            return node->key;
        }
        if (key < node->key) {
            return this->find(node->leftPtr, key);
        }
        if (key > node->key) {
            return this->find(node->rightPtr, key);
        }
    }

    template<typename T>
    void AVLTree<T>::remove(T key) {
        this->rootPtr = this->remove(this->rootPtr, key);
    }

    template<typename T>
    T &AVLTree<T>::search(T key) {
        return this->find(this->rootPtr, key);
    }
}

#endif

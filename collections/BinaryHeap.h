#ifndef COLLECTIONS_BINARYHEAP_H
#define COLLECTIONS_BINARYHEAP_H
    #include "Array.h"
    #include <iostream>
    #include <cmath>

    template <typename T>
    class BinaryHeap{
    private:
        Array<T> data;
        int size;
    public:
        template<typename Fun> BinaryHeap(Array<T>, Fun);
        template<typename Fun> void siftDown(int, Fun);
        template<typename Fun> void siftUp(int, Fun);
        template<typename Fun> void heapify(Fun);
        template<typename Fun> T extractMin(Fun);
        template<typename T1> friend std::ostream& operator<< (std::ostream &, BinaryHeap<T1> &);
    };

    template<typename T>
    template<typename Fun>
    BinaryHeap<T>::BinaryHeap(Array<T> Arr, Fun ratioFunction) {
        this->data = Arr;
        this->size = log2(Arr.length());
        heapify(ratioFunction);
    }
    template<typename T>
    template<typename Fun>
    void BinaryHeap<T>::siftDown(int node, Fun ratioFunction) {
        if (2 * node + 2 < this->data.length()){
            if (ratioFunction(this->data[node], this->data[node * 2 + 1]) || ratioFunction(this->data[node], this->data[node * 2 + 2])){
                if (ratioFunction(this->data[node * 2 + 1], this->data[node * 2 + 2])){
                    this->data.swap(node, node * 2 + 2);
                    siftDown(node * 2 + 2, ratioFunction);
                }
                else {
                    this->data.swap(node, node * 2 + 1);
                    siftDown(node * 2 + 1, ratioFunction);
                }
            }
        }
    }

    template<typename T>
    template<typename Fun>
    void BinaryHeap<T>::siftUp(int node, Fun ratioFunction) {
        int fNode = node % 2 == 0 ? (node / 2 - 1) : (node / 2);
        if (fNode >= 0 && ratioFunction(this->data[fNode], this->data[node])){
            this->data.swap(node, fNode);
            siftUp(fNode, ratioFunction);
        }
    }

    template<typename T>
    template<typename Fun>
    void BinaryHeap<T>::heapify(Fun ratioFunction) {
        for (int i = this->data.length() - 1; i >= 0; --i){
            siftUp(i, ratioFunction);
        }
        for (int i = 0; i < this->data.length(); ++i){
            siftDown(i, ratioFunction);
        }
    }

    template<typename T>
    template<typename Fun>
    T BinaryHeap<T>::extractMin(Fun ratioFunction) {
        T mn = this->data[0];
        this->data[0] = this->data[this->data.length() - 1];
        this->data.pop(this->data.length() - 1);
        heapify(ratioFunction);
        this->size = log2(this->data.length());
        return mn;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, BinaryHeap<T1> &BinH) {
        for(int i = 0; i < BinH.data.length() / 2; ++i){
            out << BinH.data[i] << std::endl;
            out << "/ \\" << std::endl;
            if (i * 2 + 2 == BinH.data.length()){
                out << BinH.data[i * 2 + 1] << ' ' << "NULL" << std::endl;
            }
            else {
                out << BinH.data[i * 2 + 1] << ' ' << BinH.data[i * 2 + 2] << std::endl;
            }
        }
        return out;
    }

#endif

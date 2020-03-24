#ifndef SET_COLLECTION_BINARY_HEAP_H
#define SET_COLLECTION_BINARY_HEAP_H

    #include "array.h"
    #include <cmath>

    template <typename T>
    class BinaryHeap{
        private:
            Array<T> data;
            int size;
        public:
            explicit BinaryHeap(Array<T>);
            void print_b_heap();
            void sift_down(int);
            void sift_up(int);
            void heapify();
            T extract_min();
    };

    template<typename T>
    BinaryHeap<T>::BinaryHeap(Array<T> Arr) {
        data = Arr;
        size = log2(Arr.length());
        heapify();
    }

    template<typename T>
    void BinaryHeap<T>::print_b_heap() {
        for(int i = 0; i < data.length() / 2; ++i){
                std::cout << data[i] << std::endl;
                std::cout << "/ \\" << std::endl;
                if (i * 2 + 2 == data.length()){
                    std::cout << data[i * 2 + 1] << ' ' << "none" << std::endl;
                }
                else {
                    std::cout << data[i * 2 + 1] << ' ' << data[i * 2 + 2] << std::endl;
                }
        }
    }

    template<typename T>
    void BinaryHeap<T>::sift_down(int node) {
        if (2 * node + 2 < data.length()){
            if (data[node] > data[node * 2 + 1] || data[node] > data[node * 2 + 2]){
                if (data[node * 2 + 1] > data[node * 2 + 2]){
                    data.swap(node, node * 2 + 2);
                    sift_down(node * 2 + 2);
                }
                else {
                    data.swap(node, node * 2 + 1);
                    sift_down(node * 2 + 1);
                }
            }
        }
    }

    template<typename T>
    void BinaryHeap<T>::sift_up(int node) {
        int f_node = node % 2 == 0 ? (node / 2 - 1) : (node / 2);
        if (f_node >= 0 && data[f_node] > data[node]){
            data.swap(node, f_node);
            sift_up(f_node);
        }
    }

    template<typename T>
    void BinaryHeap<T>::heapify() {
        for (int i = data.length() - 1; i >= 0; --i){
            sift_up(i);
        }
        for (int i = 0; i < data.length(); ++i){
            sift_down(i);
        }
    }

    template<typename T>
    T BinaryHeap<T>::extract_min() {
        T mn = data.get_element(0);
        data.set_element(0, data[data.length() - 1]);
        data.pop(data.length() - 1);
        heapify();
        size = log2(data.length());
        return mn;
    }


#endif

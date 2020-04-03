#ifndef SET_COLLECTION_BINARY_HEAP_H
#define SET_COLLECTION_BINARY_HEAP_H

    #include "array_sequence.h"
    #include <cmath>

    template <typename T>
    class BinaryHeap{
        private:
            ArraySequence<T> data;
            int size;
        public:
            template<typename Fun> explicit BinaryHeap(ArraySequence<T>, Fun);
            void print_b_heap();
            template<typename Fun> void sift_down(int, Fun);
            template<typename Fun> void sift_up(int, Fun);
            template<typename Fun> void heapify(Fun);
            template<typename Fun> T extract_min(Fun);
    };

    template<typename T>
    template<typename Fun>
    BinaryHeap<T>::BinaryHeap(ArraySequence<T> Arr, Fun ratio_function) {
        data = Arr;
        size = log2(Arr.length());
        heapify(ratio_function);
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
    template<typename Fun>
    void BinaryHeap<T>::sift_down(int node, Fun ratio_function) {
        if (2 * node + 2 < data.length()){
            if (ratio_function(data[node], data[node * 2 + 1]) || ratio_function(data[node], data[node * 2 + 2])){
                if (ratio_function(data[node * 2 + 1], data[node * 2 + 2])){
                    data.swap(node, node * 2 + 2);
                    sift_down(node * 2 + 2, ratio_function);
                }
                else {
                    data.swap(node, node * 2 + 1);
                    sift_down(node * 2 + 1, ratio_function);
                }
            }
        }
    }

    template<typename T>
    template<typename Fun>
    void BinaryHeap<T>::sift_up(int node, Fun ratio_function) {
        int f_node = node % 2 == 0 ? (node / 2 - 1) : (node / 2);
        if (f_node >= 0 && ratio_function(data[f_node], data[node])){
            data.swap(node, f_node);
            sift_up(f_node, ratio_function);
        }
    }

    template<typename T>
    template<typename Fun>
    void BinaryHeap<T>::heapify(Fun ratio_function) {
        for (int i = data.length() - 1; i >= 0; --i){
            sift_up(i, ratio_function);
        }
        for (int i = 0; i < data.length(); ++i){
            sift_down(i, ratio_function);
        }
    }

    template<typename T>
    template<typename Fun>
    T BinaryHeap<T>::extract_min(Fun ratio_function) {
        T mn = data.get_element(0);
        data.set_element(0, data[data.length() - 1]);
        data.pop(data.length() - 1);
        heapify(ratio_function);
        size = log2(data.length());
        return mn;
    }


#endif

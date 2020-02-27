//
// Created by qunity on 26.02.2020.
//

#ifndef SET_SET_H
#define SET_SET_H

    #include "list.h"
    #include <iostream>

    template <typename T>
    class Set {
    private:
        int size;
        T *content;
    public:
        explicit Set(int, T);
        void print_set();
        ~Set();
    };

    template <typename T>
    Set<T>::Set(int dim, T default_val){
        content = new T [dim];
        size = dim;
        for (int i = 0; i < size; ++i){
            content[i] = default_val;
        }
    }

    template <typename T>
    void Set<T>::print_set() {
        for (int i = 0; i < size; ++i){
            std::cout << content[i] << " ";
        }
    }

    template<typename T>
    Set<T>::~Set() {
        delete [] content;
    }

#endif //SET_SET_H

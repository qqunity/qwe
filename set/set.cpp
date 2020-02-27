#include <iostream>
#include "set.h"


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

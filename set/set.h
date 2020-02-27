//
// Created by qunity on 26.02.2020.
//

#ifndef SET_SET_H
#define SET_SET_H

    #include "list.h"

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

#endif //SET_SET_H

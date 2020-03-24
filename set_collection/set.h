#ifndef SET_SET_H
#define SET_SET_H

    #include "list.h"
    #include <iostream>

    template <typename T>
    class Set: public List<T>::List {
        private:
            List<T> content;
        public:
            Set();
            ~Set();
            Set(const Set&);
            void append(T);

    };

    template<typename T>
    Set<T>::Set() {
        List<T> buff;
        content = buff;
    }

    template<typename T>
    Set<T>::~Set() {
        List<T>::content.del();
    }

    template<typename T>
    Set<T>::Set(const Set &S) {
        List buff(S.content);
        content = buff;
    }

    template<typename T>
    void Set<T>::append(T value) {
        content.append(value);
    }


#endif

#ifndef SET_LIST_H
#define SET_LIST_H

#include <ostream>
#include <zconf.h>

template <typename T>
    struct Element {
        T data;
        Element *next;
        Element *prev;
    };

    template <typename T>
    class List {
    private:
        Element<T> *head;
        Element<T> *tail;
        int count;
    public:
        List();
        ~List();
        List(const List&);
        void append(T);
        void pop(int);
        void print_list();
        void reversed();
        void swap(int, int);
        T get_firts();
        T get_last();
        T get_element(int);
        int length();
        void insert(int, T);
        List& operator = (const List&);
        List operator + (const List&);
        bool operator == (const List&);
        bool operator != (const List&);
    };
#endif

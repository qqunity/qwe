#ifndef SET_LIST_H
#define SET_LIST_H

    #include <zconf.h>
    #include <iostream>
    #include <algorithm>
    #include "list_element.h"
    #include "binary_heap.h"

    template <typename T>
    class List {
        private:
            ListElement<T> *head;
            ListElement<T> *tail;
            int count;
        public:
            List();
            ~List();
            List(const List<T> &);
            void append(T);
            void prepend(T);
            void pop(int);
            void print_list();
            void del();
            List<T> reversed();
            void swap(int, int);
            T get_first();
            T get_last();
            ListElement<T> *get_head_ptr();
            ListElement<T> *get_tail_ptr();
            T get_element(int);
            ListElement<T> *get_element_ptr(int);
            int get_index(T);
            void set_element(int, T);
            int length();
            void insert(int, T);
            Array<T> convert_to_array();
            List<T> sorted(const std::string &);
            List<T> &operator = (const List<T> &);
            List<T> operator + (const List<T> &);
            bool operator == (const List<T> &);
            bool operator != (const List<T> &);
            T operator [] (int);
            class ListIterator {
            private:
                ListElement<T> *cur_o;
            public:
                ListIterator(ListElement<T> *);
                ListElement<T> &operator + (int );
                ListElement<T> &operator - (int );
                ListElement<T> operator ++ (int);
                ListElement<T> operator -- (int);
                ListElement<T> &operator ++ ();
                ListElement<T> &operator -- ();
                ListElement<T> &operator = (ListElement<T> &);
                bool operator != (const ListIterator &);
                bool operator == (const ListIterator &);
                ListElement<T> &operator * ();
            };
            ListIterator begin();
            ListIterator end();
            template<typename T1> friend std::ostream& operator<< (std::ostream &, const List<T1> &);
    };

    template<typename T>
    List<T>::ListIterator::ListIterator(ListElement<T> *first_o) {
        this->cur_o = first_o;
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator+(int n) {
        ListElement<T> *buff = this->cur_o;
        for (int i = 0; i < n && buff != nullptr; ++i){
            buff = buff->get_next();
        }
        return *buff;
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator-(int n) {
        ListElement<T> *buff = this->cur_o;
        for (int i = 0; i < n && buff != nullptr; ++i){
            buff = buff->get_prev();
        }
        return *buff;
    }

    template<typename T>
    ListElement<T> List<T>::ListIterator::operator++(int) {
        this->cur_o = this->cur_o->get_next();
        return *(this->cur_o->get_prev);
    }

    template<typename T>
    ListElement<T> List<T>::ListIterator::operator--(int) {
        this->cur_o = this->cur_o->get_prev();
        return *(this->cur_o->get_next());
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator++() {
        this->cur_o = this->cur_o->get_next();
        return *(this->cur_o);
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator--() {
        this->cur_o = this->cur_o->get_prev();
        return *(this->cur_o);
    }

    template<typename T>
    bool List<T>::ListIterator::operator!=(const List::ListIterator &It) {
        return this->cur_o != It.cur_o;
    }

    template<typename T>
    bool List<T>::ListIterator::operator==(const List::ListIterator &It) {
        return this->cur_o == It.cur_o;
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator*() {
        return *this->cur_o;
    }

    template<typename T>
    ListElement<T> &List<T>::ListIterator::operator=(ListElement<T> &It) {
        this->cur_o = &It;
        return *this->cur_o;
    }

template<typename T>
    List<T>::List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }

    template<typename T>
    void List<T>::append(T value) {
        if (this->head == nullptr){
            auto buff = new ListElement<T>(value);
            this->head = buff;
            this->tail = buff;
            ++this->count;
        }
        else {
            auto buff = new ListElement<T>(value);
            buff->set_next(nullptr);
            buff->set_prev(this->tail);
            this->tail->set_next(buff);
            this->tail = buff;
            ++this->count;
        }
    }

    template<typename T>
    void List<T>::pop(int index) {
        if (index == 0 && this->count != 1){
            this->head = this->head->get_next();
            delete this->head->get_prev();
            this->head->set_prev(nullptr);
            --this->count;
        }
        else if (index == this->count - 1 && this->count != 1){
            this->tail = this->tail->get_prev();
            delete this->tail->get_next();
            this-> tail->set_next(nullptr);
            --this->count;
        }
        else if(count == 1){
            --this->count;
            this->tail = nullptr;
            delete this->head;
        }
        else {
            index += 1;
            ListElement<T> *buff = this->head;
            for (int i = 1; i < index; ++i) {
                buff = buff->get_next();
            }
            (buff->get_prev())->set_next(buff->get_next());
            (buff->get_next())->set_prev(buff->get_prev());
            --this->count;
            delete buff;
        }
    }

    template<typename T>
    void List<T>::print_list() {
        if (this->count == 0){
            std::cout << "null";
        }
        else {
            ListElement<T> *buff = this->head;
            std::cout << "[";
            for (int i = 0; i < this->count; ++i) {
                if (i == this->count - 1){
                    std::cout << buff->get_data();
                }
                else {
                    std::cout << buff->get_data() << ", ";
                }
                buff = buff->get_next();
            }
            std::cout << "]";
            std::cout << std::endl;
        }
    }

    template<typename T>
    void List<T>::swap(int index1, int index2) {
        if (index2 < index1){
            int buff = index1;
            index1 = index2;
            index2 = buff;
        }
        ++index1;
        ++index2;
        ListElement<T> *buff1 = this->head;
        ListElement<T> *buff2 = this->head;
        for (int i = 1; i < index1; ++i){
            buff1 = buff1->get_next();
        }
        for (int i = 1; i < index2; ++i){
            buff2 = buff2->get_next();
        }
        T t_buff = buff1->get_data();
        buff1->set_data(buff2->get_data());
        buff2->set_data(t_buff);
    }

    template<typename T>
    T List<T>::get_first() {
        return this->head->get_data();
    }

    template<typename T>
    T List<T>::get_last() {
        return this->tail->get_data();
    }

    template<typename T>
    T List<T>::get_element(int index) {
        ++index;
        ListElement<T> *buff = this->head;
        for (int i = 1; i < index; ++i) {
            buff = buff->get_next();
        }
        return buff->get_data();
    }

    template<typename T>
    int List<T>::length() {
        return this->count;
    }

    template<typename T>
    void List<T>::insert(int index, T value) {
        ++index;
        if (index - 1 == 0){
            ListElement<T> *buff = this->head;
            auto s_buff = new ListElement<T>(value);
            buff->set_prev(s_buff);
            s_buff->set_next(buff);
            s_buff->set_prev(nullptr);
            this->head = s_buff;
            ++this->count;
        }
        else if (index - 1 == this->count - 1){
            ListElement<T> *buff = this->tail;
            auto s_buff = new ListElement<T>(value);
            buff->set_next(s_buff);
            s_buff->set_prev(buff);
            s_buff->set_next(nullptr);
            this->tail = s_buff;
            ++this->count;
        }
        else {
            ListElement<T> *buff = this->head;
            for (int i = 1; i < index - 1; ++i) {
                buff = buff->get_next();
            }
            ListElement<T> *next_buff = buff->get_next();
            auto s_buff = new ListElement<T>(value);
            buff->set_next(s_buff);
            s_buff->set_prev(buff);
            s_buff->set_next(next_buff);
            next_buff->set_prev(s_buff);
            ++this->count;
        }
    }

    template<typename T>
    List<T>::List(const List<T> &L) {
        this->head = this->tail = nullptr;
        this->count = 0;
        ListElement<T> *buff = L.head;
        while (buff != nullptr) {
            append(buff->get_data());
            buff = buff->get_next();
        }
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &L) {
        if (this == &L){
            return *this;
        }
        this->~List<T>();
        ListElement<T> *buff = L.head;
        while (buff != nullptr){
            append(buff->get_data());
            buff = buff->get_next();
        }
        return *this;
    }

    template<typename T>
    List<T> List<T>::operator+(const List<T> &L) {
        List<T> res(*this);
        ListElement<T> *buff = L.head;
        while (buff != nullptr){
            res.append(buff->get_data());
            buff = buff->get_next();
        }
        return res;
    }

    template<typename T>
    bool List<T>::operator==(const List<T> &L2) {
        ListElement<T> *ptr_L1 = this->head;
        ListElement<T> *ptr_L2 = L2.head;
        if (this->count != L2.count){
            return false;
        }
        while (ptr_L1 != nullptr && ptr_L2 != nullptr){
            if (ptr_L1->get_data() != ptr_L2->get_data()){
                return false;
            }
            ptr_L1 = ptr_L1->get_next();
            ptr_L2 = ptr_L2->get_next();
        }
        return true;
    }

    template<typename T>
    bool List<T>::operator!=(const List<T> &L2) {
        return !((*this) == L2);
    }

    template<typename T>
    List<T> List<T>::reversed() {
        List<T> new_L;
        ListElement<T> *buff = this->tail;
        while (buff != nullptr){
            new_L.append(buff->get_data());
            buff = buff->get_prev();
        }
        return new_L;
    }

    template<typename T>
    void List<T>::del() {
        while (this->count != 0){
            pop(0);
        }
    }

    template<typename T>
    List<T>::~List() {
        del();
    }

    template<typename T>
    void List<T>::set_element(int index, T value) {
        ListElement<T> *buff = this->head;
        for (int i = 0; i < index; ++i){
            buff = buff->get_next();
        }
        buff->set_data(value);
    }

    template<typename T>
    void List<T>::prepend(T val) {
        if (this->count != 0) {
            ListElement<T> *buff = this->head;
            auto *s_buff = new ListElement<T>(val);
            s_buff->set_prev(nullptr);
            s_buff->set_next(buff);
            buff->set_prev(s_buff);
            this->head = s_buff;
            ++this->count;
        }
        else {
            auto *s_buff = new ListElement<T>(val);
            s_buff->set_prev(nullptr);
            s_buff->set_next(nullptr);
            this->head = s_buff;
            this->tail = s_buff;
            ++this->count;
        }
    }

    template<typename T>
    int List<T>::get_index(T val) {
        ListElement<T> *buff = this->head;
        int i = 0;
        while (buff != nullptr){
            if (buff->get_data() == val) {
                return i;
            }
            buff = buff->get_next();
            ++i;
        }
        return -1;
    }

    template<typename T>
    Array<T> List<T>::convert_to_array() {
        Array<T> arr;
        ListElement<T> *buff = this->head;
        while (buff != nullptr){
            arr.append(buff->get_data());
            buff = buff->get_next();
        }
        return arr;
    }

    template<typename T>
    List<T> List<T>::sorted(const std::string& order) {
        Array<T> arr((*this).convert_to_array());
        BinaryHeap<T> b_h(arr);
        if (order == "ASC") {
            List<T> l_buff;
            for (int i = 0; i < count; ++i){
                l_buff.append(b_h.extract_min());
            }
            return l_buff;
        }
        else if (order == "DESC"){
            List<T> l_buff;
            for (int i = 0; i < count; ++i){
                l_buff.prepend(b_h.extract_min());
            }
            return l_buff;
        }
    }

    template<typename T>
    typename List<T>::ListIterator List<T>::begin() {
        return this->head;
    }

    template<typename T>
    typename List<T>::ListIterator List<T>::end() {
        return this->tail->get_next();
    }

    template<typename T>
    T List<T>::operator[](int index) {
        return get_element(index);
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const List<T1> &L) {
        if (L.count == 0){
            out << "null";
        }
        else {
            auto buff = L.head;
            out << "[";
            for (int i = 0; i < L.count; ++i) {
                if (i == L.count - 1){
                    out << buff->get_data();
                }
                else {
                    out << buff->get_data() << ", ";
                }
                buff = buff->get_next();
            }
            out << "]";
        }
        return out;
    }

    template<typename T>
    ListElement<T> *List<T>::get_head_ptr() {
        return this->head;
    }

    template<typename T>
    ListElement<T> *List<T>::get_tail_ptr() {
        return this->tail;
    }

    template<typename T>
    ListElement<T> *List<T>::get_element_ptr(int index) {
        ListElement<T> *buff = this->head;
        for (int i = 0; i < index; ++i){
            buff = buff->get_next();
        }
        return buff;
    }

#endif

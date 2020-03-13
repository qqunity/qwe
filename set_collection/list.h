#ifndef SET_LIST_H
#define SET_LIST_H

    #include <zconf.h>
    #include <iostream>
    #include <algorithm>
    #include "list_element.h"

    template <typename T>
    class List {
    private:
        ListElement<T> *head;
        ListElement<T> *tail;
        int count;
    public:
        List();
        ~List();
        List(const List<T>&);
        void append(T);
        void prepend(T);
        void pop(int);
        void print_list();
        void del();
        List<T> reversed();
        void swap(int, int);
        T get_firts();
        T get_last();
        T get_element(int);
        void set_element(int, T);
        int length();
        void insert(int, T);
        List<T>& operator = (const List<T>&);
        List<T> operator + (const List<T>&);
        bool operator == (const List<T>&);
        bool operator != (const List<T>&);
    };

    template<typename T>
    List<T>::List() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    template<typename T>
    void List<T>::append(T value) {
        if (head == nullptr){
            auto *buff = new ListElement<T>(value);
            head = buff;
            tail = buff;
            ++count;
        }
        else {
            auto *buff = new ListElement<T>(value);
            buff->set_next(nullptr);
            buff->set_prev(tail);
            tail->set_next(buff);
            tail = buff;
            ++count;
        }
    }

    template<typename T>
    void List<T>::pop(int index) {
        if (index == 0 && count != 1){
            head = head->get_next();
            delete head->get_prev();
            head->set_prev(nullptr);
            --count;
        }
        else if (index == count - 1 && count != 1){
            tail = tail->get_prev();
            delete tail->get_next();
            tail->set_next(nullptr);
            --count;
        }
        else if(count == 1){
            --count;
            tail = nullptr;
            delete head;
        }
        else {
            index += 1;
            ListElement<T> *buff = head;
            for (int i = 1; i < index; ++i) {
                buff = buff->get_next();
            }
            (buff->get_prev())->set_next(buff->get_next());
            (buff->get_next())->set_prev(buff->get_prev());
            --count;
            delete buff;
        }
    }

    template<typename T>
    void List<T>::print_list() {
        if (count == 0){
            std::cout << "null";
        }
        else {
            ListElement<T> *buff = head;
            std::cout << "[";
            for (int i = 0; i < count; ++i) {
                if (i == count - 1){
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
        ListElement<T> *buff1 = head;
        ListElement<T> *buff2 = head;
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
    T List<T>::get_firts() {
        return head->get_data();
    }

    template<typename T>
    T List<T>::get_last() {
        return tail->get_data();
    }

    template<typename T>
    T List<T>::get_element(int index) {
        ++index;
        ListElement<T> *buff = head;
        for (int i = 1; i < index; ++i) {
            buff = buff->get_next();
        }
        return buff->get_data();
    }

    template<typename T>
    int List<T>::length() {
        return count;
    }

    template<typename T>
    void List<T>::insert(int index, T value) {
        ++index;
        if (index - 1 == 0){
            ListElement<T> *buff = head;
            auto *s_buff = new ListElement<T>(value);
            buff->set_prev(s_buff);
            s_buff->set_next(buff);
            s_buff->set_prev(nullptr);
            head = s_buff;
            ++count;
        }
        else if (index - 1 == count - 1){
            ListElement<T> *buff = tail;
            auto *s_buff = new ListElement<T>(value);
            buff->set_next(s_buff);
            s_buff->set_prev(buff);
            s_buff->set_next(nullptr);
            tail = s_buff;
            ++count;
        }
        else {
            ListElement<T> *buff = head;
            for (int i = 1; i < index - 1; ++i) {
                buff = buff->get_next();
            }
            ListElement<T> *next_buff = buff->get_next();
            auto *s_buff = new ListElement<T>(value);
            buff->set_next(s_buff);
            s_buff->set_prev(buff);
            s_buff->set_next(next_buff);
            next_buff->set_prev(s_buff);
            ++count;
        }
    }

    template<typename T>
    List<T>::List(const List<T> &L) {
        head = tail = nullptr;
        count = 0;
        ListElement<T> *buff = L.head;
        while (buff != nullptr) {
            this->append(buff->get_data());
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
            this->append(buff->get_data());
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
        ListElement<T> *ptr_L1 = (*this).head;
        ListElement<T> *ptr_L2 = L2.head;
        if ((*this).count != L2.count){
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
        ListElement<T> *buff = tail;
        while (buff != nullptr){
            new_L.append(buff->get_data());
            buff = buff->get_prev();
        }
        return new_L;
    }

    template<typename T>
    void List<T>::del() {
        while (count != 0){
            pop(0);
        }
    }

    template<typename T>
    List<T>::~List() {
        del();
    }

    template<typename T>
    void List<T>::set_element(int index, T value) {
        ListElement<T> *buff = head;
        for (int i = 0; i < index; ++i){
            buff = buff->get_next();
        }
        buff->set_data(value);
    }

    template<typename T>
    void List<T>::prepend(T val) {
        if (count != 0) {
            ListElement<T> *buff = head;
            auto *s_buff = new ListElement<T>(val);
            s_buff->set_prev(nullptr);
            s_buff->set_next(buff);
            buff->set_prev(s_buff);
            head = s_buff;
            ++count;
        }
        else {
            auto *s_buff = new ListElement<T>(val);
            s_buff->set_prev(nullptr);
            s_buff->set_next(nullptr);
            head = s_buff;
            tail = s_buff;
            ++count;
        }
    }


#endif

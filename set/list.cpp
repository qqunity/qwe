#include "list.h"
#include <iostream>
#include <algorithm>

template<typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<typename T>
void List<T>::append(T value) {
    if (head == nullptr){
        auto *buff = new Element<T>;
        buff->data = value;
        buff->prev = nullptr;
        buff->next = nullptr;
        head = buff;
        tail = buff;
        ++count;
    }
    else {
        auto *buff = new Element<T>;
        buff->data = value;
        buff->next = nullptr;
        buff->prev = tail;
        tail->next = buff;
        tail = buff;
        ++count;
    }
}

template<typename T>
void List<T>::pop(int index) {
    index += 1;
    Element<T> *buff = head;
    for (int i = 1; i < index; ++i){
        buff = buff->next;
    }
    (buff->prev)->next = buff->next;
    (buff->next)->prev = buff->prev;
    --count;
    delete buff;
}

template<typename T>
void List<T>::print_list() {
    Element<T> *buff = head;
    for(int i = 0; i < count; ++i){
        std::cout << buff->data << " ";
        buff = buff->next;
    }
    std::cout << std::endl;
}

template<typename T>
void List<T>::swap(int index1, int index2) {
    index1 = std::min(index1, index2);
    index2 = std::max(index1, index2);
    if (index1 != 0 && index1 != count - 1 && index2 != 0 && index2 != count - 1) {
        ++index1;
        ++index2;
        Element<T> *buff1 = head;
        for (int i = 1; i < index1; ++i) {
            buff1 = buff1->next;
        }
        Element<T> *buff2 = head;
        for (int i = 1; i < index2; ++i) {
            buff2 = buff2->next;
        }
        Element<T> *prev_buff2 = buff2->prev;
        Element<T> *next_buff2 = buff2->next;
        buff1->prev->next = buff2;
        buff2->prev = buff1->prev;
        buff2->next = buff1->next;
        buff1->next->prev = buff2;
        prev_buff2->next = buff1;
        buff1->prev = prev_buff2;
        next_buff2->prev = buff1;
        buff1->next = next_buff2;
    }
    else if (index1 == 0 && index2 != 0 && index2 != count - 1) {
        ++index1;
        ++index2;
        Element<T> *buff1 = head;
        for (int i = 1; i < index1; ++i) {
            buff1 = buff1->next;
        }
        Element<T> *buff2 = head;
        for (int i = 1; i < index2; ++i) {
            buff2 = buff2->next;
        }
        Element<T> *prev_buff2 = buff2->prev;
        Element<T> *next_buff2 = buff2->next;
        head = buff2;
        buff2->prev = nullptr;
        buff2->next = buff1->next;
        buff1->next->prev = buff2;
        prev_buff2->next = buff1;
        buff1->prev = prev_buff2;
        next_buff2->prev = buff1;
        buff1->next = next_buff2;
    }
    else if (index1 == 0 && index2 == count - 1) {
        ++index1;
        ++index2;
        Element<T> *buff1 = head;
        for (int i = 1; i < index1; ++i) {
            buff1 = buff1->next;
        }
        Element<T> *buff2 = head;
        for (int i = 1; i < index2; ++i) {
            buff2 = buff2->next;
        }
        Element<T> *prev_buff2 = buff2->prev;
        head = buff2;
        buff2->prev = nullptr;
        buff2->next = buff1->next;
        buff1->next->prev = buff2;
        prev_buff2->next = buff1;
        buff1->prev = prev_buff2;
        buff1->next = nullptr;
        tail = buff1;
    }
}

template<typename T>
T List<T>::get_firts() {
    return head->data;
}

template<typename T>
T List<T>::get_last() {
    return tail->data;
}

template<typename T>
T List<T>::get_element(int index) {
    ++index;
    Element<T> *buff = head;
    for (int i = 1; i < index; ++i) {
        buff = buff->next;
    }
    return buff->data;
}

template<typename T>
int List<T>::length() {
    return count;
}

template<typename T>
void List<T>::insert(int index, T value) {
    ++index;
    if (index - 1 == 0){
        Element<T> *buff = head;
        auto *sbuff = new Element<T>;
        sbuff->data = value;
        buff->prev = sbuff;
        sbuff->next = buff;
        sbuff->prev = nullptr;
        head = sbuff;
        ++count;
    }
    else if (index - 1 == count - 1){
        Element<T> *buff = tail;
        auto *sbuff = new Element<T>;
        sbuff->data = value;
        buff->next = sbuff;
        sbuff->prev = buff;
        sbuff->next = nullptr;
        tail = sbuff;
        ++count;
    }
    else {
        Element<T> *buff = head;
        for (int i = 1; i < index - 1; ++i) {
            buff = buff->next;
        }
        Element<T> *next_buff = buff->next;
        auto *sbuff = new Element<T>;
        sbuff->data = value;
        buff->next = sbuff;
        sbuff->prev = buff;
        sbuff->next = next_buff;
        next_buff->prev = sbuff;
        ++count;
    }
}

template<typename T>
List<T>::List(const List &L) {
    head = tail = nullptr;
    count = 0;
    Element<T> *buff = L.head;
    while (buff != nullptr){
        append(buff->data);
        buff = buff->next;
    }
}

template<typename T>
List<T> &List<T>::operator=(const List &L) {
    if (this == &L){
        return *this;
    }
    this->~List<T>();
    Element<T> *buff = L.head;
    while (buff != nullptr){
        (*this).append(buff->data);
        buff = buff->next;
    }
    return *this;
}

template<typename T>
List<T> List<T>::operator+(const List &L) {
    List res(*this);
    Element<T> *buff = L.head;
    while (buff != nullptr){
        res.append(buff->data);
        buff = buff->next;
    }
    return res;
}

template<typename T>
bool List<T>::operator==(const List &L2) {
    Element<T> *ptr_L1 = (*this).head;
    Element<T> *ptr_L2 = L2.head;
    if ((*this).count != L2.count){
        return false;
    }
    while (ptr_L1 != nullptr && ptr_L2 != nullptr){
        if (ptr_L1->data != ptr_L2->data){
            return false;
        }
        ptr_L1 = ptr_L1->next;
        ptr_L2 = ptr_L2->next;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(const List &L2) {
    return !((*this) == L2);
}

template<typename T>
List<T>::~List() = default;

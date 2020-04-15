#pragma once
#ifndef TASKS_LIST_H
#define TASKS_LIST_H
    #include "ListElement.h"

    template<typename T>
    class List {
        private:
            std::shared_ptr<ListElement<T>> headPtr;
            std::shared_ptr<ListElement<T>> tailPtr;
            int size;
        public:
            List();
            List(const  List<T> &list);
            List(T *mas, int count);
            void append(T val);
            void prepend(T val);
            void pop(int index);
            void remove();
            void swap(int index1, int index2);
            T getElement(int index);
            int getIndex(T val);
            int length();
            ListElement<T> getFirst();
            ListElement<T> getLast();
            void insert(int pos, T val);
            List<T> &operator=(const List<T> &list);
            List<T> operator+(const List<T> &list);
            ListElement<T> &operator[](int pos);
            bool operator==(const List<T> &list);
            bool operator!=(const List<T> &list);
            ~List();
            template<typename T1> friend std::ostream& operator<< (std::ostream &out, const List<T1> &list);
    };

    template<typename T>
    List<T>::List() {
        this->tailPtr.reset();
        this->headPtr.reset();
        this->size = 0;
    }

    template<typename T>
    void List<T>::append(T val) {
        if(this->size == 0){
            auto buffElPtr = new ListElement<T>(val);
            auto buffElSmartPtr = std::make_shared<ListElement<T>>(*buffElPtr);
            this->headPtr = buffElSmartPtr;
            this->tailPtr = buffElSmartPtr;
            ++this->size;
        }
        else {
            auto buffElPtr = new ListElement<T>(val);
            auto buffElSmartPtr = std::make_shared<ListElement<T>>(*buffElPtr);
            this->tailPtr->setNextPtr(buffElSmartPtr);
            buffElSmartPtr->setPrevPtr(this->tailPtr);
            this->tailPtr = buffElSmartPtr;
            ++this->size;
        }
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const List<T1> &list) {
        if (list.size == 0){
            out << "NULL";
        }
        else {
            auto buffElSmartPtr = list.headPtr;
            out << "[";
            for (int i = 0; i < list.size && buffElSmartPtr != NULL; ++i){
                if (i == list.size - 1){
                    out << *buffElSmartPtr << "]";
                }
                else {
                    out << *buffElSmartPtr << ", ";
                }
                buffElSmartPtr = buffElSmartPtr->getNextPtr();
            }
        }
        return out;
    }

    template<typename T>
    List<T>::List(T *mas, int count) {
        this->tailPtr.reset();
        this->headPtr.reset();
        this->size = 0;
        for (int i = 0; i < count; ++i) {
            append(mas[i]);
        }
    }

    template<typename T>
    void List<T>::prepend(T val) {
        if(this->size == 0){
            auto buffElPtr = new ListElement<T>(val);
            auto buffElSmartPtr = std::make_shared<ListElement<T>>(*buffElPtr);
            this->headPtr = buffElSmartPtr;
            this->tailPtr = buffElSmartPtr;
            ++this->size;
        }
        else {
            auto buffElPtr = new ListElement<T>(val);
            auto buffElSmartPtr = std::make_shared<ListElement<T>>(*buffElPtr);
            this->headPtr->setPrevPtr(buffElSmartPtr);
            buffElSmartPtr->setNextPtr(this->headPtr);
            this->headPtr = buffElSmartPtr;
            ++this->size;
        }
    }

    template<typename T>
    void List<T>::pop(int index) {
        if (index >= 0 && index < this->size){
            if (this->size == 1){
                this->headPtr.reset();
                this->tailPtr.reset();
            }
            else if (index == 0) {
                this->headPtr = this->headPtr->getNextPtr();
                this->headPtr->getPrevPtr().reset();
            }
            else if (index == this->size - 1) {
                this->tailPtr = this->tailPtr->getPrevPtr();
                this->tailPtr->getNextPtr().reset();
            }
            else {
                auto buffElSmartPtr = this->headPtr;
                for (int i = 0; i < index && buffElSmartPtr != NULL; ++ i){
                    buffElSmartPtr = buffElSmartPtr->getNextPtr();
                }
                buffElSmartPtr->getPrevPtr()->setNextPtr(buffElSmartPtr->getNextPtr());
                buffElSmartPtr->getNextPtr()->setPrevPtr(buffElSmartPtr->getPrevPtr());
                buffElSmartPtr.reset();
            }
            --this->size;
        }
        else {
            throw ListException("Index out of range!");
        }
    }

    template<typename T>
    void List<T>::remove() {
        while (this->size > 0) {
            pop(0);
        }
    }

    template<typename T>
    void List<T>::swap(int index1, int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size) {
            T buffData;
            auto buffElSmartPtr1 = this->headPtr;
            for (int i = 0; i < index1 && buffElSmartPtr1 != NULL; ++ i){
                buffElSmartPtr1 = buffElSmartPtr1->getNextPtr();
            }
            auto buffElSmartPtr2 = this->headPtr;
            for (int i = 0; i < index2 && buffElSmartPtr2 != NULL; ++ i){
                buffElSmartPtr2 = buffElSmartPtr2->getNextPtr();
            }
            buffData = buffElSmartPtr1->getData();
            buffElSmartPtr1->setData(buffElSmartPtr2->getData());
            buffElSmartPtr2->setData(buffData);
        }
        else {
            throw ListException("Index out of range!");
        }
    }

    template<typename T>
    T List<T>::getElement(int index) {
        if (index >= 0 && index < this->size) {
            auto buffElSmartPtr = this->headPtr;
            for (int i = 0; i < index && buffElSmartPtr != NULL; ++ i){
                buffElSmartPtr = buffElSmartPtr->getNextPtr();
            }
            return buffElSmartPtr->getData();
        }
        else {
            throw ListException("Index out of range!");
        }
    }

    template<typename T>
    int List<T>::getIndex(T val) {
        auto buffElSmartPtr = this->headPtr;
        for (int i = 0; i < size && buffElSmartPtr != NULL; ++ i){
            if (buffElSmartPtr->getData() == val) {
                return i;
            }
            buffElSmartPtr = buffElSmartPtr->getNextPtr();
        }
        return -1;
    }

    template<typename T>
    int List<T>::length() {
        return this->size;
    }

    template<typename T>
    ListElement<T> List<T>::getFirst() {
        return *this->headPtr;
    }

    template<typename T>
    ListElement<T> List<T>::getLast() {
        return *this->tailPtr;
    }

    template<typename T>
    void List<T>::insert(int pos, T val) {
        if (pos >= 0 && pos <= this->size) {
            if (pos == 0) {
                prepend(val);
            }
            else if (pos == this->size) {
                append(val);
            }
            else {
                auto buffElSmartPtr = this->headPtr;
                for (int i = 0; i < pos - 1 && buffElSmartPtr != NULL; ++ i){
                    buffElSmartPtr = buffElSmartPtr->getNextPtr();
                }
                auto buffElPtr = new ListElement<T>(val);
                auto newBuffElSmartPtr = std::make_shared<ListElement<T>>(*buffElPtr);
                auto nextBuffSmartPtr = buffElSmartPtr->getNextPtr();
                buffElSmartPtr->setNextPtr(newBuffElSmartPtr);
                newBuffElSmartPtr->setPrevPtr(buffElSmartPtr);
                newBuffElSmartPtr->setNextPtr(nextBuffSmartPtr);
                nextBuffSmartPtr->setPrevPtr(newBuffElSmartPtr);
            }
        }
        else {
            throw ListException("Index out of range!");
        }
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &list) {
        if (this == &list) {
            return *this;
        }
        remove();
        auto buffElSmartPtr = list.headPtr;
        for (int i = 0; i < list.size && buffElSmartPtr != NULL; ++ i){
            append(buffElSmartPtr->getData());
            buffElSmartPtr = buffElSmartPtr->getNextPtr();
        }
        return *this;
    }

    template<typename T>
    List<T> List<T>::operator+(const List<T> &list) {
        List<T> buffList(*this);
        auto buffElSmartPtr = list.headPtr;
        for (int i = 0; i < list.size && buffElSmartPtr != NULL; ++ i){
            buffList.append(buffElSmartPtr->getData());
            buffElSmartPtr = buffElSmartPtr->getNextPtr();
        }
        return buffList;
    }

    template<typename T>
    List<T>::List(const List<T> &list) {
        this->tailPtr.reset();
        this->headPtr.reset();
        this->size = 0;
        auto buffElSmartPtr = list.headPtr;
        for (int i = 0; i < list.size && buffElSmartPtr != NULL; ++ i){
            append(buffElSmartPtr->getData());
            buffElSmartPtr = buffElSmartPtr->getNextPtr();
        }
    }

    template<typename T>
    ListElement<T> &List<T>::operator[](int pos) {
        if (pos >= 0 && pos < this->size) {
            auto buffElSmartPtr = this->headPtr;
            for (int i = 0; i < pos && buffElSmartPtr != NULL; ++ i){
                buffElSmartPtr = buffElSmartPtr->getNextPtr();
            }
            return *buffElSmartPtr;
        }
        else {
            throw ListException("Index out of range!");
        }
    }

    template<typename T>
    bool List<T>::operator==(const List<T> &list) {
        if (this->size == list.size) {
            auto buffElSmartPtr1 = this->headPtr;
            auto buffElSmartPtr2 = list.headPtr;
            for (int i = 0; i < this->size && buffElSmartPtr1 != NULL && buffElSmartPtr2 != NULL; ++ i){
                if (buffElSmartPtr1->getData() != buffElSmartPtr2->getData()) {
                    return false;
                }
                buffElSmartPtr1 = buffElSmartPtr1->getNextPtr();
                buffElSmartPtr2 = buffElSmartPtr2->getNextPtr();
            }
            return true;
        }
        else {
            throw ListException("It is not possible to compare arrays of different lengths!");
        }
    }

    template<typename T>
    bool List<T>::operator!=(const List<T> &list) {
        return !(*this == list);
    }


template<typename T>
    List<T>::~List() = default;

#endif

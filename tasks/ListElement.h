#pragma once
#ifndef TASKS_LISTELEMENT_H
#define TASKS_LISTELEMENT_H

    #include <memory>
    #include "Exceptions.h"

    template<typename T>
    class ListElement {
        private:
            T data;
            bool hasData;
            std::shared_ptr<ListElement<T>> nextPtr;
            std::weak_ptr<ListElement<T>> prevPtr;
        public:
            ListElement();
            ListElement(T data);
            void setData(T data);
            void setNextPtr(std::shared_ptr<ListElement<T>> ptr);
            void setPrevPtr(std::shared_ptr<ListElement<T>> ptr);
            T getData();
            std::shared_ptr<ListElement<T>> getNextPtr();
            std::shared_ptr<ListElement<T>> getPrevPtr();
            bool checkData();
            ListElement<T> &operator = (const ListElement<T> &listEl);
            ListElement<T> &operator = (T data);
            operator T();
            ~ListElement();
            template<typename T1> friend std::ostream& operator<< (std::ostream &out, const ListElement<T1> &listEl);
    };

    template<typename T>
    ListElement<T>::ListElement() {
        this->hasData = false;
    }

    template<typename T>
    ListElement<T>::ListElement(T data) {
        this->data = data;
        this->hasData = true;
    }

    template<typename T>
    void ListElement<T>::setData(T data) {
        this->data = data;
        this->hasData = true;
    }

    template<typename T>
    void ListElement<T>::setNextPtr(std::shared_ptr<ListElement<T>> ptr) {
        this->nextPtr = ptr;
    }

    template<typename T>
    void ListElement<T>::setPrevPtr(std::shared_ptr<ListElement<T>> ptr) {
        this->prevPtr = ptr;
    }

    template<typename T>
    T ListElement<T>::getData() {
        if (this->hasData){
            return this->data;
        }
        else {
            throw ListElementException("Element hasn't data!");
        }
    }

    template<typename T>
    std::shared_ptr<ListElement<T>> ListElement<T>::getNextPtr() {
        auto buffPtr = this->nextPtr;
        return buffPtr;
    }

    template<typename T>
    std::shared_ptr<ListElement<T>> ListElement<T>::getPrevPtr() {
        auto buffPtr = this->prevPtr.lock();
        return buffPtr;
    }

    template<typename T>
    bool ListElement<T>::checkData() {
        return this->hasData;
    }

    template<typename T>
    ListElement<T> &ListElement<T>::operator=(const ListElement<T> &listEl) {
        if (this == &listEl){
            return *this;
        }
        this->hasData = listEl.hasData;
        this->data = listEl.data;
        this->prevPtr = listEl.prevPtr;
        this->nextPtr = listEl.nextPtr;
        return *this;
    }

    template<typename T>
    ListElement<T> &ListElement<T>::operator=(T data) {
        this->data = data;
        this->hasData = true;
        return *this;
    }

    template<typename T>
    ListElement<T>::operator T() {
        return this->data;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ListElement<T1> &listEl) {
        out << listEl.data;
        return out;
    }

    template<typename T>
    ListElement<T>::~ListElement() = default;


#endif

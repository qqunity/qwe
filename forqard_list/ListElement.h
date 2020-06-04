#ifndef FORQARD_LIST_LISTELEMENT_H
#define FORQARD_LIST_LISTELEMENT_H

#include <iostream>

template<typename T>
class ListElement {
private:
    T value;
    bool hasValue;
    ListElement<T> *nextPtr;
public:
    ListElement();
    ListElement(T value);
    ListElement(T value, ListElement<T> *nextPtr);
    ListElement(const ListElement<T> & listEl);
    void setValue(T value);
    T &getValue();
    void setNextPtr(ListElement<T> *ptr);
    ListElement<T> *getNextPtr();
    ListElement<T> &operator=(const ListElement<T> &listEl);
    ListElement<T> &operator=(T value);
    operator T();
    bool checkValue();
    template<typename T1> friend std::ostream& operator<< (std::ostream &out, const ListElement<T1> &listEl);
    ~ListElement();
};

template<typename T>
ListElement<T>::ListElement() {
    this->hasValue = false;
    this->nextPtr = nullptr;
}

template<typename T>
ListElement<T>::ListElement(T value) {
    this->value = value;
    this->hasValue = true;
    this->nextPtr = nullptr;
}

template<typename T>
ListElement<T>::ListElement(const ListElement<T> &listEl) {
    this->value = listEl.value;
    this->hasValue = listEl.hasValue;
    this->nextPtr = listEl.nextPtr;
}

template<typename T>
void ListElement<T>::setValue(T value) {
    this->value = value;
    this->hasValue = true;
}

template<typename T>
ListElement<T>::ListElement(T value, ListElement<T> *nextPtr) {
    this->value = value;
    this->nextPtr = nextPtr;
    this->hasValue = true;
}

template<typename T>
T &ListElement<T>::getValue() {
    if (this->hasValue) {
        return this->value;
    } else {
        throw "Err!";
    }
}

template<typename T>
void ListElement<T>::setNextPtr(ListElement<T> *ptr) {
    this->nextPtr = ptr;
}

template<typename T>
ListElement<T> *ListElement<T>::getNextPtr() {
    return this->nextPtr;
}

template<typename T>
bool ListElement<T>::checkValue() {
    return this->hasValue;
}

template<typename T>
ListElement<T> &ListElement<T>::operator=(const ListElement<T> &listEl) {
    if (*this == &listEl) {
        return *this;
    }
    this->hasValue = listEl.hasValue;
    this->value = listEl.value;
    this->nextPtr = listEl.nextPtr;
    return *this;
}

template<typename T>
ListElement<T> &ListElement<T>::operator=(T value) {
    this->value = value;
    this->hasValue = true;
    return *this;
}

template<typename T>
ListElement<T>::operator T() {
    if (this->hasValue) {
        return this->value;
    } else {
        throw "Err!";
    }
}

template<typename T1>
std::ostream &operator<<(std::ostream &out, const ListElement<T1> &listEl) {
    if (listEl.hasValue) {
        out << listEl.value;
    } else {
        throw "Err!";
    }
    return out;
}

template<typename T>
ListElement<T>::~ListElement() = default;

#endif

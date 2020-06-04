#ifndef FORQARD_LIST_FORWARDLIST_H
#define FORQARD_LIST_FORWARDLIST_H

#include "ListElement.h"

template<typename T>
class ForwardList {
private:
    ListElement<T> *headPtr;
    ListElement<T> *tailPtr;
    unsigned int size;
public:
    ForwardList();
    ForwardList(const ForwardList<T> &list);
    ForwardList(ForwardList<T> &&list);
    unsigned int length();
    ListElement<T> *front();
    ListElement<T> *back();
    T &getValue(unsigned int index);
    void setValue(unsigned int index, T value);
    void append(T value);
    void prepend(T value);
    T &operator[](unsigned int index);
    ForwardList<T> &operator=(const ForwardList<T> &list);
    ForwardList<T> &operator=(ForwardList<T> &&list);
    template<typename T1> friend std::ostream& operator<< (std::ostream &out, ForwardList<T> list);
    ~ForwardList();
};

template<typename T>
ForwardList<T>::ForwardList() {
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->size = 0;
}

template<typename T>
void ForwardList<T>::append(T value) {
    if (this->size == 0) {
        this->headPtr = new ListElement<T>(value);
        this->tailPtr = this->headPtr;
    } else {
        auto  buffEl = new ListElement<T>(value);
        this->tailPtr->setNextPtr(buffEl);
        this->tailPtr = buffEl;
    }
    ++this->size;
}

template<typename T1>
std::ostream &operator<<(std::ostream &out, ForwardList<T1> list) {
    if (list.length() != 0) {
        out << "[";
        auto buffEl = list.front();
        for (unsigned int i = 0; i < list.length(); ++i) {
            if (i == list.length() - 1) {
                out << buffEl->getValue();
            } else {
                out << buffEl->getValue() << ", ";
            }
            buffEl = buffEl->getNextPtr();
        }
        out << "]";
    } else {
        out << "NULL";
    }
    return out;
}

template<typename T>
unsigned int ForwardList<T>::length() {
    return this->size;
}

template<typename T>
ListElement<T> *ForwardList<T>::front() {
    return this->headPtr;
}

template<typename T>
ListElement<T> *ForwardList<T>::back() {
    return this->tailPtr;
}

template<typename T>
void ForwardList<T>::prepend(T value) {
    if (this->size == 0) {
        this->headPtr = new ListElement<T>(value);
        this->tailPtr = this->headPtr;
    } else {
        auto  buffEl = new ListElement<T>(value);
        buffEl->setNextPtr(this->headPtr);
        this->headPtr = buffEl;
    }
    ++this->size;
}

template<typename T>
ForwardList<T>::ForwardList(const ForwardList<T> &list) {
    auto buffEl = list.headPtr;
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->size = 0;
    for (unsigned int i = 0; i < list.size; ++i) {
        this->append(buffEl->getValue());
        buffEl = buffEl->getNextPtr();
    }
}

template<typename T>
T &ForwardList<T>::getValue(unsigned int index) {
    if (index >= 0 && index < this->size) {
        auto buffEl = this->headPtr;
        for (unsigned int i = 0; i < index; ++i) {
            buffEl = buffEl->getNextPtr();
        }
        return buffEl->getValue();
    } else {
        throw "Err!";
    }
}

template<typename T>
void ForwardList<T>::setValue(unsigned int index, T value) {
    if (index >= 0 && index < this->size) {
        auto buffEl = this->headPtr;
        for (unsigned int i = 0; i < index; ++i) {
            buffEl = buffEl->getNextPtr();
        }
        buffEl->setValue(value);
    } else {
        throw "Err!";
    }
}

template<typename T>
T &ForwardList<T>::operator[](unsigned int index) {
    return this->getValue(index);
}

template<typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &list) {
    if (this == &list) {
        return *this;
    }
    auto buffEl = this->headPtr;
    for (unsigned int i = 0; i < this->size; ++i) {
        auto nextBuffEl = buffEl->getNextPtr();
        delete buffEl;
        buffEl = nextBuffEl;
    }
    buffEl = list.headPtr;
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
    this->size = 0;
    for (unsigned int i = 0; i < list.size; ++i) {
        this->append(buffEl->getValue());
        buffEl = buffEl->getNextPtr();
    }
    return *this;
}

template<typename T>
ForwardList<T>::ForwardList(ForwardList<T> &&list) {
    this->size = std::move(list.size);
    this->tailPtr = std::move(list.tailPtr);
    this->headPtr = std::move(list.headPtr);
    list.size = 0;
    list.headPtr = nullptr;
    list.tailPtr = nullptr;
}

template<typename T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList<T> &&list) {
    if (this == &list) {
        return *this;
    }
    auto buffEl = this->headPtr;
    for (unsigned int i = 0; i < this->size; ++i) {
        auto nextBuffEl = buffEl->getNextPtr();
        delete buffEl;
        buffEl = nextBuffEl;
    }
    this->headPtr = list.headPtr;
    this->tailPtr = list.tailPtr;
    this->size = list.size;
    list.headPtr = nullptr;
    list.tailPtr = nullptr;
    list.size = 0;
    return *this;
}

template<typename T>
ForwardList<T>::~ForwardList() = default;

#endif

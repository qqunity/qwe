#ifndef COLLECTIONS_LIST_H
#define COLLECTIONS_LIST_H
    #include "ListElement.h"
    #include "Exceptions.h"
    #include <iostream>

    template<typename T>
    class List {
        private:
            ListElement<T> *headPtr;
            ListElement<T> *tailPtr;
            int size;
        public:
            List();
            List(T *, int);
            List(const List<T> &);
            void append(T);
            void prepend(T);
            void pop(int);
            void remove();
            void swap(int, int);
            T getElement(int);
            int getIndex(T);
            int length();
            T getFirst();
            T getLast();
            void insert(int, T);
            List<T> &operator = (const List<T> &);
            List<T> operator + (const List<T> &);
            List<T> operator * (int);
            ListElement<T> &operator [] (int);
            bool operator == (const List<T> &);
            bool operator != (const List<T> &);
            ~List();
            class ListIterator {
                private:
                    ListElement<T> *curObj;
                public:
                    ListIterator(ListElement<T> *obj) {
                        this->curObj = obj;
                    }
                    ListElement<T> &operator + (int k) {
                        ListElement<T> *buffObj = curObj;
                        for (int i = 0; i < k && buffObj != nullptr; ++i){
                            buffObj = buffObj->getNextPtr();
                        }
                        return *buffObj;
                    }
                    ListElement<T> &operator - (int k) {
                        ListElement<T> *buffObj = curObj;
                        for (int i = 0; i < k && buffObj != nullptr; ++i){
                            buffObj = buffObj->getPrevPtr();
                        }
                        return *buffObj;
                    }
                    ListElement<T> &operator ++ (int) {
                        this->curObj = this->curObj->getNextPtr();
                        return *(this->curObj->getPrevPtr());
                    }
                    ListElement<T> &operator -- (int) {
                        this->curObj = this->curObj->getPrevPtr();
                        return *(this->curObj->getNextPtr());
                    }
                    ListElement<T> &operator ++ () {
                        this->curObj = this->curObj->getNextPtr();
                        return *this->curObj;
                    }
                    ListElement<T> &operator -- () {
                        this->curObj = this->curObj->getPrevPtr();
                        return *this->curObj;
                    }
                    ListElement<T> &operator = (ListElement<T> &LstEl) {
                        this->curObj = &LstEl;
                        return *(this->curObj);
                    }
                    bool operator != (const ListIterator &LstIt) {
                        return this->curObj != LstIt.curObj;
                    }
                    bool operator == (const ListIterator &LstIt) {
                        return this->curObj == LstIt.curObj;
                    }
                    ListElement<T> &operator * () {
                        return *this->curObj;
                    }
            };
            ListIterator begin();
            ListIterator end();
            template<typename T1> friend std::ostream& operator<< (std::ostream &, const List<T1> &);
    };

    template<typename T>
    List<T>::List() {
        this->headPtr = nullptr;
        this->tailPtr = nullptr;
        this->size = 0;
    }

    template<typename T>
    void List<T>::append(T val) {
        if (this->size == 0){
            ListElement<T> *BuffEl = new ListElement<T>;
            BuffEl->setValue(val);
            BuffEl->setNextPtr(nullptr);
            BuffEl->setPrevPtr(nullptr);
            this->headPtr = BuffEl;
            this->tailPtr = BuffEl;
        }
        else {
            ListElement<T> *BuffEl = new ListElement<T>;
            BuffEl->setValue(val);
            BuffEl->setNextPtr(nullptr);
            BuffEl->setPrevPtr(this->tailPtr);
            this->tailPtr->setNextPtr(BuffEl);
            this->tailPtr = BuffEl;
        }
        ++this->size;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const List<T1> &Lst) {
        if (Lst.size != 0){
            ListElement<T1> *BuffEl = Lst.headPtr;
            out << "[";
            int i = 0;
            while (BuffEl != nullptr){
                if (i == Lst.size - 1){
                    out << BuffEl->getValue() << "]";
                }
                else {
                    out << BuffEl->getValue() << ", ";
                }
                BuffEl = BuffEl->getNextPtr();
                ++i;
            }
        }
        else {
            out << "NULL";
        }
        return out;
    }

    template<typename T>
    ListElement<T> &List<T>::operator[](int index) {
        if (index >= 0 && index < this->size){
            ListElement<T> *BuffEl = this->headPtr;
            int i = 0;
            while (BuffEl != nullptr && i < index) {
                BuffEl = BuffEl->getNextPtr();
                ++i;
            }
            return *BuffEl;
        }
        else {
            throw listException::ListException("Index out of range!");
        }
    }

    template<typename T>
    List<T>::List(const List<T> &Lst) {
        this->headPtr = nullptr;
        this->tailPtr = nullptr;
        this->size = 0;
        ListElement<T> *BuffEl = Lst.headPtr;
        while (BuffEl != nullptr){
            append(*BuffEl);
            BuffEl = BuffEl->getNextPtr();
        }
    }

    template<typename T>
    void List<T>::prepend(T val) {
        if (this->size == 0){
            ListElement<T> *BuffEl = new ListElement<T>;
            BuffEl->setValue(val);
            BuffEl->setNextPtr(nullptr);
            BuffEl->setPrevPtr(nullptr);
            this->headPtr = BuffEl;
            this->tailPtr = BuffEl;
        }
        else {
            ListElement<T> *BuffEl = new ListElement<T>;
            BuffEl->setValue(val);
            BuffEl->setNextPtr(this->headPtr);
            BuffEl->setPrevPtr(nullptr);
            this->headPtr->setPrevPtr(BuffEl);
            this->headPtr = BuffEl;
        }
        ++this->size;
    }

    template<typename T>
    List<T>::List(T *mas, int n) {
        this->headPtr = nullptr;
        this->tailPtr = nullptr;
        this->size = 0;
        for (int i = 0; i < n; ++ i){
            append(mas[i]);
        }
    }

    template<typename T>
    void List<T>::pop(int index) {
        if (index >= 0 && index < this->size) {
            if (this->size == 1){
                delete this->headPtr;
                this->headPtr = nullptr;
                this->tailPtr = nullptr;
            }
            else if (index == 0){
                this->headPtr = this->headPtr->getNextPtr();
                delete this->headPtr->getPrevPtr();
                this->headPtr->setPrevPtr(nullptr);
            }
            else if (index == this->size - 1) {
                this->tailPtr = this->tailPtr->getPrevPtr();
                delete this->tailPtr->getNextPtr();
                this->tailPtr->setNextPtr(nullptr);
            }
            else {
                ListElement<T> *BuffEl = this->headPtr;
                for (int i = 0; i < index - 1; ++i){
                    BuffEl = BuffEl->getNextPtr();
                }
                BuffEl->setNextPtr(BuffEl->getNextPtr()->getNextPtr());
                delete BuffEl->getNextPtr()->getPrevPtr();
                BuffEl->getNextPtr()->setPrevPtr(BuffEl);
            }
            --this->size;
        }
        else {
            throw listException::ListException("Index out of range!");
        }
    }

    template<typename T>
    void List<T>::remove() {
        while(this->size > 0){
            pop(0);
        }
    }

    template<typename T>
    void List<T>::swap(int index1, int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size) {
            ListElement<T> *BuffEl1 = this->headPtr;
            for (int i = 0; i < index1; ++i) {
                BuffEl1 = BuffEl1->getNextPtr();
            }
            ListElement<T> *BuffEl2 = this->headPtr;
            for (int i = 0; i < index2; ++i) {
                BuffEl2 = BuffEl2->getNextPtr();
            }
            T BuffVal = *BuffEl1;
            BuffEl1->setValue(BuffEl2->getValue());
            BuffEl2->setValue(BuffVal);
        }
        else {
            throw listException::ListException("Index out of range!");
        }
    }

    template<typename T>
    T List<T>::getElement(int index) {
        if (index >= 0 && index < this->size) {
            ListElement<T> *BuffEl = this->headPtr;
            for (int i = 0; i < index; ++i) {
                BuffEl = BuffEl->getNextPtr();
            }
            return *BuffEl;
        }
        else {
            throw listException::ListException("Index out of range!");
        }
    }

    template<typename T>
    int List<T>::getIndex(T val) {
        ListElement<T> *BuffEl = this->headPtr;
        for (int i = 0; i < this->size; ++i) {
            if (BuffEl->getValue() == val) {
                return i;
            }
            BuffEl = BuffEl->getNextPtr();
        }
        return -1;
    }

    template<typename T>
    int List<T>::length() {
        return this->size;
    }

    template<typename T>
    T List<T>::getFirst() {
        return *this->headPtr;
    }

    template<typename T>
    T List<T>::getLast() {
        return *this->tailPtr;
    }

    template<typename T>
    void List<T>::insert(int index, T val) {
        if (index >= 0 && index <= this->size) {
            if (index == 0) {
                prepend(val);
            }
            else if (index == this->size){
                append(val);
            }
            else {
                ListElement<T> *BuffElPrev = this->headPtr;
                for (int i = 0; i < index - 1; ++i) {
                    BuffElPrev = BuffElPrev->getNextPtr();
                }
                ListElement<T> *BuffElNext = BuffElPrev->getNextPtr();
                ListElement<T> *BuffEl = new ListElement<T>;
                BuffEl->setValue(val);
                BuffEl->setPrevPtr(BuffElPrev);
                BuffEl->setNextPtr(BuffElNext);
                BuffElPrev->setNextPtr(BuffEl);
                BuffElNext->setPrevPtr(BuffEl);
                ++this->size;
            }
        }
        else {
            throw listException::ListException("Index out of range!");
        }
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &Lst) {
        if (this == &Lst){
            return *this;
        }
        remove();
        ListElement<T> *BuffEl = Lst.headPtr;
        while (BuffEl != nullptr) {
            append(*BuffEl);
            BuffEl = BuffEl->getNextPtr();
        }
        return *this;
    }

    template<typename T>
    List<T> List<T>::operator+(const List<T> &Lst) {
        List<T> BuffLst (*this);
        ListElement<T> *BuffEl = Lst.headPtr;
        while (BuffEl != nullptr) {
            BuffLst.append(*BuffEl);
            BuffEl = BuffEl->getNextPtr();
        }
        return BuffLst;
    }

    template<typename T>
    List<T> List<T>::operator*(int k) {
        if (k == 0) {
            List<T> BuffLst;
            return BuffLst;
        }
        else {
            List<T> BuffLst(*this);
            for (int i = 1; i < k; ++i) {
                BuffLst = BuffLst + *this;
            }
            return BuffLst;
        }
    }

    template<typename T>
    bool List<T>::operator==(const List<T> &Lst) {
        if (this->size = Lst.size) {
            ListElement<T> *BuffEl1 = this->headPtr;
            ListElement<T> *BuffEl2 = Lst.headPtr;
            while (BuffEl1 != nullptr && BuffEl2 != nullptr){
                if (*BuffEl1 != *BuffEl2) {
                    return false;
                }
                BuffEl1 = BuffEl1->getNextPtr();
                BuffEl2 = BuffEl2->getNextPtr();
            }
            return true;
        }
        else {
            throw listException::ListException("It is not possible to compare arrays of different lengths!");
        }
    }

    template<typename T>
    bool List<T>::operator!=(const List<T> &Lst) {
        return !(*this == Lst);
    }

    template<typename T>
    typename List<T>::ListIterator List<T>::begin() {
        return this->headPtr;
    }

    template<typename T>
    typename List<T>::ListIterator List<T>::end() {
        return this->tailPtr->getNextPtr();
    }

    template<typename T>
    List<T>::~List() = default;

#endif

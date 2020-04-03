#ifndef COLLECTIONS_LISTELEMENT_H
#define COLLECTIONS_LISTELEMENT_H
    #include "Exceptions.h"

    template<typename T>
    class ListElement {
    private:
        T value;
        ListElement<T> *nextPtr;
        ListElement<T> *prevPtr;
        bool hasValue;
    public:
        ListElement();

        ListElement(T);

        ListElement(const ListElement<T> &);

        void setValue(T);

        void setNextPtr(ListElement<T> *);

        void setPrevPtr(ListElement<T> *);

        T getValue();

        ListElement<T> *getNextPtr();

        ListElement<T> *getPrevPtr();

        bool checkValue();

        ListElement<T> &operator = (const ListElement<T> &);

        ListElement<T> &operator = (T);

        operator T();

        template<typename T1> friend std::ostream& operator<< (std::ostream &, const ListElement<T1> &);

        ~ListElement();
    };

    template<typename T>
    ListElement<T>::ListElement() {
        this->hasValue = false;
        this->prevPtr = nullptr;
        this->nextPtr = nullptr;
    }

    template<typename T>
    ListElement<T>::ListElement(T val) {
        this->value = val;
        this->hasValue = true;
        this->nextPtr = nullptr;
        this->prevPtr = nullptr;
    }

    template<typename T>
    ListElement<T>::ListElement(const ListElement<T> &ListEl) {
        this->hasValue = ListEl.hasValue;
        this->value = ListEl.value;
        this->nextPtr = ListEl.nextPtr;
        this->prevPtr = ListEl.prevPtr;
    }

    template<typename T>
    void ListElement<T>::setValue(T val) {
        this->value = val;
        this->hasValue = true;
    }

    template<typename T>
    T ListElement<T>::getValue() {
        if (this->hasValue){
            return this->value;
        }
        else {
            throw listException::ListElementException("Element has not value!");
        }
    }

    template<typename T>
    bool ListElement<T>::checkValue() {
        return this->hasValue;
    }

    template<typename T>
    ListElement<T> &ListElement<T>::operator=(const ListElement<T> &ListEl) {
        if (this == &ListEl){
            return *this;
        }
        this->hasValue = ListEl.hasValue;
        this->value = ListEl.value;
        this->nextPtr = ListEl.nextPtr;
        this->prevPtr = ListEl.prevPtr;
        return *this;
    }

    template<typename T>
    ListElement<T>::operator T() {
        if (this->hasValue){
            return this->value;
        }
        else {
            throw listException::ListElementException("Element has not value!");
        }
    }

    template<typename T>
    ListElement<T> &ListElement<T>::operator=(T val) {
        this->value = val;
        this->hasValue = true;
        return *this;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ListElement<T1> &ArrEl) {
        out << ArrEl.value;
        return out;
    }

    template<typename T>
    void ListElement<T>::setNextPtr(ListElement<T> *nextPtr) {
        this->nextPtr = nextPtr;
    }

    template<typename T>
    void ListElement<T>::setPrevPtr(ListElement<T> *prevPtr) {
        this->prevPtr = prevPtr;
    }

    template<typename T>
    ListElement<T> *ListElement<T>::getNextPtr() {
        return this->nextPtr;
    }

    template<typename T>
    ListElement<T> *ListElement<T>::getPrevPtr() {
        return this->prevPtr;
    }

    template<typename T>
    ListElement<T>::~ListElement() = default;

#endif

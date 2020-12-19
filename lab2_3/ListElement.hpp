#ifndef SORTER_LISTELEMENT_HPP
#define SORTER_LISTELEMENT_HPP

#include "Optional.hpp"
#include "Exceptions.hpp"

namespace list {
    template<typename T>
    class ListElement : public optional::Optional<T> {
    private:
        ListElement<T> *nextPtr;
        ListElement<T> *prevPtr;
    public:
        ListElement();

        explicit ListElement(T value);

        ListElement(const ListElement<T> &listEl);

        void setValue(T value) override;

        void setNextPtr(ListElement<T> *nextPtr);

        void setPrevPtr(ListElement<T> *prevPtr);

        ListElement<T> *getNextPtr();

        ListElement<T> *getPrevPtr();

        T &getValue() override;

        bool checkValue() override;

        ListElement<T> &operator=(const ListElement<T> &listEl);

        ListElement<T> &operator=(T value);

        operator T() override;

//        template<typename T1> friend std::ostream& operator<< (std::ostream &out, const ListElement<T1> &listEL);

        ~ListElement();
    };

    template<typename T>
    ListElement<T>::ListElement(): optional::Optional<T>() {
        this->prevPtr = nullptr;
        this->nextPtr = nullptr;
    }

    template<typename T>
    ListElement<T>::ListElement(T value): optional::Optional<T>(value) {
        this->nextPtr = nullptr;
        this->prevPtr = prevPtr;
    }

    template<typename T>
    ListElement<T>::ListElement(const ListElement<T> &listEl) {
        this->value = listEl.value;
        this->hasValue = listEl.hasValue;
        this->nextPtr = listEl.nextPtr;
        this->prevPtr = listEl.prevPtr;
    }

    template<typename T>
    void ListElement<T>::setValue(T value) {
        this->value = value;
        this->hasValue = true;
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
    T &ListElement<T>::getValue() {
        if (this->hasValue) {
            return this->value;
        } else {
            throw exceptions::ListElementException("Element has not value!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    bool ListElement<T>::checkValue() {
        return this->hasValue;
    }

    template<typename T>
    ListElement<T> &ListElement<T>::operator=(const ListElement<T> &listEl) {
        if (this == &listEl) {
            return *this;
        }
        this->hasValue = listEl.hasValue;
        this->value = listEl.value;
        this->nextPtr = listEl.nextPtr;
        this->prevPtr = listEl.prevPtr;
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
            throw exceptions::ListElementException("Element has not value!", __LINE__, __FILE__);
        }
    }

//    template<typename T1>
//    std::ostream &operator<<(std::ostream &out, const ListElement<T1> &listEl) {
//        if (listEl.hasValue) {
//            out << listEl.value;
//        } else {
//            out << "null";
//        }
//        return out;
//    }

    template<typename T>
    ListElement<T>::~ListElement() = default;
}


#endif

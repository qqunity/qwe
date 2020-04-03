#ifndef COLLECTIONS_ARRAYELEMENT_H
#define COLLECTIONS_ARRAYELEMENT_H

    #include "Exceptions.h"

    template<typename T>
    class ArrayElement {
        private:
            T value;
            bool hasValue;
        public:
            ArrayElement();

            ArrayElement(T);

            ArrayElement(const ArrayElement<T> &);

            void setValue(T);

            T getValue();

            bool checkValue();

            ArrayElement<T> &operator = (const ArrayElement<T> &);

            ArrayElement<T> &operator = (T);

            operator T();

            template<typename T1> friend std::ostream& operator<< (std::ostream &, const ArrayElement<T1> &);

            ~ArrayElement();
    };

    template<typename T>
    ArrayElement<T>::ArrayElement() {
        this->hasValue = false;
    }

    template<typename T>
    ArrayElement<T>::ArrayElement(T val) {
        this->value = val;
        this->hasValue = true;
    }

    template<typename T>
    ArrayElement<T>::ArrayElement(const ArrayElement<T> &ArrEl) {
        this->hasValue = ArrEl.hasValue;
        this->value = ArrEl.value;
    }

    template<typename T>
    void ArrayElement<T>::setValue(T val) {
        this->value = val;
        this->hasValue = true;
    }

    template<typename T>
    T ArrayElement<T>::getValue() {
        if (this->hasValue){
            return this->value;
        }
        else {
            throw arrayException::ArrayElementException("Element has not value!");
        }
    }

    template<typename T>
    bool ArrayElement<T>::checkValue() {
        return this->hasValue;
    }

    template<typename T>
    ArrayElement<T> &ArrayElement<T>::operator=(const ArrayElement<T> &ArrEl) {
        if (this == &ArrEl){
            return *this;
        }
        this->hasValue = ArrEl.hasValue;
        this->value = ArrEl.value;
        return *this;
    }

    template<typename T>
    ArrayElement<T>::operator T() {
        if (this->hasValue){
            return this->value;
        }
        else {
            throw arrayException::ArrayElementException("Element has not value!");
        }
    }

    template<typename T>
    ArrayElement<T> &ArrayElement<T>::operator=(T val) {
        this->value = val;
        this->hasValue = true;
        return *this;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ArrayElement<T1> &ArrEl) {
        out << ArrEl.value;
        return out;
    }

    template<typename T>
    ArrayElement<T>::~ArrayElement() = default;

#endif
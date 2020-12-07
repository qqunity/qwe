#ifndef SORTER_ARRAYELEMENT_HPP
#define SORTER_ARRAYELEMENT_HPP

#include "Optional.hpp"
#include "Exceptions.hpp"

namespace array {
    template<typename T>
    class ArrayElement : public optional::Optional<T>{
    public:
        explicit ArrayElement(T value);

        ArrayElement();

        ArrayElement(const ArrayElement<T> &arrEl);

        void setValue(T value) override;

        T &getValue() override;

        bool checkValue() override;

        ArrayElement<T> &operator=(const ArrayElement<T> &arrEl);

        ArrayElement<T> &operator=(T value);

        operator T() override;

//        template<typename T1> friend std::ostream& operator<< (std::ostream &out, const ArrayElement<T1> &arrEl);

        ~ArrayElement();
    };

    template<typename T>
    ArrayElement<T>::ArrayElement(T value): optional::Optional<T>(value) {}

    template<typename T>
    ArrayElement<T>::ArrayElement(): optional::Optional<T>() {}

    template<typename T>
    ArrayElement<T>::ArrayElement(const ArrayElement<T> &arrEl) {
        this->hasValue = arrEl.hasValue;
        this->value = arrEl.value;
    }

    template<typename T>
    void ArrayElement<T>::setValue(T value) {
        this->value = value;
        this->hasValue = true;
    }

    template<typename T>
    T &ArrayElement<T>::getValue() {
        if (this->hasValue) {
            return this->value;
        } else {
            throw exceptions::ArrayElementException("Element has not value!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    bool ArrayElement<T>::checkValue() {
        return this->hasValue;
    }

    template<typename T>
    ArrayElement<T> &ArrayElement<T>::operator=(const ArrayElement<T> &arrEl) {
        if (this == &arrEl) {
            return *this;
        }
        this->hasValue = arrEl.hasValue;
        this->value = arrEl.value;
        return *this;
    }

    template<typename T>
    ArrayElement<T> &ArrayElement<T>::operator=(T value) {
        this->value = value;
        this->hasValue = true;
        return *this;
    }

    template<typename T>
    ArrayElement<T>::operator T() {
        if (this->hasValue) {
            return this->value;
        } else {
            throw exceptions::ArrayElementException("Element has not value!", __LINE__, __FILE__);
        }
    }

//    template<typename T1>
//    std::ostream &operator<<(std::ostream &out, const ArrayElement<T1> &arrEl) {
//        if (arrEl.hasValue) {
//            out << arrEl.value;
//        } else {
//            out << "null";
//        }
//        return out;
//    }

    template<typename T>
    ArrayElement<T>::~ArrayElement() = default;
}
#endif

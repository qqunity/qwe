#ifndef TIC_TAC_TOE_GAME_OPTIONAL_H
#define TIC_TAC_TOE_GAME_OPTIONAL_H

#include <iostream>
#include "Exception.h"


template<typename T>
class Optional {
private:
    T value;
    bool hasValue{false};
public:
    Optional();

    Optional(T val);

    Optional(const Optional<T> &opt);

    void setValue(T val);

    T &getValue();

    bool checkValue();

    Optional<T> &operator=(const Optional<T> &opt);

    Optional<T> &operator=(T val);

    operator T();

    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, const Optional<T1> &opt);

    ~Optional();
};

template<typename T>
Optional<T>::Optional() {
    this->hasValue = false;
}

template<typename T>
Optional<T>::Optional(T val) {
    this->value = val;
    this->hasValue = true;
}

template<typename T>
Optional<T>::Optional(const Optional<T> &opt) {
    this->hasValue = opt.hasValue;
    this->value = opt.value;
}

template<typename T>
void Optional<T>::setValue(T val) {
    this->value = val;
    this->hasValue = true;
}

template<typename T>
T &Optional<T>::getValue() {
    if (this->hasValue) {
        return this->value;
    } else {
        throw Exception("Element has not value!", __LINE__, __FILE__);
    }
}

template<typename T>
bool Optional<T>::checkValue() {
    return this->hasValue;
}

template<typename T>
Optional<T> &Optional<T>::operator=(const Optional<T> &opt) {
    if (this == &opt) {
        return *this;
    }
    this->hasValue = opt.hasValue;
    this->value = opt.value;
    return *this;
}

template<typename T>
Optional<T>::operator T() {
    if (this->hasValue) {
        return this->value;
    } else {
        throw Exception("Element has not value!", __LINE__, __FILE__);
    }
}

template<typename T>
Optional<T> &Optional<T>::operator=(T val) {
    this->value = val;
    this->hasValue = true;
    return *this;
}

template<typename T1>
std::ostream &operator<<(std::ostream &out, const Optional<T1> &opt) {
    if (opt.hasValue) {
        out << opt.value;
    } else {
        throw Exception("Element has not value!", __LINE__, __FILE__);
    }
    return out;
}

template<typename T>
Optional<T>::~Optional() = default;

#endif

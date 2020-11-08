#ifndef LAB_2_OPT_HPP
#define LAB_2_OPT_HPP

#include "Exceptions.hpp"

namespace optional {
    template<typename T>
    class Opt {
    private:
        T value;
        bool hasValue{false};
    public:
        Opt();

        explicit Opt(T val);

        Opt(const Opt<T> &opt);

        void setValue(T val);

        T &getValue();

        bool checkValue();

        Opt<T> &operator=(const Opt<T> &opt);

        Opt<T> &operator=(T val);

        operator T();

        template<typename T1>
        friend std::ostream &operator<<(std::ostream &out, const Opt<T1> &opt);

        ~Opt();
    };

    template<typename T>
    Opt<T>::Opt() {
        this->hasValue = false;
    }

    template<typename T>
    Opt<T>::Opt(T val) {
        this->value = val;
        this->hasValue = true;
    }

    template<typename T>
    Opt<T>::Opt(const Opt<T> &opt) {
        this->hasValue = opt.hasValue;
        this->value = opt.value;
    }

    template<typename T>
    void Opt<T>::setValue(T val) {
        this->value = val;
        this->hasValue = true;
    }

    template<typename T>
    T &Opt<T>::getValue() {
        if (this->hasValue) {
            return this->value;
        } else {
            throw exceptions::OptException("Element has not value!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    bool Opt<T>::checkValue() {
        return this->hasValue;
    }

    template<typename T>
    Opt<T> &Opt<T>::operator=(const Opt<T> &opt) {
        if (this == &opt) {
            return *this;
        }
        this->hasValue = opt.hasValue;
        this->value = opt.value;
        return *this;
    }

    template<typename T>
    Opt<T>::operator T() {
        if (this->hasValue) {
            return this->value;
        } else {
            throw exceptions::OptException("Element has not value!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    Opt<T> &Opt<T>::operator=(T val) {
        this->value = val;
        this->hasValue = true;
        return *this;
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const Opt<T1> &opt) {
        if (opt.hasValue) {
            out << opt.value;
        } else {
            throw exceptions::OptException("Element has not value!", __LINE__, __FILE__);
        }
        return out;
    }

    template<typename T>
    Opt<T>::~Opt() = default;
}

#endif

#ifndef SORTER_OPTIONAL_HPP
#define SORTER_OPTIONAL_HPP

namespace optional {
    template<typename T>
    class Optional {
    protected:
        T value;
        bool hasValue{};
    public:
        Optional();

        explicit Optional(T value);

        ~Optional();

        virtual void setValue(T value) = 0;

        virtual T &getValue() = 0;

        virtual bool checkValue() = 0;

        virtual operator T() = 0;
    };

    template<typename T>
    Optional<T>::Optional(T value) {
        this->value = value;
        this->hasValue = true;
    }

    template<typename T>
    Optional<T>::Optional() {
        this->hasValue = false;
    }

    template<typename T>
    Optional<T>::~Optional() = default;
}

#endif

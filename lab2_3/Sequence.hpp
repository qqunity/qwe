#ifndef SORTER_SEQUENCE_HPP
#define SORTER_SEQUENCE_HPP

#include "Optional.hpp"

namespace sequence {
    template<typename T>
    class Sequence {
    public:

        Sequence() = default;

        ~Sequence() = default;

        virtual unsigned length() = 0;

        virtual void append(T value) = 0;

        virtual void prepend(T value) = 0;

        virtual void pop(unsigned int index) = 0;

        virtual void remove() = 0;

        virtual void swap(unsigned int index1, unsigned int index2) = 0;

        virtual T &getElement(unsigned int index) = 0;

        virtual int getIndex(T value) = 0;

        virtual optional::Optional<T> *getFirst() = 0;

        virtual optional::Optional<T> *getLast() = 0;

        virtual void insert(unsigned int index, T value) = 0;

        virtual void setElement(unsigned int index, T value) = 0;

        virtual optional::Optional<T> *operator[](unsigned int index) = 0;
    };

}

#endif

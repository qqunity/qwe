#ifndef SORTER_ARRAYSEQUENCE_HPP
#define SORTER_ARRAYSEQUENCE_HPP

#include "Array.hpp"
#include "Sequence.hpp"

namespace array {
    template<typename T>
    class ArraySequence: public sequence::Sequence<T> {
    private:
        Array<T> data;
        unsigned int size;
    public:
        ArraySequence();

        void append(T value) override;

        void prepend(T value) override;

        void pop(unsigned int index) override;

        void swap(unsigned int index1, unsigned int index2) override;

        void remove() override;

        T &getElement(unsigned int index) override;

        int getIndex(T value) override;

        ArrayElement<T> *getFirst() override;

        ArrayElement<T> *getLast() override;

        void insert(unsigned int index, T value) override;

        void setElement(unsigned int index, T value) override;

        ArrayElement<T> *operator[](unsigned int index) override;

        unsigned int length() override;

        typename Array<T>::ArrayIterator begin();

        typename Array<T>::ArrayIterator end();

        template<typename T1>
        friend std::ostream &operator<<(std::ostream &out, const ArraySequence<T1> &arrSeq);
    };

    template<typename T>
    ArraySequence<T>::ArraySequence(): sequence::Sequence<T>() {
        this->size = 0;
    }

    template<typename T>
    void ArraySequence<T>::append(T value) {
        this->data.append(value);
        ++this->size;
    }

    template<typename T>
    void ArraySequence<T>::prepend(T value) {
        this->data.prepend(value);
        ++this->size;
    }

    template<typename T>
    void ArraySequence<T>::pop(unsigned int index) {
        this->data.pop(index);
        --this->size;
    }

    template<typename T>
    void ArraySequence<T>::remove() {
        this->data.remove();
        this->size = 0;
    }

    template<typename T>
    void ArraySequence<T>::swap(unsigned int index1, unsigned int index2) {
        this->data.swap(index1, index2);
    }

    template<typename T>
    T &ArraySequence<T>::getElement(unsigned int index) {
        return this->data.getElement(index);
    }

    template<typename T>
    int ArraySequence<T>::getIndex(T value) {
        return this->data.getIndex(value);
    }

    template<typename T>
    ArrayElement<T> *ArraySequence<T>::getFirst() {
        return this->data.getFirst();
    }

    template<typename T>
    ArrayElement<T> *ArraySequence<T>::getLast() {
        return this->data.getLast();
    }

    template<typename T>
    void ArraySequence<T>::insert(unsigned int index, T value) {
        this->data.insert(index, value);
        ++this->size;
    }

    template<typename T>
    void ArraySequence<T>::setElement(unsigned int index, T value) {
        *this->data[index] = value;
    }

    template<typename T>
    ArrayElement<T> *ArraySequence<T>::operator[](unsigned int index) {
        return this->data[index];
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const ArraySequence<T1> &arrSeq) {
        out << arrSeq.data;
        return out;
    }

    template<typename T>
    unsigned int ArraySequence<T>::length() {
        return this->size;
    }

    template<typename T>
    typename Array<T>::ArrayIterator ArraySequence<T>::begin() {
        return this->data.begin();
    }


    template<typename T>
    typename Array<T>::ArrayIterator ArraySequence<T>::end() {
        return this->data.end();
    }
}


#endif

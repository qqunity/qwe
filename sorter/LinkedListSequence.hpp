#ifndef SORTER_LINKEDLISTSEQUENCE_HPP
#define SORTER_LINKEDLISTSEQUENCE_HPP

#include "LinkedList.hpp"
#include "Sequence.hpp"

namespace list {
    template<typename T>
    class LinkedListSequence: public sequence::Sequence<T> {
    private:
        LinkedList<T> data;
        unsigned int size;
    public:
        LinkedListSequence();

        void append(T value) override;

        void prepend(T value) override;

        void pop(unsigned int index) override;

        void swap(unsigned int index1, unsigned int index2) override;

        void remove() override;

        T &getElement(unsigned int index) override;

        int getIndex(T value) override;

        ListElement<T> *getFirst() override;

        ListElement<T> *getLast() override;

        void insert(unsigned int index, T value) override;

        void setElement(unsigned int index, T value) override;

        ListElement<T> *operator[](unsigned int index) override;

        unsigned int length() override;

        typename LinkedList<T>::LinkedListIterator begin();

        typename LinkedList<T>::LinkedListIterator end();

        template<typename T1>
        friend std::ostream &operator<<(std::ostream &out, const LinkedListSequence<T1> &listSeq);
    };

    template<typename T>
    LinkedListSequence<T>::LinkedListSequence(): sequence::Sequence<T>() {
        this->size = 0;
    }

    template<typename T>
    void LinkedListSequence<T>::append(T value) {
        this->data.append(value);
        ++this->size;
    }

    template<typename T>
    void LinkedListSequence<T>::prepend(T value) {
        this->data.prepend(value);
        ++this->size;
    }

    template<typename T>
    void LinkedListSequence<T>::pop(unsigned int index) {
        this->data.pop(index);
        --this->size;
    }

    template<typename T>
    void LinkedListSequence<T>::swap(unsigned int index1, unsigned int index2) {
        this->data.swap(index1, index2);
    }

    template<typename T>
    void LinkedListSequence<T>::remove() {
        this->data.remove();
        this->size = 0;
    }

    template<typename T>
    T &LinkedListSequence<T>::getElement(unsigned int index) {
        return this->data.getElement(index);
    }

    template<typename T>
    int LinkedListSequence<T>::getIndex(T value) {
        return this->data.getIndex(value);
    }

    template<typename T>
    ListElement<T> *LinkedListSequence<T>::getFirst() {
        return this->data.getFirst();
    }

    template<typename T>
    ListElement<T> *LinkedListSequence<T>::getLast() {
        return this->data.getLast();
    }

    template<typename T>
    void LinkedListSequence<T>::insert(unsigned int index, T value) {
        this->data.insert(index, value);
        ++this->size;
    }

    template<typename T>
    void LinkedListSequence<T>::setElement(unsigned int index, T value) {
        *this->data[index] = value;
    }

    template<typename T>
    ListElement<T> *LinkedListSequence<T>::operator[](unsigned int index) {
        return this->data[index];
    }

    template<typename T>
    unsigned int LinkedListSequence<T>::length() {
        return this->size;
    }

    template<typename T>
    typename LinkedList<T>::LinkedListIterator LinkedListSequence<T>::begin() {
        return this->data.begin();
    }

    template<typename T>
    typename LinkedList<T>::LinkedListIterator LinkedListSequence<T>::end() {
        return this->data.end();
    }

    template<typename T1>
    std::ostream &operator<<(std::ostream &out, const LinkedListSequence<T1> &listSeq) {
        out << listSeq.data;
        return out;
    }
}

#endif

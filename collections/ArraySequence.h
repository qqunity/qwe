#ifndef COLLECTIONS_ARRAYSEQUENCE_H
#define COLLECTIONS_ARRAYSEQUENCE_H

    #include "Array.h"
    #include "Sequence.h"

    namespace arraySequence {
        template<typename T>
        class ArraySequence : public sequence::Sequence<T> {
            private:
                array::Array<T> data;
                int size;
            public:
                ArraySequence();

                void append(T) override;

                void prepend(T) override;

                void pop(int)  override;

                void remove() override;

                void swap(int, int) override;

                T getElement(int) override;

                int getIndex(T) override;

                ArrayElement<T> *getFirst() override;

                ArrayElement<T> *getLast() override;

                void insert(int, T) override;

                void setElement(int, T) override;

                int length() override;

                operator array::Array<T>();

                ~ArraySequence();

                typename array::Array<T>::ArrayIterator begin();

                typename array::Array<T>::ArrayIterator end();

                template<typename T1>
                friend std::ostream &operator<<(std::ostream &, const ArraySequence<T1> &);
        };

        template<typename T>
        ArraySequence<T>::ArraySequence(): sequence::Sequence<T>() {
            this->size = 0;
        }

        template<typename T>
        void ArraySequence<T>::append(T val) {
            this->data.append(val);
            ++this->size;
        }

        template<typename T>
        void ArraySequence<T>::prepend(T val) {
            this->data.prepend(val);
            ++this->size;
        }

        template<typename T>
        void ArraySequence<T>::pop(int index) {
            this->data.pop(index);
            --this->size;
        }

        template<typename T>
        void ArraySequence<T>::remove() {
            this->data.remove();
            this->size = 0;
        }

        template<typename T>
        void ArraySequence<T>::swap(int index1, int index2) {
            this->data.swap(index1, index2);
        }

        template<typename T>
        T ArraySequence<T>::getElement(int index) {
            return this->data[index];
        }

        template<typename T>
        int ArraySequence<T>::getIndex(T val) {
            return this->data.getIndex(val);
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
        void ArraySequence<T>::insert(int index, T val) {
            this->data.insert(index, val);
            ++this->size;
        }

        template<typename T>
        void ArraySequence<T>::setElement(int index, T val) {
            this->data[index] = val;
        }

        template<typename T>
        ArraySequence<T>::operator array::Array<T>() {
            return this->data;
        }

        template<typename T1>
        std::ostream &operator<<(std::ostream &out, const ArraySequence<T1> &ArrS) {
            out << ArrS.data;
            return out;
        }

        template<typename T>
        typename array::Array<T>::ArrayIterator ArraySequence<T>::begin() {
            return this->data.begin();
        }

        template<typename T>
        typename array::Array<T>::ArrayIterator ArraySequence<T>::end() {
            return this->data.end();
        }

        template<typename T>
        int ArraySequence<T>::length() {
            return this->size;
        }

        template<typename T>
        ArraySequence<T>::~ArraySequence() = default;
    }
#endif

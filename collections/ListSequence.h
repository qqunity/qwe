#ifndef COLLECTIONS_LISTSEQUENCE_H
#define COLLECTIONS_LISTSEQUENCE_H

    #include "Sequence.h"
    #include "List.h"

    namespace listSequence {
        template<typename T>
        class ListSequence: public sequence::Sequence<T> {
            private:
                list::List<T> data;
                int size;
            public:
                ListSequence();

                void append(T) override;

                void prepend(T) override;

                void pop(int) override;

                void remove() override;

                void swap(int, int) override;

                int getIndex(T) override;

                T getElement(int) override;

                ListElement<T> *getFirst() override;

                ListElement<T> * getLast() override;

                void insert(int, T) override;

                void setElement(int, T) override;

                int length() override;

                operator list::List<T>();

                typename list::List<T>::ListIterator begin();

                typename list::List<T>::ListIterator end();

                ~ListSequence();

                template<typename T1>
                friend std::ostream &operator<<(std::ostream &, const ListSequence<T1> &);
        };

        template<typename T>
        ListSequence<T>::ListSequence(): sequence::Sequence<T>() {
            this->size = 0;
        }

        template<typename T>
        void ListSequence<T>::append(T val) {
            this->data.append(val);
            ++this->size;
        }

        template<typename T>
        void ListSequence<T>::prepend(T val) {
            this->data.prepend(val);
            ++this->size;
        }

        template<typename T>
        void ListSequence<T>::pop(int index) {
            this->data.pop(index);
            --this->size;
        }

        template<typename T>
        void ListSequence<T>::remove() {
            this->data.remove();
            this->size = 0;
        }

        template<typename T>
        void ListSequence<T>::swap(int index1, int index2) {
            this->data.swap(index1, index2);
        }

        template<typename T>
        T ListSequence<T>::getElement(int index) {
            return this->data[index];
        }

        template<typename T>
        int ListSequence<T>::getIndex(T val) {
            return this->data.getIndex(val);
        }

        template<typename T>
        ListElement<T> *ListSequence<T>::getFirst() {
            return this->data.getFirst();
        }

        template<typename T>
        ListElement<T> *ListSequence<T>::getLast() {
            return this->data.getLast();
        }

        template<typename T>
        void ListSequence<T>::insert(int index, T val) {
            this->data.insert(index, val);
            ++this->size;
        }

        template<typename T>
        void ListSequence<T>::setElement(int index, T val) {
            this->data[index] = val;
        }

        template<typename T>
        ListSequence<T>::operator list::List<T>() {
            return this->data;
        }

        template<typename T1>
        std::ostream &operator<<(std::ostream &out, const ListSequence <T1> &LstSeq) {
            out << LstSeq.data;
            return out;
        }

        template<typename T>
        typename list::List<T>::ListIterator ListSequence<T>::begin() {
            return this->data.begin();
        }

        template<typename T>
        typename list::List<T>::ListIterator ListSequence<T>::end() {
            return this->data.end();
        }

        template<typename T>
        int ListSequence<T>::length() {
            return this->size;
        }

        template<typename T>
        ListSequence<T>::~ListSequence() = default;


    }
#endif

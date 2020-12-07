#ifndef LAB_2_SPARSEVECTOR_HPP
#define LAB_2_SPARSEVECTOR_HPP

#include <string>
#include "IDictionary.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "SequenceIterator.hpp"
#include "Array.hpp"
#include "Pair.hpp"
#include "BTreeDictionary.hpp"
#include "AVLTreeDictionary.hpp"
#include "Exceptions.hpp"

namespace vector {
    template<typename T>
    class SparseVector {
    private:
        unsigned int size;
        std::string baseTypeOfDictionary;
        std::string baseTypeOfSequence;
        dictionary::IDictionary<int, T> *data;
        int usedIndex;
        T defaultValue;
        sequence::SequenceIterator<T> *items;
    private:
        void resetUsedIndex();

        void refreshItems();
    public:
        SparseVector(std::string baseTypeOfDictionary, std::string baseTypeOfSequence, T defaultValue);

        SparseVector(T *mas, unsigned int size, std::string baseTypeOfDictionary, std::string baseTypeOfSequence, T defaultValue);

        SparseVector(const SparseVector<T> &vector);

        void append(T value);

        void prepend(T value);

        void pop(unsigned int index);

        void remove();

        void swap(unsigned int index1, unsigned int index2);

        T &getElement(unsigned int index);

        T& operator[](unsigned int index);

        unsigned int length();

        void insert(unsigned int index, T value);

        std::string representation();

        typename array::Array<T>::ArrayIterator begin();

        typename array::Array<T>::ArrayIterator end();

        ~SparseVector();
    };

    template<typename T>
    SparseVector<T>::SparseVector(std::string baseTypeOfDictionary, std::string baseTypeOfSequence, T defaultValue) {
        this->size = 0;
        this->usedIndex = -1;
        this->baseTypeOfDictionary = baseTypeOfDictionary;
        this->baseTypeOfSequence = baseTypeOfSequence;
        this->defaultValue = defaultValue;
        if (this->baseTypeOfDictionary == "BTreeDictionary") {
            this->data = new dictionary::BTreeDictionary<int, T>(2, this->baseTypeOfSequence, -1, this->defaultValue);
        } else if (this->baseTypeOfSequence == "AVLTreeDictionary") {
            this->data = new dictionary::AVLTreeDictionary<int, T>(this->baseTypeOfSequence, -1, this->defaultValue);
        } else {
            throw exceptions::SparseVectorException("Invalid dictionary type!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    SparseVector<T>::SparseVector(T *mas, unsigned int size, std::string baseTypeOfDictionary, std::string baseTypeOfSequence, T defaultValue) {
        this->size = 0;
        this->usedIndex = -1;
        this->baseTypeOfDictionary = baseTypeOfDictionary;
        this->baseTypeOfSequence = baseTypeOfSequence;
        this->defaultValue = defaultValue;
        if (this->baseTypeOfDictionary == "BTreeDictionary") {
            this->data = new dictionary::BTreeDictionary<int, T>(2, this->baseTypeOfSequence, -1, this->defaultValue);
        } else if (this->baseTypeOfSequence == "AVLTreeDictionary") {
            this->data = new dictionary::AVLTreeDictionary<int, T>(this->baseTypeOfSequence, -1, this->defaultValue);
        } else {
            throw exceptions::SparseVectorException("Invalid dictionary type!", __LINE__, __FILE__);
        }
        for (unsigned int i = 0; i < size; ++i) {
            this->append(mas[i]);
        }
    }

    template<typename T>
    void SparseVector<T>::append(T value) {
        this->resetUsedIndex();
        if (value != this->defaultValue) {
            this->data->insert(this->size, value);
        }
        ++this->size;
    }

    template<typename T>
    std::string SparseVector<T>::representation() {
        this->resetUsedIndex();
        std::string representation;
        if (this->size != 0) {
            representation += "[";
            for (unsigned int i = 0; i < this->size; ++i) {
                if (i == this->size - 1) {
                    if (this->data->contains(i)) {
                        representation += std::to_string(this->data->get(i).getValue()) + "]";
                    } else {
                        representation += std::to_string(this->defaultValue) + "]";
                    }
                } else {
                    if (this->data->contains(i)) {
                        representation += std::to_string(this->data->get(i).getValue()) + ", ";
                    } else {
                        representation += std::to_string(this->defaultValue) + ", ";
                    }
                }
            }
        } else {
            representation = "[]";
        }
        return representation;
    }

    template<typename T>
    SparseVector<T>::SparseVector(const SparseVector<T> &vector) {
        this->defaultValue = vector.defaultValue;
        this->size = 0;
        this->usedIndex = vector.usedIndex;
        this->baseTypeOfSequence = vector.baseTypeOfSequence;
        this->baseTypeOfDictionary = vector.baseTypeOfDictionary;
        if (this->baseTypeOfDictionary == "BTreeDictionary") {
            this->data = new dictionary::BTreeDictionary<int, T>(2, this->baseTypeOfSequence, -1, this->defaultValue);
        } else if (this->baseTypeOfSequence == "AVLTreeDictionary") {
            this->data = new dictionary::AVLTreeDictionary<int, T>(this->baseTypeOfSequence, -1, this->defaultValue);
        } else {
            throw exceptions::SparseVectorException("Invalid dictionary type!", __LINE__, __FILE__);
        }
        for (unsigned int i = 0; i < vector.size; ++i) {
            if (vector.data->contains(i)) {
                this->append(vector.data->get(i).getValue());
            } else {
                this->append(this->defaultValue);
            }
        }
        this->resetUsedIndex();
    }

    template<typename T>
    void SparseVector<T>::prepend(T value) {
        this->resetUsedIndex();
        array::ArraySequence<Pair<int, T>> arr;
        for (unsigned int i = 0; i < this->size; ++i) {
            if (this->data->contains(i)){
                arr.append(Pair<int, T>(std::make_pair(i + 1, this->data->get(i).getValue())));
                this->data->remove(i);
            }
        }
        for (auto p: arr) {
            this->data->insert(p.getValue().getFirst(), p.getValue().getSecond());
        }
        if (value != this->defaultValue){
            this->data->insert(0, value);
        }
        ++this->size;
    }

    template<typename T>
    void SparseVector<T>::pop(unsigned int index) {
        if (index >= 0 && index < this->size) {
            this->resetUsedIndex();
            array::ArraySequence<Pair<int, T>> arr;
            for (unsigned int i = index + 1; i < this->size; ++i) {
                if (this->data->contains(i)) {
                    arr.append(Pair<int, T>(std::make_pair(i - 1, this->data->get(i).getValue())));
                    this->data->remove(i);
                }
            }
            if (this->data->contains(index)) {
                this->data->remove(index);
            }
            for (auto p: arr) {
                this->data->insert(p.getValue().getFirst(), p.getValue().getSecond());
            }
            --this->size;
        } else {
            throw exceptions::SparseVectorException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    void SparseVector<T>::remove() {
        this->resetUsedIndex();
        for (auto key: this->data->keys()) {
            this->data->remove(key.getValue());
        }
        this->size = 0;
    }

    template<typename T>
    void SparseVector<T>::swap(unsigned int index1, unsigned int index2) {
        if (index1 >= 0 && index1 < this->size && index2 >= 0 && index2 < this->size) {
            this->resetUsedIndex();
            if (this->data->contains(index1) && this->data->contains(index2)) {
                auto buff1 = this->data->get(index1).getValue();
                auto buff2 = this->data->get(index2).getValue();
                this->data->remove(index1);
                this->data->remove(index2);
                this->data->insert(index1, buff2);
                this->data->insert(index2, buff1);
            } else if (this->data->contains(index1) && !this->data->contains(index2)) {
                auto buff1 = this->data->get(index1).getValue();
                this->data->remove(index1);
                this->data->insert(index2, buff1);
            } else if (!this->data->contains(index1) && this->data->contains(index2)) {
                auto buff2 = this->data->get(index2).getValue();
                this->data->remove(index2);
                this->data->insert(index1, buff2);
            }
        } else {
            throw exceptions::SparseVectorException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    T &SparseVector<T>::getElement(unsigned int index) {
        if (index >= 0 && index < this->size) {
            this->resetUsedIndex();
            if (!this->data->contains(index)) {
                this->data->insert(index, this->defaultValue);
                this->usedIndex = index;
            }
            return this->data->get(index).getValue();
        } else {
            throw exceptions::SparseVectorException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    void SparseVector<T>::resetUsedIndex() {
        if (this->usedIndex != -1) {
            if (this->data->get(this->usedIndex).getValue() == this->defaultValue) {
                this->data->remove(this->usedIndex);
            }
            this->usedIndex = -1;
        }
    }

    template<typename T>
    unsigned int SparseVector<T>::length() {
        this->resetUsedIndex();
        return this->size;
    }

    template<typename T>
    void SparseVector<T>::insert(unsigned int index, T value) {
        if (index >= 0 && index <= this->size) {
            this->resetUsedIndex();
            array::ArraySequence<Pair<int, T>> arr;
            for (unsigned int i = index; i < this->size; ++i) {
                if (this->data->contains(i)) {
                    arr.append(Pair<int, T>(std::make_pair(i + 1, this->data->get(i).getValue())));
                    this->data->remove(i);
                }
            }
            for (auto p: arr) {
                this->data->insert(p.getValue().getFirst(), p.getValue().getSecond());
            }
            if (value != this->defaultValue) {
                this->data->insert(index, value);
            }
            ++this->size;
        } else {
            throw exceptions::SparseVectorException("Index out of range!", __LINE__, __FILE__);
        }
    }

    template<typename T>
    T &SparseVector<T>::operator[](unsigned int index) {
        return this->getElement(index);
    }

    template<typename T>
    SparseVector<T>::~SparseVector() {
        this->remove();
    }

    template<typename T>
    typename array::Array<T>::ArrayIterator SparseVector<T>::begin() {
        this->resetUsedIndex();
        this->refreshItems();
        return this->items->begin();
    }

    template<typename T>
    void SparseVector<T>::refreshItems() {
        sequence::Sequence<T> *seq;
        if (this->baseTypeOfSequence == "ArraySequence") {
            seq = new array::ArraySequence<T>();
        } else {
            seq = new list::LinkedListSequence<T>();
        }
        for (unsigned int i = 0; i < this->size; ++i) {
            if (this->data->contains(i)) {
                seq->append(this->data->get(i).getValue());
            } else {
                seq->append(this->defaultValue);
            }
        }
        this->items = new sequence::SequenceIterator<T>(seq);
    }

    template<typename T>
    typename array::Array<T>::ArrayIterator SparseVector<T>::end() {
        return this->items->end();
    }
}

#endif

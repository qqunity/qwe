#ifndef LAB_2_SEQUENCEITERATOR_HPP
#define LAB_2_SEQUENCEITERATOR_HPP

#include "Sequence.hpp"
#include "Array.hpp"

namespace sequence {
    template<typename T>
    class SequenceIterator {
    private:
        Sequence<T> *sequence;
        array::Array<T> arr;
    public:
        SequenceIterator(Sequence<T> *seq);

        typename array::Array<T>::ArrayIterator begin();

        typename array::Array<T>::ArrayIterator end();

        ~SequenceIterator();
    };

    template<typename T>
    SequenceIterator<T>::SequenceIterator(Sequence<T> *seq) {
        this->sequence = seq;
        for (unsigned int i = 0; i < this->sequence->length(); ++i) {
            this->arr.append((*this->sequence)[i]->getValue());
        }
    }

    template<typename T>
    typename array::Array<T>::ArrayIterator SequenceIterator<T>::begin() {
        return this->arr.begin();
    }

    template<typename T>
    typename array::Array<T>::ArrayIterator SequenceIterator<T>::end() {
        return this->arr.end();
    }


    template<typename T>
    SequenceIterator<T>::~SequenceIterator() = default;
}


#endif

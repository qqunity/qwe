#ifndef SORTER_ISORTER_HPP
#define SORTER_ISORTER_HPP

#include "Sequence.hpp"
#include "iostream"

namespace sorter {
    template<typename T>
    class ISorter {
    protected:
        unsigned int cntIterations{};
        unsigned int numberOfIterationMilliseconds{};
    public:
        ISorter();

        void shuffle(sequence::Sequence<T> *seq, unsigned int (*randomFunc)(unsigned int i));

        virtual sequence::Sequence<T> *sort(sequence::Sequence<T> *seq, bool (*cmp) (T value1, T value2)) = 0;

        unsigned int getCntIterations();

        unsigned int getNumberOfIterationSeconds();

        void resetMetrics();

        ~ISorter() = default;
    };

    template<typename T>
    void ISorter<T>::shuffle(sequence::Sequence<T> *seq, unsigned int (*randomFunc)(unsigned int i)) {
        for (unsigned int i = seq->length() - 1; i > 0; --i) {
            seq->swap(i, randomFunc(i));
        }
    }

    template<typename T>
    ISorter<T>::ISorter() {
        this->cntIterations = 0;
        this->numberOfIterationMilliseconds = 0;
    }

    template<typename T>
    unsigned int ISorter<T>::getCntIterations() {
        return this->cntIterations;
    }

    template<typename T>
    unsigned int ISorter<T>::getNumberOfIterationSeconds() {
        return this->numberOfIterationMilliseconds;
    }

    template<typename T>
    void ISorter<T>::resetMetrics() {
        this->cntIterations = 0;
        this->numberOfIterationMilliseconds = 0;
    }

}
#endif

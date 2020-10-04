#ifndef SORTER_ISORTER_HPP
#define SORTER_ISORTER_HPP

#include "Sequence.hpp"
#include "iostream"
#include <string>
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"

namespace sorter {
    template<typename T>
    class ISorter {
    protected:
        unsigned int cntIterations{};
        unsigned int numberOfIterationMilliseconds{};
    public:
        ISorter();

        void shuffle(sequence::Sequence<T> *seq, unsigned int (*randomFunc)(unsigned int i));

        sequence::Sequence<T> *getRandomSequence(sequence::Sequence<T> *seq, T (*randomFunc)(unsigned int i), unsigned int size);

        virtual sequence::Sequence<T> *sort(sequence::Sequence<T> *seq, bool (*cmp) (T value1, T value2)) = 0;

        unsigned int getCntIterations();

        unsigned int getNumberOfIterationMilliseconds();

        virtual void writeMetricsInFile(unsigned int startNumberOfElems, unsigned int endNumberOfElems, unsigned int step, std::string filePath) = 0;

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
    unsigned int ISorter<T>::getNumberOfIterationMilliseconds() {
        return this->numberOfIterationMilliseconds;
    }

    template<typename T>
    void ISorter<T>::resetMetrics() {
        this->cntIterations = 0;
        this->numberOfIterationMilliseconds = 0;
    }

    template<typename T>
    sequence::Sequence<T> *
    ISorter<T>::getRandomSequence(sequence::Sequence<T> *seq, T (*randomFunc)(unsigned int), unsigned int size) {
        for (unsigned int i = 0; i < size; ++i) {
            seq->append(randomFunc(i));
        }
        return seq;
    }


}
#endif

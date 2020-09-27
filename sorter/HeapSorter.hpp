#ifndef SORTER_HEAPSORTER_HPP
#define SORTER_HEAPSORTER_HPP

#include "ISorter.hpp"
#include <chrono>

namespace sorter {

    template<typename T>
    class HeapSorter: public ISorter<T> {
    public:
        HeapSorter();

        void heapify(sequence::Sequence<T> *seq, unsigned int n, unsigned int index, bool (*cmp) (T value1, T value2));

        sequence::Sequence<T> *sort(sequence::Sequence<T> *seq, bool (*cmp) (T value1, T value2)) override;

        ~HeapSorter();
    };

    template<typename T>
    void HeapSorter<T>::heapify(sequence::Sequence<T> *seq, unsigned int n, unsigned int index, bool (*cmp)(T value1, T value2)) {
        ++this->cntIterations;

        unsigned int largest = index;
        unsigned int l = 2 * index + 1;
        unsigned int r = 2 * index + 2;

        if (l < n && cmp((*seq)[l]->getValue(), (*seq)[largest]->getValue())) {
            largest = l;
        }

        if (r < n && cmp((*seq)[r]->getValue(), (*seq)[largest]->getValue())) {
            largest = r;
        }

        if (largest != index) {
            seq->swap(index, largest);
            this->heapify(seq, n, largest, cmp);
        }

    }

    template<typename T>
    sequence::Sequence<T> *HeapSorter<T>::sort(sequence::Sequence<T> *seq, bool (*cmp)(T, T)) {
        auto startTime = std::chrono::system_clock::now();
        for (int i = (seq->length() / 2) - 1; i >= 0; --i) {
            this->heapify(seq, seq->length(), i, cmp);
        }
        for (int i = seq->length() - 1; i >= 0; --i) {
            seq->swap(0, i);
            this->heapify(seq, i, 0, cmp);
        }
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> elapsedMilliseconds = endTime - startTime;
        this->numberOfIterationMilliseconds = elapsedMilliseconds.count();
        return seq;
    }

    template<typename T>
    HeapSorter<T>::HeapSorter(): ISorter<T>() {}

    template<typename T>
    HeapSorter<T>::~HeapSorter() = default;
}

#endif

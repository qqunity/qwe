#ifndef SORTER_QUICKSORTER_HPP
#define SORTER_QUICKSORTER_HPP

#include "ISorter.hpp"
#include <chrono>
#include <fstream>
#include <iostream>

namespace sorter {
    template <typename T>
    class QuickSorter: public ISorter<T> {
    public:
        QuickSorter();

        void quickSort(sequence::Sequence<T> *seq, int first, int last, bool (*cmp) (T value1, T value2));

        sequence::Sequence<T> *sort(sequence::Sequence<T> *seq, bool (*cmp) (T value1, T value2)) override;

        void writeMetricsInFile(unsigned int startNumberOfElems, unsigned int endNumberOfElems, unsigned int step, std::string filePath) override;

        ~QuickSorter();
    };

    template<typename T>
    QuickSorter<T>::QuickSorter(): ISorter<T>() {}

    template<typename T>
    sequence::Sequence<T> *QuickSorter<T>::sort(sequence::Sequence<T> *seq, bool (*cmp)(T, T)) {
        auto startTime = std::chrono::system_clock::now();
        this->quickSort(seq, 0, seq->length() - 1, cmp);
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> elapsedMilliseconds = endTime - startTime;
        this->numberOfIterationMilliseconds = elapsedMilliseconds.count();
        return seq;
    }

    template<typename T>
    void QuickSorter<T>::quickSort(sequence::Sequence<T> *seq, int first, int last, bool (*cmp) (T value1, T value2)) {
        ++this->cntIterations;
        int f = first, l = last;
        auto mid = (*seq)[(f+l) / 2]->getValue();
        do {
            while ((*seq)[f]->getValue() != mid && !cmp((*seq)[f]->getValue(), mid)) {
                f++;
                ++this->cntIterations;
            }
            while (cmp((*seq)[l]->getValue(), mid)) {
                l--;
                ++this->cntIterations;
            }
            if (f <= l){
                seq->swap(f, l);
                f++;
                l--;
            }
            ++this->cntIterations;
        } while (f < l);
        if (first < l) {
            this->quickSort(seq, first, l, cmp);
        }
        if (f < last) {
            this->quickSort(seq, f, last, cmp);
        }
    }

    template<typename T>
    void QuickSorter<T>::writeMetricsInFile(unsigned int startNumberOfElems, unsigned int endNumberOfElems,
                                            unsigned int step, std::string filePath) {
        std::ofstream out;
        out.open(filePath);
        if (out.is_open()) {
            out << "LinkedList metrics:\n";
            for (unsigned int size = startNumberOfElems; size < endNumberOfElems; size += step) {
                this->resetMetrics();
                list::LinkedListSequence<unsigned int> a;
                list::LinkedListSequence<unsigned int> b;
                this->getRandomSequence(&a, [](unsigned int i) {
                    return std::rand() % 100000 + i;
                }, size);
                b = a;
                this->sort(&a, [](unsigned int a, unsigned int b) {
                    return a < b;
                });
                out << "ASC" << "\tsize: " << size << "\tcntIter: " << this->getCntIterations() << "\tcntMilliseconds: " << this->getNumberOfIterationMilliseconds() << '\n';
                this->resetMetrics();
                this->sort(&a, [](unsigned int a, unsigned int b) {
                    return a > b;
                });
                out << "DESC" << "\tsize: " << size << "\tcntIter: " << this->getCntIterations() << "\tcntMilliseconds: " << this->getNumberOfIterationMilliseconds() << '\n';
            }
            out << "Array metrics:\n";
            for (unsigned int size = startNumberOfElems; size < endNumberOfElems; size += step) {
                this->resetMetrics();
                array::ArraySequence<unsigned int> a;
                array::ArraySequence<unsigned int> b;
                this->getRandomSequence(&a, [](unsigned int i) {
                    return std::rand() % 100000 + i;
                }, size);
                b = a;
                this->sort(&a, [](unsigned int a, unsigned int b) {
                    return a < b;
                });
                out << "ASC" << "\tsize: " << size << "\tcntIter: " << this->getCntIterations() << "\tcntMilliseconds: " << this->getNumberOfIterationMilliseconds() << '\n';
                this->resetMetrics();
                this->sort(&a, [](unsigned int a, unsigned int b) {
                    return a > b;
                });
                out << "DESC" << "\tsize: " << size << "\tcntIter: " << this->getCntIterations() << "\tcntMilliseconds: " << this->getNumberOfIterationMilliseconds() << '\n';
            }
        }
    }

    template<typename T>
    QuickSorter<T>::~QuickSorter() = default;
}
#endif

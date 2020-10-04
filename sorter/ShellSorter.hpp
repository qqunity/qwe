#ifndef SORTER_SHELLSORTER_HPP
#define SORTER_SHELLSORTER_HPP
#include "ISorter.hpp"
#include <chrono>

namespace sorter {
    template<typename T>
    class ShellSorter: public ISorter<T> {
    public:
        ShellSorter();

        sequence::Sequence<T> *sort(sequence::Sequence<T> *seq, bool (*cmp) (T value1, T value2)) override;

        void writeMetricsInFile(unsigned int startNumberOfElems, unsigned int endNumberOfElems, unsigned int step, std::string filePath) override;

        ~ShellSorter();
    };

    template<typename T>
    ShellSorter<T>::ShellSorter(): ISorter<T>() {}

    template<typename T>
    sequence::Sequence<T> *ShellSorter<T>::sort(sequence::Sequence<T> *seq, bool (*cmp)(T, T)) {
        auto startTime = std::chrono::system_clock::now();
        int n = seq->length();
        int i, j, step;
        int tmp;
        for (step = n / 2; step > 0; step /= 2) {
            for (i = step; i < n; ++i) {
                auto tmp = (*seq)[i]->getValue();
                for (j = i; j >= step; j -= step) {
                    if (!cmp(tmp, (*seq)[j - step]->getValue())) {
                        (*seq)[j]->setValue((*seq)[j - step]->getValue());
                    }
                    else {
                        break;
                    }
                    ++this->cntIterations;
                }
                (*seq)[j]->setValue(tmp);
                ++this->cntIterations;
            }
            ++this->cntIterations;
        }
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> elapsedMilliseconds = endTime - startTime;
        this->numberOfIterationMilliseconds = elapsedMilliseconds.count();
        return seq;
    }

    template<typename T>
    void ShellSorter<T>::writeMetricsInFile(unsigned int startNumberOfElems, unsigned int endNumberOfElems,
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
    ShellSorter<T>::~ShellSorter() = default;
}
#endif
#ifndef SORTER_UTILS_HPP
#define SORTER_UTILS_HPP

namespace utils {
    template<typename InputIterator, typename Function>
    void map(InputIterator firstIt, InputIterator lastIt, Function function) {
        while (firstIt != lastIt) {
            function(*firstIt);
            ++firstIt;
        }
    }

    template<typename SeqType, typename InputIterator, typename Function>
    SeqType where(InputIterator firstIt, InputIterator lastIt, Function function) {
        SeqType subSeq;
        while (firstIt != lastIt) {
            if (function(*firstIt)) {
                subSeq.append(*firstIt);
            }
            ++firstIt;
        }
        return subSeq;
    }

    template<typename T, typename InputIterator, typename Function>
    T reduce(InputIterator firstIt, InputIterator lastIt, T c, Function function) {
        T buff = function(*firstIt, c);
        ++firstIt;
        while (firstIt != lastIt) {
            buff = function(*firstIt, buff);
            ++firstIt;
        }
        return buff;
    }

    template<typename InputIterator, typename Function>
    void reverse(InputIterator firstIt, InputIterator lastIt, Function swapFunction) {
        InputIterator it1 = firstIt;
        InputIterator it2 = firstIt;
        while (it1 != lastIt) {
            ++it1;
            if (it1 != lastIt) {
                ++it2;
            }
        }
        it1 = firstIt;
        int n = (lastIt - firstIt) / 2;
        int i = 0;
        while (it1 != it2 && i < n) {
            swapFunction(*it1, *it2);
            ++it1;
            --it2;
            ++i;
        }
    }
}

#endif

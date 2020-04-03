
#ifndef COLLECTIONS_UTILS_H
#define COLLECTIONS_UTILS_H
    #include "BinaryHeap.h"
    #include "Sequence.h"
    #include "Array.h"
    #include "List.h"
    #include <cstdarg>
    #include <algorithm>

    namespace utils {
        template<typename SeqType, typename T, typename InputIterator, typename Function>
        SeqType sorted(InputIterator firstIt, InputIterator lastIt, Function ratioFunction) {
            array::Array<T> BuffArray;
            while (firstIt != lastIt) {
                BuffArray.append(*firstIt);
                ++firstIt;
            }
            binaryHeap::BinaryHeap<T> BinHeap(BuffArray, ratioFunction);
            SeqType SortedSeq;
            for (int i = 0; i < BuffArray.length(); ++i) {
                SortedSeq.append(BinHeap.extractMin(ratioFunction));
            }
            return SortedSeq;
        }

        template<typename InputIterator, typename Function>
        void map(InputIterator firstIt, InputIterator lastIt, Function function) {
            while (firstIt != lastIt) {
                function(*firstIt);
                ++firstIt;
            }
        }

        template<typename SeqType, typename InputIterator, typename Function>
        SeqType where(InputIterator firstIt, InputIterator lastIt, Function function) {
            SeqType SubSeq;
            while (firstIt != lastIt) {
                if (function(*firstIt)) {
                    SubSeq.append(*firstIt);
                }
                ++firstIt;
            }
            return SubSeq;
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

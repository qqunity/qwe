
#ifndef COLLECTIONS_UTILS_H
#define COLLECTIONS_UTILS_H
    #include "BinaryHeap.h"

    template<typename SeqType, typename T, typename InputIterator, typename Function>
    SeqType sorted(InputIterator firstIt, InputIterator lastIt, Function ratioFunction) {
        Array<T> BuffArray;
        while (firstIt != lastIt) {
            BuffArray.append(*firstIt);
            ++firstIt;
        }
        BinaryHeap<T> BinHeap(BuffArray, ratioFunction);
        SeqType SortedSeq;
        for (int i = 0; i < BuffArray.length(); ++i) {
            SortedSeq.append(BinHeap.extractMin(ratioFunction));
        }
        return SortedSeq;
    }

    template<typename InputIterator, typename Function>
    void map(InputIterator firstIt, InputIterator lastIt, Function function) {
        while (firstIt != lastIt){
            function(*firstIt);
            ++firstIt;
        }
    }

    template<typename SeqType, typename InputIterator, typename Function>
    SeqType where(InputIterator firstIt, InputIterator lastIt, Function function) {
        SeqType SubSeq;
        while (firstIt != lastIt){
            if (function(*firstIt)) {
                SubSeq.append(*firstIt);
            }
            ++firstIt;
        }
        return SubSeq;
    }

    template<typename T, typename InputIterator, typename Function>
    T reduce(InputIterator firstIt, InputIterator lastIt, T c,  Function function) {
        T buff = function(*firstIt, c);
        ++firstIt;
        while (firstIt != lastIt){
            buff = function(*firstIt, buff);
            ++firstIt;
        }
        return buff;
    }



#endif

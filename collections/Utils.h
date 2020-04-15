
#ifndef COLLECTIONS_UTILS_H
#define COLLECTIONS_UTILS_H
    #include "BinaryHeap.h"
    #include "Sequence.h"
    #include "Array.h"
    #include "List.h"
    #include <cstdarg>
    #include <algorithm>
    #include "Exceptions.h"

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

        template<typename seqType, typename InputIterator>
        seqType getSubSequence(InputIterator firstIt, InputIterator lastIt, int index1, int index2) {
            if (index1 >= 0 && index1 < (lastIt - firstIt) && index2 >=0 && index2 < (lastIt - firstIt)) {
                int i = 0;
                if (index2 < index1) {
                    int buff = index1;
                    index1 = index2;
                    index2 = buff;
                }
                seqType subSeq;
                while (firstIt != lastIt) {
                    if (i >= index1 && i <= index2) {
                        subSeq.append(*firstIt);
                    }
                    ++firstIt;
                    ++i;
                }
                return subSeq;
            }
            else {
                throw utilsException::UtilsException("Index out of range!");
            }
        }

        template<typename InputIteratorSeq, typename subSeqType>
        int getIndexOfSubseq(InputIteratorSeq firstItSeq, InputIteratorSeq lastItSeq, subSeqType subSeq) {
            if (subSeq.length() <= (lastItSeq - firstItSeq)) {
                int i = 0;
                int j = 0;
                InputIteratorSeq buffItSeq(nullptr);
                bool flag;
                while (firstItSeq != lastItSeq && (lastItSeq - firstItSeq) >= subSeq.length()) {
                    buffItSeq = firstItSeq;
                    j = 0;
                    flag = true;
                    while (j < subSeq.length()) {
                        if (subSeq[j] != *buffItSeq) {
                            flag = false;
                            break;
                        }
                        ++buffItSeq;
                        ++j;
                    }
                    if (flag) {
                        return i;
                    }
                    ++firstItSeq;
                    ++i;
                }
                return -1;
            }
            else {
                throw utilsException::UtilsException("It is not possible to compare sequence of different lengths!");
            }
        }

        template<typename T, typename InputIterator>
        list::List<list::List<T>> splitByLabel(InputIterator firstItSeq, InputIterator lastItSeq, T param){
            list::List<list::List<T>> splitSeq;
            list::List<T> buffSeq;
            while (firstItSeq != lastItSeq) {
                if (*firstItSeq == param) {
                    splitSeq.append(buffSeq);
                    buffSeq.remove();
                }
                else {
                    buffSeq.append(*firstItSeq);
                }
                ++firstItSeq;
            }
            splitSeq.append(buffSeq);
            return splitSeq;
        }
    }

#endif

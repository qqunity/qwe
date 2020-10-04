#ifndef SORTER_BASETESTS_HPP
#define SORTER_BASETESTS_HPP
#include "UnitTests.hpp"
#include "LinkedList.hpp"
#include "Array.hpp"

namespace unitTests{
    bool testListAppend() {
        list::LinkedList<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        for (int i = 0; i < 7; ++i){
            if (*l[i] != i){
                return false;
            }
        }
        return true;
    }

    bool testListPrepend() {
        list::LinkedList<int> l;
        for (int i = 0; i < 7; ++i){
            l.prepend(i);
        }
        int j = 6;
        for (int i = 0; i < 7; ++i){
            if (*l[i] != j){
                return false;
            }
            --j;
        }
        return true;
    }

    bool testListSwap() {
        list::LinkedList<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.swap(2, 5);
        return (*l[2] == 5) && (*l[5] == 2);
    }

    bool testListSwapNegative() {
        list::LinkedList<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.swap(2, 55);
        return (*l[2] == 5) && (*l[5] == 2);
    }

    bool testListInsert() {
        list::LinkedList<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.insert(6, 77);
        return *l[6] == 77;
    }

    bool testArrayPop() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        a.pop(0);
        return *a[0] != 0;
    }

    bool testArrayRemove() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        a.remove();
        return a.length() == 0;
    }

    bool testArrayConcat() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        array::Array<int> b;
        for (int i = 7; i < 11; ++i){
            b.append(i);
        }
        array::Array<int> c = a + b;
        for (int i = 0; i < 11; ++i){
            if (*c[i] != i) {
                return false;
            }
        }
        return true;
    }

    bool testArrayGetElementNegative() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        return *a[77] == 11;
    }

    bool testArrayResizeNegative() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        a.resize(2);
        return *a[0] == 0;
    }

    void startBaseTests() {
        UnitTests<bool (*)()> tests;
        tests.addTest(testListAppend, "ListAppend", false);
        tests.addTest(testListPrepend, "ListPrepend", false);
        tests.addTest(testListSwap, "ListSwap", false);
        tests.addTest(testListSwapNegative, "ListSwapNegative", true);
        tests.addTest(testListInsert, "ListInsert", false);
        tests.addTest(testArrayPop, "ArrayPop", false);
        tests.addTest(testArrayRemove, "ArrayRemove", false);
        tests.addTest(testArrayConcat, "ArrayConcat", false);
        tests.addTest(testArrayGetElementNegative, "ArrayGetElementNegative", true);
        tests.addTest(testArrayResizeNegative, "ArrayResizeNegative", true);
        tests.startTests();
    }
}
#endif

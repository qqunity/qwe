#ifndef COLLECTIONS_BASETEST_H
#define COLLECTIONS_BASETEST_H
    #include "UnitTests.h"
    #include "List.h"
    #include "Array.h"

    bool testListAppend() {
        list::List<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        for (int i = 0; i < 7; ++i){
            if (l[i] != i){
                return false;
            }
        }
        return true;
    }

    bool testListPrepend() {
        list::List<int> l;
        for (int i = 0; i < 7; ++i){
            l.prepend(i);
        }
        int j = 6;
        for (int i = 0; i < 7; ++i){
            if (l[i] != j){
                return false;
            }
            --j;
        }
        return true;
    }

    bool testListSwap() {
        list::List<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.swap(2, 5);
        return (l[2] == 5) && (l[5] == 2);
    }

    bool testListSwapNegative() {
        list::List<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.swap(2, 55);
        return (l[2] == 5) && (l[5] == 2);
    }

    bool testListInsert() {
        list::List<int> l;
        for (int i = 0; i < 7; ++i){
            l.append(i);
        }
        l.insert(6, 77);
        return l[6] == 77;
    }

    bool testArrayPop() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        a.pop(0);
        return a[0] != 0;
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
            if (c[i] != i) {
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
        return a[77] == 11;
    }

    bool testArrayResizeNegative() {
        array::Array<int> a;
        for (int i = 0; i < 7; ++i){
            a.append(i);
        }
        a.resize(2);
        return a[0] == 0;
    }

    void startBaseTest() {
        unitTests::UnitTests<bool (*)()> tests;
        tests.addTest(testListAppend, "ListAppend");
        tests.addTest(testListPrepend, "ListPrepend");
        tests.addTest(testListSwap, "ListSwap");
        tests.addTest(testListSwapNegative, "ListSwapNegative");
        tests.addTest(testListInsert, "ListInsert");
        tests.addTest(testArrayPop, "ArrayPop");
        tests.addTest(testArrayRemove, "ArrayRemove");
        tests.addTest(testArrayConcat, "ArrayConcat");
        tests.addTest(testArrayGetElementNegative, "ArrayGetElementNegative");
        tests.addTest(testArrayResizeNegative, "ArrayResizeNegative");
        tests.startTests();
    }
#endif

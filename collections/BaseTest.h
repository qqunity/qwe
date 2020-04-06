#ifndef COLLECTIONS_BASETEST_H
#define COLLECTIONS_BASETEST_H
    #include "UnitTests.h"
    #include "List.h"

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


    void startBaseTest() {
        unitTests::UnitTests<bool (*)()> tests;
        tests.addTest(testListAppend, "ListAppend");
        tests.addTest(testListPrepend, "ListPrepend");
        tests.addTest(testListSwap, "ListSwap");
        tests.startTests();
    }
#endif

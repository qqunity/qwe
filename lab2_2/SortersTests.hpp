#ifndef SORTER_SORTERSTESTS_HPP
#define SORTER_SORTERSTESTS_HPP

#include "UnitTests.hpp"
#include "ArraySequence.hpp"
#include "LinkedListSequence.hpp"
#include "HeapSorter.hpp"
#include "ShellSorter.hpp"
#include "QuickSorter.hpp"

namespace unitTests{
    bool testCorrectShellSorterBasedOnArray(){
        array::ArraySequence<unsigned int> a;
        array::ArraySequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::ShellSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    bool testCorrectShellSorterBasedOnLinkedList(){
        list::LinkedListSequence<unsigned int> a;
        list::LinkedListSequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::ShellSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    bool testCorrectQuickSorterBasedOnArray(){
        array::ArraySequence<unsigned int> a;
        array::ArraySequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::QuickSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    bool testCorrectQuickSorterBasedOnLinkedList(){
        list::LinkedListSequence<unsigned int> a;
        list::LinkedListSequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::QuickSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    bool testCorrectHeapSorterBasedOnArray(){
        array::ArraySequence<unsigned int> a;
        array::ArraySequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::HeapSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    bool testCorrectHeapSorterBasedOnLinkedList(){
        list::LinkedListSequence<unsigned int> a;
        list::LinkedListSequence<unsigned int> b;
        for (unsigned int i = 0; i < 50; ++i) {
            a.append(i);
        }
        b = a;
        sorter::HeapSorter<unsigned int> sorter;
        sorter.shuffle(&a, [](unsigned int i) {
            return std::rand() % i;
        });
        sorter.sort(&a, [](unsigned int a, unsigned int b) {
            return a > b;
        });
        return a.getRawData() == b.getRawData();
    }

    void startSortersTests() {
        UnitTests<bool (*)()> tests;
        tests.addTest(testCorrectShellSorterBasedOnArray, "CorrectShellSorterBasedOnArray", false);
        tests.addTest(testCorrectShellSorterBasedOnLinkedList, "CorrectShellSorterBasedOnLinkedList", false);
        tests.addTest(testCorrectQuickSorterBasedOnArray, "CorrectQuickSorterBasedOnArray", false);
        tests.addTest(testCorrectQuickSorterBasedOnLinkedList, "CorrectQuickSorterBasedOnLinkedList", false);
        tests.addTest(testCorrectHeapSorterBasedOnArray, "CorrectHeapSorterBasedOnArray", false);
        tests.addTest(testCorrectHeapSorterBasedOnLinkedList, "CorrectHeapSorterBasedOnLinkedList", false);
        tests.startTests();
    }
}

#endif

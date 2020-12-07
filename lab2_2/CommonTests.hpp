#ifndef LAB_2_COMMONTESTS_HPP
#define LAB_2_COMMONTESTS_HPP

#include "UnitTests.hpp"
#include "BTreeDictionary.hpp"
#include "AVLTreeDictionary.hpp"
#include "SparseVector.hpp"

namespace unitTests {
    bool testBTreeDictionaryInsert() {
        dictionary::BTreeDictionary<int, int> tree(2, "ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key).getValue() == value;
    }

    bool testBTreeDictionaryGetPositive() {
        dictionary::BTreeDictionary<int, int> tree(2, "ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key).getValue() == value;
    }

    bool testBTreeDictionaryGetNegative() {
        dictionary::BTreeDictionary<int, int> tree(2, "ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key + std::rand() % 10 + 1).getValue() == value;
    }

    bool testBTreeDictionaryRemove() {
        dictionary::BTreeDictionary<int, int> tree(2, "ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        tree.remove(key);
        return !tree.contains(key);
    }

    bool testAVLTreeDictionaryInsert() {
        dictionary::AVLTreeDictionary<int, int> tree("ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key).getValue() == value;
    }

    bool testAVLTreeDictionaryGetPositive() {
        dictionary::AVLTreeDictionary<int, int> tree("ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key).getValue() == value;
    }

    bool testAVLTreeDictionaryGetNegative() {
        dictionary::AVLTreeDictionary<int, int> tree("ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        return tree.get(key + std::rand() % 10 + 1).getValue() == value;
    }

    bool testAVLTreeDictionaryRemove() {
        dictionary::AVLTreeDictionary<int, int> tree("ArraySequence", -1, -1);
        int key = std::rand() % 1000;
        int value = std::rand() % 1000;
        tree.insert(key, value);
        tree.remove(key);
        return !tree.contains(key);
    }

    bool testSparseVectorAppend() {
        int mas[] = {0, 0, 0, 0, 2, 3, -13};
        vector::SparseVector<int> vec("BTreeDictionary", "ArraySequence", 0);
        for (unsigned int i = 0; i < 7; ++i) {
            vec.append(mas[i]);
        }
        for (unsigned int i = 0; i < 7; ++i) {
            if (vec[i] != mas[i]) {
                return false;
            }
        }
        return true;
    }

    bool testSparseVectorSwap() {
        int mas1[] = {0, 0, 0, 0, 2, 3, -13};
        int mas2[] = {0, 0, 0, 2, 0, 3, -13};
        vector::SparseVector<int> vec("BTreeDictionary", "ArraySequence", 0);
        for (unsigned int i = 0; i < 7; ++i) {
            vec.append(mas1[i]);
        }
        vec.swap(3, 4);
        for (unsigned int i = 0; i < 7; ++i) {
            if (vec[i] != mas2[i]) {
                return false;
            }
        }
        return true;
    }

    bool testSparseVectorPopPositive() {
        int mas1[] = {0, 0, 0, 0, 2, 3, -13};
        int mas2[] = {0, 0, 0, 0, 3, -13};
        vector::SparseVector<int> vec("BTreeDictionary", "ArraySequence", 0);
        for (unsigned int i = 0; i < 7; ++i) {
            vec.append(mas1[i]);
        }
        vec.pop(4);
        for (unsigned int i = 0; i < 6; ++i) {
            if (vec[i] != mas2[i]) {
                return false;
            }
        }
        return true;
    }

    bool testSparseVectorPopNegative() {
        int mas1[] = {0, 0, 0, 0, 2, 3, -13};
        int mas2[] = {0, 0, 0, 0, 3, -13};
        vector::SparseVector<int> vec("BTreeDictionary", "ArraySequence", 0);
        for (unsigned int i = 0; i < 7; ++i) {
            vec.append(mas1[i]);
        }
        vec.pop(44);
        for (unsigned int i = 0; i < 6; ++i) {
            if (vec[i] != mas2[i]) {
                return false;
            }
        }
        return true;
    }

    bool testSparseVectorInsert() {
        int mas1[] = {0, 0, 0, 0, 2, 3, -13};
        int mas2[] = {0, 0, 0, 0, 1, 2, 3, -13};
        vector::SparseVector<int> vec("BTreeDictionary", "ArraySequence", 0);
        for (unsigned int i = 0; i < 7; ++i) {
            vec.append(mas1[i]);
        }
        vec.insert(4, 1);
        for (unsigned int i = 0; i < 8; ++i) {
            if (vec[i] != mas2[i]) {
                return false;
            }
        }
        return true;
    }

    void startCommonTests() {
        UnitTests<bool (*)()> tests;

        tests.addTest(testBTreeDictionaryInsert, "BTreeDictionaryInsert", false);
        tests.addTest(testBTreeDictionaryRemove, "BTreeDictionaryRemove", false);
        tests.addTest(testBTreeDictionaryGetPositive, "BTreeDictionaryGetPositive", false);
        tests.addTest(testBTreeDictionaryGetNegative, "BTreeDictionaryGetNegative", true);
        tests.addTest(testAVLTreeDictionaryInsert, "AVLTreeDictionaryInsert", false);
        tests.addTest(testAVLTreeDictionaryRemove, "AVLTreeDictionaryRemove", false);
        tests.addTest(testAVLTreeDictionaryGetPositive, "AVLTreeDictionaryGetPositive", false);
        tests.addTest(testAVLTreeDictionaryGetNegative, "AVLTreeDictionaryGetNegative", true);
        tests.addTest(testSparseVectorAppend, "SparseVectorAppend", false);
        tests.addTest(testSparseVectorSwap, "SparseVectorSwap", false);
        tests.addTest(testSparseVectorPopPositive, "SparseVectorPopPositive", false);
        tests.addTest(testSparseVectorPopNegative, "SparseVectorPopNegative", true);
        tests.addTest(testSparseVectorInsert, "SparseVectorInsert", false);
        tests.startTests();
    }
}
#endif

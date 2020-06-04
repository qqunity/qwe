#include <iostream>
#include <chrono>
#include <vector>
#include "ForwardList.h"

using namespace std;
using namespace chrono;

template<typename seqT, typename FuncComp, typename FuncSwap>
void sort(seqT &seq, FuncComp comp, FuncSwap swap) {
    for (unsigned int i = 0; i < seq.length() - 1; ++i) {
        for (unsigned int j = 0; j < seq.length() - i - 1; ++j) {
            if (comp(seq[j], seq[j + 1])) {
                swap(seq[j], seq[j + 1]);
            }
        }        
    }
}

template<typename Fun>
double getExecutionTime(Fun f) {
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    f();
    double timeTaken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    return timeTaken;
}

template<typename T>
void swap1(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void swap2(T &a, T &b) {
    T temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}

void testSwap1() {
    srand(time(nullptr));
    ForwardList<ForwardList<int>> ll;
    for (unsigned int j = 0; j < 50; ++j) {
        ForwardList<int> buffL;
        for (unsigned int i = 0; i < 500; ++i) {
            buffL.append(rand() % 500);
        }
        ll.append(buffL);
    }

    sort(ll, [](ForwardList<int> a, ForwardList<int> b) {
        int sum1 = 0;
        for (unsigned int i = 0; i < a.length(); ++i) {
            sum1 += a[i];
        }
        int sum2 = 0;
        for (unsigned int j = 0; j < b.length(); ++j) {
            sum2 += b[j];
        }
        return sum1 < sum2;
    }, swap1<ForwardList<int>>);
}

void testSwap2() {
    srand(time(nullptr));
    ForwardList<ForwardList<int>> ll;
    for (unsigned int j = 0; j < 50; ++j) {
        ForwardList<int> buffL;
        for (unsigned int i = 0; i < 500; ++i) {
            buffL.append(rand() % 500);
        }
        ll.append(buffL);
    }

    sort(ll, [](ForwardList<int> a, ForwardList<int> b) {
        int sum1 = 0;
        for (unsigned int i = 0; i < a.length(); ++i) {
            sum1 += a[i];
        }
        int sum2 = 0;
        for (unsigned int j = 0; j < b.length(); ++j) {
            sum2 += b[j];
        }
        return sum1 < sum2;
    }, swap2<ForwardList<int>>);
}


void testCopy() {
    srand(time(nullptr));
    ForwardList<ForwardList<int>> ll;
    for (unsigned int j = 0; j < 50; ++j) {
        ForwardList<int> buffL;
        for (unsigned int i = 0; i < 500; ++i) {
            buffL.append(rand() % 500);
        }
        ll.append(buffL);
    }
    ForwardList<ForwardList<int>> llc = ll;
}

void testMove() {
    srand(time(nullptr));
    ForwardList<ForwardList<int>> ll;
    for (unsigned int j = 0; j < 50; ++j) {
        ForwardList<int> buffL;
        for (unsigned int i = 0; i < 500; ++i) {
            buffL.append(rand() % 500);
        }
        ll.append(buffL);
    }
    ForwardList<ForwardList<int>> llc = std::move(ll);
}

void testFillPushBack() {
    vector<int> vec;
    srand(time(nullptr));
    for (unsigned int i = 0; i < 1000000; ++i) {
        vec.push_back(rand() % 1000000);
    }
}

void testFill() {
    vector<int> vec(1000000);
    srand(time(nullptr));
    for (unsigned int i = 0; i < 1000000; ++i) {
        vec[i] = rand() % 1000000;
    }
}

int main() {
    cout << "Swap with copy: " << getExecutionTime(testSwap1) << " nanoseconds" << '\n';
    cout << "Swap with move: " << getExecutionTime(testSwap2) << " nanoseconds" << '\n';
    cout << "Just copy: " << getExecutionTime(testCopy) << " nanoseconds" << '\n';
    cout << "Just move: " << getExecutionTime(testMove) << " nanoseconds" << '\n';
    cout << "Fill with push_back: " << getExecutionTime(testFillPushBack) << " nanoseconds" << '\n';
    cout << "Fill with const size: " << getExecutionTime(testFill) << " nanoseconds" << '\n';
    return 0;
}

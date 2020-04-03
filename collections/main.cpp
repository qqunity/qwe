#include <iostream>
#include <ctime>
#include "Utils.h"
#include "List.h"

void arrayTest() {
    Array<int> a(7);
    for (int i = 0; i < 7; ++i){
        a[i] = i;
    }
    Array<int> b;
    srand( time(0));
    for (int i = 0; i < 7; ++i){
        b.append(rand() % 13);
    }
    std::cout << b << std::endl;
    b = sorted<Array<int>, int>(b.begin(), b.end(), [](ArrayElement<int> a, ArrayElement<int> b) {
        return a < b;
    });
    std::cout << b << std::endl;
    int count = 8;
    map(b.begin(), b.end(), [&count](ArrayElement<int> &a) {
        a = count;
        ++count;
    });
    std::cout << b << std::endl;
    auto c = where<Array<int>>(b.begin(), b.end(), [](ArrayElement<int> a) {
        return a >= 11;
    });
    std::cout << c << std::endl;
    Array<int> d;
    d.append(1);
    d.append(2);
    d.append(3);
    auto res = reduce<int>(d.begin(), d.end(), 4, [](int a, int b) {
        return a > b ? a : b;
    });
    std::cout << res << std::endl;
    int mas[] = {1, 2, 3, 4};
    Array<int> aa(mas, 4);
    std::cout << aa;
}


int main() {
    List<int> b;
    srand( time(0));
    for (int i = 0; i < 7; ++i){
        b.append(rand() % 13);
    }
    std::cout << b << std::endl;
    b = sorted<List<int>, int>(b.begin(), b.end(), [](auto a, auto b) {
        return a < b;
    });
    std::cout << b << std::endl;
    int count = 8;
    map(b.begin(), b.end(), [&count](ListElement<int> &a) {
        a = count;
        ++count;
    });
    std::cout << b << std::endl;
    auto c = where<List<int>>(b.begin(), b.end(), [](ListElement<int> a) {
        return a >= 11;
    });
    std::cout << c << std::endl;
    List<int> d;
    d.append(1);
    d.append(2);
    d.append(3);
    auto res = reduce<int>(d.begin(), d.end(), 4, [](int a, int b) {
        return a > b ? a : b;
    });
    std::cout << res << std::endl;
    int mas[] = {1, 2, 3, 4};
    List<int> aa(mas, 4);
    std::cout << aa;
    return 0;
}

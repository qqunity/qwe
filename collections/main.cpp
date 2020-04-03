#include <iostream>
#include <ctime>
#include "Utils.h"
#include "List.h"
#include "Stream.h"
#include "UnitTests.h"

void arrayTest() {
    array::Array<int> a(7);
    for (int i = 0; i < 7; ++i){
        a[i] = i;
    }
    array::Array<int> b;
    srand( time(0));
    for (int i = 0; i < 7; ++i){
        b.append(rand() % 13);
    }
    std::cout << b << std::endl;
    b = utils::sorted<array::Array<int>, int>(b.begin(), b.end(), [](ArrayElement<int> a, ArrayElement<int> b) {
        return a < b;
    });
    std::cout << b << std::endl;
    int count = 8;
    utils::map(b.begin(), b.end(), [&count](ArrayElement<int> &a) {
        a = count;
        ++count;
    });
    std::cout << b << std::endl;
    auto c = utils::where<array::Array<int>>(b.begin(), b.end(), [](ArrayElement<int> a) {
        return a >= 11;
    });
    std::cout << c << std::endl;
    array::Array<int> d;
    d.append(1);
    d.append(2);
    d.append(3);
    auto res = utils::reduce<int>(d.begin(), d.end(), 4, [](int a, int b) {
        return a > b ? a : b;
    });
    std::cout << res << std::endl;
    int mas[] = {1, 2, 3, 4};
    array::Array<int> aa(mas, 4);
    std::cout << aa;
}

void listTest(){
    std::cout << std::endl;
    list::List<int> b;
    srand( time(0));
    for (int i = 0; i < 7; ++i){
        b.append(rand() % 13);
    }
    std::cout << b << std::endl;
    b = utils::sorted<list::List<int>, int>(b.begin(), b.end(), [](auto a, auto b) {
        return a < b;
    });
    std::cout << b << std::endl;
    int count = 8;
    utils::map(b.begin(), b.end(), [&count](ListElement<int> &a) {
        a = count;
        ++count;
    });
    std::cout << b << std::endl;
    auto c = utils::where<list::List<int>>(b.begin(), b.end(), [](ListElement<int> a) {
        return a >= 11;
    });
    std::cout << c << std::endl;
    list::List<int> d;
    d.append(1);
    d.append(2);
    d.append(3);
    auto res = utils::reduce<int>(d.begin(), d.end(), 4, [](int a, int b) {
        return a > b ? a : b;
    });
    std::cout << res << std::endl;
    int mas[] = {1, 2, 3, 4};
    list::List<int> aa(mas, 4);
    std::cout << aa;
}

bool testFun(){
    return false;
}

int main() {
    unitTests::Test t(testFun, "testFun");
    t.startTest();
    t.getTestResult();
    return 0;
}

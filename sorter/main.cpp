#include <iostream>
#include "LinkedListSequence.hpp"
#include "Utils.hpp"
#include "HeapSorter.hpp"



int main() {
    list::LinkedListSequence<unsigned int> a;
    for (unsigned int i = 0; i < 10000; ++i) {
        a.append(i);
    }
//    std::cout << a << '\n';
    sorter::HeapSorter<unsigned int> sorter;
    std::srand(std::time(nullptr));
    sorter.shuffle(&a, [](unsigned int i) {
        return std::rand() % (i + 1);
    });
//    std::cout << a << '\n';
    sorter.sort(&a, [](unsigned int a, unsigned int b) {
        return a > b;
    });
//    std::cout << a << '\n';
    std::cout << sorter.getNumberOfIterationSeconds() ;
    return 0;
}

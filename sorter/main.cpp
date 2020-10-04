#include <iostream>
#include "LinkedListSequence.hpp"
#include "ArraySequence.hpp"
#include "Utils.hpp"
#include "HeapSorter.hpp"
#include "QuickSorter.hpp"
#include "ShellSorter.hpp"
#include "BaseTests.hpp"
#include "SortersTests.hpp"


void UI() {
    std::cout << "Консольное тестирование базовых сортировок, выполненных в рамках лабораторной работы №1" << std::endl;
    array::ArraySequence<unsigned int> a;
    list::LinkedListSequence<unsigned int> b;
    std::srand(std::time(nullptr));
    while (true) {
        std::cout << "\x1b[35m<o>\x1b[0m Введите 0, если хотите завершить консольное приложение." << std::endl
                  << "\x1b[35m<o>\x1b[0m Введите 1, если хотите запустить unit-тесты на базовые структуры." << std::endl
                  << "\x1b[35m<o>\x1b[0m Введите 2, если хотите запустить unit-тесты на базовые сортировки."
                  << std::endl << "\x1b[35m<o>\x1b[0m Введите 3, если хотите ввести массив для сортировки." << std::endl
                  << "\x1b[35m<o>\x1b[0m Введите 4, если хотите отсортировать массив." << std::endl << "\x1b[35m<o>\x1b[0m Введите 5, если хотите сбросить введенные данные." << std::endl;
        std::cout << "\x1b[35m-> \x1b[0m";
        int userInput;
        std::cin >> userInput;
        if (userInput == 0) {
            break;
        } else if (userInput == 1) {
            unitTests::startBaseTests();
        } else if (userInput == 2) {
            unitTests::startSortersTests();
        } else if (userInput == 3) {
            std::cout
                    << "\x1b[35m<o>\x1b[0m Введите количество элеменетов массива."
                    << std::endl;
            std::cout << "\x1b[35m-> \x1b[0m";
            int n;
            std::cin >> n;
            std::cout
                    << "\x1b[35m<o>\x1b[0m Если хотите сгенерировать массив рандомно, введите 1 (иначе вам придется вводить его вручную)."
                    << std::endl;
            std::cout << "\x1b[35m-> \x1b[0m";
            int anotherUserInput1;
            std::cin >> anotherUserInput1;
            std::cout
                    << "\x1b[35m<o>\x1b[0m Если хотите сгенерировать массив на основе Linked List, введите 1 (иначе он сгенерируется на основе Array)."
                    << std::endl;
            std::cout << "\x1b[35m-> \x1b[0m";
            int anotherUserInput2;
            std::cin >> anotherUserInput2;
            if (anotherUserInput1 == 1) {
                if (anotherUserInput2 == 1) {
                    for (unsigned int i = 0; i < n; ++i) {
                        b.append(std::rand() % n);
                    }
                } else {
                    for (unsigned int i = 0; i < n; ++i) {
                        a.append(std::rand() % n);
                    }
                }
            } else {
                std::cout
                        << "\x1b[35m<o>\x1b[0m Вводите по очереди числа."
                        << std::endl;
                if (anotherUserInput2 == 1) {
                    for (unsigned int i = 0; i < n; ++i) {
                        int buff;
                        std::cin >> buff;
                        b.append(buff);
                    }
                } else {
                    for (unsigned int i = 0; i < n; ++i) {
                        int buff;
                        std::cin >> buff;
                        a.append(buff);
                    }
                }
            }
            std::cout
                    << "\x1b[35m<o>\x1b[0m Полученный массив:"
                    << std::endl;
            if (a.length() != 0) {
                std::cout << a << std::endl;
            }
            if (b.length() != 0) {
                std::cout << b << std::endl;
            }
        } else if (userInput == 4) {
            std::cout << "\x1b[35m<o>\x1b[0m Введите 0, если хотите отсортировать массив сортировкой Quick sort." << std::endl
                      << "\x1b[35m<o>\x1b[0m Введите 1, если хотите отсортировать массив сортировкой Shell sort." << std::endl
                      << "\x1b[35m<o>\x1b[0m Введите 2, если хотите отсортировать массив сортировкой Heap sort."
                      << std::endl;
            std::cout << "\x1b[35m-> \x1b[0m";
            int anotherUserInput1;
            std::cin >> anotherUserInput1;
            if (anotherUserInput1 == 0) {
                sorter::QuickSorter<unsigned int> sorter;
                if (a.length() != 0) {
                    sorter.sort(&a, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << a << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
                if (b.length() != 0) {
                    sorter.sort(&b, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << b << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
            } else if (anotherUserInput1 == 1) {
                sorter::ShellSorter<unsigned int> sorter;
                if (a.length() != 0) {
                    sorter.sort(&a, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << a << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
                if (b.length() != 0) {
                    sorter.sort(&b, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << b << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
            } else if (anotherUserInput1 == 2) {
                sorter::HeapSorter<unsigned int> sorter;
                if (a.length() != 0) {
                    sorter.sort(&a, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << a << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
                if (b.length() != 0) {
                    sorter.sort(&b, [](unsigned int a, unsigned int b) {
                        return a > b;
                    });
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Отсортированный массив:"
                            << std::endl;
                    std::cout << b << std::endl;
                    std::cout
                            << "\x1b[35m<o>\x1b[0m Полученные метрики:"
                            << std::endl;
                    std::cout << "Количество затраченных милисекунд: " << sorter.getNumberOfIterationMilliseconds() << "\tКоличество итераций: " << sorter.getCntIterations() << std::endl;
                }
            }
        } else if (userInput == 5) {
            a.remove();
            b.remove();
        }
    }
    std::cout << "До скорых встреч!";
}


int main() {
//    array::ArraySequence<unsigned int> a;
//    list::LinkedListSequence<unsigned int> b;
//    list::LinkedListSequence<unsigned int> c;
//
//    sorter::HeapSorter<unsigned int> sorter1;
//    sorter::QuickSorter<unsigned int> sorter2;
//    sorter::ShellSorter<unsigned int> sorter3;
//    std::srand(std::time(nullptr));
//    sorter2.getRandomSequence(&a, [](unsigned int i) {
//        return std::rand() % (i + SIZE);
//    }, SIZE);
//    b = a;
//    c = b;
//    sorter2.sort(&a, [](unsigned int a, unsigned int b) {
//        return a < b;
//    });
//    sorter2.sort(&b, [](unsigned int a, unsigned int b) {
//        return a < b;
//    });
//    sorter3.sort(&c, [](unsigned int a, unsigned int b) {
//        return a < b;
//    });
//    std::cout << a << '\n';
//    std::cout << b << '\n';
//    std::cout << c << '\n';
//    std::cout << (a.getRawData() == b.getRawData()) << '\n';
//    std::cout << (b.getRawData() == c.getRawData()) << '\n';
//    std::cout << b << '\n';
//    std::cout << sorter1.getCntIterations() << '\t' << sorter1.getNumberOfIterationMilliseconds() << '\n';
//    std::cout << sorter2.getCntIterations() << '\t' << sorter2.getNumberOfIterationMilliseconds() << '\n';
//    std::cout << sorter3.getCntIterations() << '\t' << sorter3.getNumberOfIterationMilliseconds() << '\n';
//    unitTests::startBaseTests();
//    unitTests::startSortersTests();
    UI();
}

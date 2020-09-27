cmake_minimum_required(VERSION 3.17)
project(sorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(sorter main.cpp Optional.hpp ArrayElement.hpp Exceptions.cpp Exceptions.hpp ListElement.hpp Array.hpp LinkedList.hpp Utils.hpp Sequence.hpp ArraySequence.hpp LinkedListSequence.hpp ISorter.hpp HeapSorter.hpp)
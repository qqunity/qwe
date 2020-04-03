cmake_minimum_required(VERSION 3.16)
project(collections)

set(CMAKE_CXX_STANDARD 20)

add_executable(collections main.cpp ArrayElement.h Exceptions.h Array.h BinaryHeap.h Utils.h ListElement.h List.h Sequence.h)
cmake_minimum_required(VERSION 3.5)
project(lab_2)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "/Applications/QT/5.15.0/clang_64")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)


add_executable(lab_2 main.cpp Optional.hpp ArrayElement.hpp Exceptions.cpp Exceptions.hpp ListElement.hpp Array.hpp LinkedList.hpp Utils.hpp Sequence.hpp ArraySequence.hpp LinkedListSequence.hpp ISorter.hpp HeapSorter.hpp UnitTests.hpp BaseTests.hpp QuickSorter.hpp ShellSorter.hpp SortersTests.hpp BTree.hpp KVElement.hpp BTreeDictionary.hpp SequenceIterator.hpp Pair.hpp AVLTree.hpp AVLTreeDictionary.hpp IDictionary.hpp GameField.cpp GameField.hpp Matrix.hpp Opt.hpp Minimax.cpp Minimax.hpp TicTacToe.cpp TicTacToe.hpp)
target_link_libraries(lab_2 Qt5::Widgets Qt5::Core)

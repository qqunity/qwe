cmake_minimum_required(VERSION 3.17)
project(lab2_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/Applications/QT/6.0.0/clang_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

add_executable(${PROJECT_NAME} main.cpp MainWindow.cpp MainWindow.hpp MainWindow.ui UndirectedGraph.hpp Optional.hpp ArrayElement.hpp Exceptions.cpp Exceptions.hpp ListElement.hpp Array.hpp LinkedList.hpp Utils.hpp Sequence.hpp ArraySequence.hpp LinkedListSequence.hpp ISorter.hpp HeapSorter.hpp UnitTests.hpp BaseTests.hpp QuickSorter.hpp ShellSorter.hpp SortersTests.hpp BTree.hpp KVElement.hpp BTreeDictionary.hpp SequenceIterator.hpp Pair.hpp AVLTree.hpp AVLTreeDictionary.hpp IDictionary.hpp Matrix.hpp Opt.hpp SparseVector.hpp CommonTests.hpp GraphVisualizationWindow.cpp GraphVisualizationWindow.hpp GraphVisualizationWindow.ui GraphInteractionWindow.cpp GraphInteractionWindow.hpp GraphInteractionWindow.ui)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

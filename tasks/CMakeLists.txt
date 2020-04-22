cmake_minimum_required(VERSION 3.16)
project(tasks)

set(CMAKE_CXX_STANDARD 20)

add_executable(tasks main.cpp List.h ListElement.h Exceptions.h TreeNode.cpp TreeNode.h MathPhraseParser.cpp MathPhraseParser.h)
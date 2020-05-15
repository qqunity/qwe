cmake_minimum_required(VERSION 3.16)
project(Tic_Tac_Toe_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tic_Tac_Toe_game main.cpp TicTacToe.cpp TicTacToe.h Matrix.h Optional.h Exception.cpp Exception.h TreeX.h NodeX.h GameIntelligence.cpp GameIntelligence.h)
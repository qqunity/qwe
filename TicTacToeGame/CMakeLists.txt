cmake_minimum_required(VERSION 3.16)
project(TicTacToeGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(TicTacToeGame main.cpp TicTacToe.cpp TicTacToe.h Matrix.h Optional.h Exception.cpp Exception.h TreeX.h NodeX.h GameIntelligence.cpp GameIntelligence.h Utils.cpp Utils.h Game.cpp Game.h GameDecisionTreeX.cpp GameDecisionTreeX.h Minimax.cpp Minimax.h)
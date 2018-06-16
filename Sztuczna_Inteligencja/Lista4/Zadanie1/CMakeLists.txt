cmake_minimum_required(VERSION 3.10)
project(Zadanie1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Zadanie1 main.cpp Board.cpp Board.h Heuristics.cpp Heuristics.h Agent.cpp Agent.h OpeningDatabase.cpp OpeningDatabase.h Game.cpp Game.h)
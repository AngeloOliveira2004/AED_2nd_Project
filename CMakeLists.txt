cmake_minimum_required(VERSION 3.26)
project(Projeto_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto_2 main.cpp
        Logic/Graph.h
        Logic/Logic.h
        Logic/Airport.h
        Logic/LoadingFunctions.h
        Logic/Airline.h
        Logic/LoadingFunctions.cpp
        Logic/Airport.cpp
        Logic/Logic.cpp
        Logic/Airline.cpp
        UI/UI.h
        UI/UI.cpp)

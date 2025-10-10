cmake_minimum_required(VERSION 4.0)
project(battleship_game)

set(CMAKE_CXX_STANDARD 26)

add_executable(battleship_game main.cpp
        ConsoleRender.cpp
        ConsoleRender.h
        GameEngine.cpp
        GameEngine.h
        BoardWidget.cpp
        BoardWidget.h
        TextWidget.cpp
        TextWidget.h
        Ship.cpp
        Ship.h
)

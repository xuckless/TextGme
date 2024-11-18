cmake_minimum_required(VERSION 3.29)
project(TextGame)

set(CMAKE_CXX_STANDARD 23)

add_executable(TextGame main.cpp
        BaseLevel.h
        BaseLevel.cpp
        Level.h
        DynamicArray.h
        Enemy.h
        Enemy.cpp
        LevelHandler.h
        LevelHandler.cpp
        LevelOne.h
        LevelOne.cpp
        Levels.h
        Levels.cpp
        Player.cpp
        AsciiArt.h
        LevelTwo.h
        LevelTwo.cpp
        Utilities.h
        Utilities.cpp
)

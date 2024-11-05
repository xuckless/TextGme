cmake_minimum_required(VERSION 3.29)
project(TextGme)

set(CMAKE_CXX_STANDARD 26)

add_executable(TextGme main.cpp
        Player.cpp
        Enemy.cpp
        Level.h
        LevelOne.h
        LevelTwo.h
        LevelThree.h
        LevelHandler.h
        Levels.h
        chest.h)

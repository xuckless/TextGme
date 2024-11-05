// LevelTwo.h
#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "Level.h"
#include <iostream>

class LevelTwo : public Level {
private:
    bool isComplete = false;

public:
    LevelTwo() = default;

    void proceed() override {
        std::cout << "Hello, welcome to level two" << std::endl;
        isComplete = true;
    }
};

#endif // LEVELTWO_H
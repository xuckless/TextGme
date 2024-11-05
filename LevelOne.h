// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "Level.h"
#include <iostream>

class LevelOne : public Level {
private:
    bool isComplete = false; 

public:
    LevelOne() = default;

    void proceed() override {
        std::cout << "Hello, welcome to the tutorial" << std::endl;
        isComplete = true;
    }
};

#endif // LEVELONE_H

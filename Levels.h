// Levels.h
#ifndef LEVELS_H
#define LEVELS_H

#include "LevelHandler.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"

class Levels {
private: //this function adds the level into the linkedlist 
    std::shared_ptr<LevelHandler> firstLevel;

    void setUp() {
        firstLevel = std::make_shared<LevelHandler>(std::make_shared<LevelOne>());
        firstLevel->addLevelInLast(std::make_shared<LevelTwo>());
        firstLevel->addLevelInLast(std::make_shared<LevelThree>());
    }

public:
    Levels() {
        setUp();
    }

    void startLevels() { //this function goes through the linkedlist one at the time changing the levels after the player completes it
        auto current = firstLevel;
        while (current) {
            auto level = current->getLevel();
            level->proceed();
            current = current->getNextLevel();
        }
    }
};

#endif // LEVELS_H

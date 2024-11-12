// Levels.cpp
#include "Levels.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"

Levels::Levels() {
    setUp();
}

Levels::~Levels() {
    delete firstLevel;
}

void Levels::setUp() {
    firstLevel = new LevelHandler(new LevelOne(), nullptr);
    firstLevel->addLevelInLast(new LevelTwo());
    firstLevel->addLevelInLast(new LevelThree());
}

void Levels::startLevels() {
    LevelHandler* current = firstLevel;
    while (current != nullptr) {
        Level* level = current->getLevel();
        level->proceed();
        current = current->getNextLevel();
    }
}

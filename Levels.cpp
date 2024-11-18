// Levels.cpp
#include "Levels.h"
#include "LevelOne.h"
#include "LevelTwo.h" // Include LevelTwo

Levels::Levels() {
    setUp();
}

Levels::~Levels() {
    delete firstLevel;
}

void Levels::setUp() {
    // Initialize the first level
    firstLevel = new LevelHandler(new LevelOne(), nullptr);

    // Add LevelTwo to the end of the levels linked list
    firstLevel->addLevelInLast(new LevelTwo());
}

void Levels::startLevels() {
    LevelHandler* current = firstLevel;
    while (current != nullptr) {
        Level* level = current->getLevel();
        level->proceed();
        current = current->getNextLevel();
    }
}

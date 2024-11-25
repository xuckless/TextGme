// Levels.cpp

#include "Levels.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include <memory>

Levels::Levels() {
    setUp();
}

Levels::~Levels() {
    LevelHandler* current = firstLevel;
    while (current != nullptr) {
        LevelHandler* next = current->getNextLevel();
        delete current;
        current = next;
    }
}

void Levels::setUp() {
    // Create a shared Player object
    std::shared_ptr<Player> player = std::make_shared<Player>();

    // Initialize the first level with the Player object
    firstLevel = new LevelHandler(new LevelOne(player), nullptr);

    // Add LevelTwo to the end of the levels linked list with the Player object
    firstLevel->addLevelAfter(new LevelTwo(player));
}

void Levels::startLevels() {
    LevelHandler* current = firstLevel;
    while (current != nullptr) {
        Level* level = current->getLevel();
        level->proceed();
        current = current->getNextLevel();
    }
}

// LevelHandler.cpp
#include "LevelHandler.h"

LevelHandler::LevelHandler(Level* level, LevelHandler* nextLevel) : level(level), nextLevel(nextLevel) {}

LevelHandler::~LevelHandler() {
    delete level;
    delete nextLevel;
}

LevelHandler* LevelHandler::getNextLevel() {
    return nextLevel;
}

Level* LevelHandler::getLevel() {
    return level;
}

void LevelHandler::addLevelAfter(Level* level) {
    this->nextLevel = new LevelHandler(level, this->nextLevel);
}

void LevelHandler::addLevelInLast(Level* level) {
    LevelHandler* current = this;
    while (current->nextLevel != nullptr) {
        current = current->nextLevel;
    }
    current->addLevelAfter(level);
}

void LevelHandler::removeLevelAfter() {
    if (this->nextLevel != nullptr) {
        LevelHandler* temp = this->nextLevel;
        this->nextLevel = this->nextLevel->nextLevel;
        temp->nextLevel = nullptr;
        delete temp;
    }
}

void LevelHandler::removeFromLast() {
    LevelHandler* current = this;
    LevelHandler* prev = nullptr;

    while (current->nextLevel != nullptr) {
        prev = current;
        current = current->nextLevel;
    }

    if (prev != nullptr) {
        prev->removeLevelAfter();
    }
}

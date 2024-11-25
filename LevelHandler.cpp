// LevelHandler.cpp
#include "LevelHandler.h"

LevelHandler::LevelHandler(Level* level, LevelHandler* nextLevel) : level(level), nextLevel(nextLevel) {}

LevelHandler::~LevelHandler() {
    delete level;
    delete nextLevel;
}

LevelHandler* LevelHandler::getNextLevel() { //this allows us to tervse the linked list
    return nextLevel;
}

Level* LevelHandler::getLevel() {  //this is a pointer telling us where the node we are at is 
    return level;
}

void LevelHandler::addLevelAfter(Level* level) { //this adds a node after the head of the linked list
    this->nextLevel = new LevelHandler(level, this->nextLevel);
}

void LevelHandler::addLevelInLast(Level* level) { //this adds a level in the last place of the linked list
    LevelHandler* current = this;
    while (current->nextLevel != nullptr) {
        current = current->nextLevel;
    }
    current->addLevelAfter(level);
}

void LevelHandler::removeLevelAfter() { //this removes a node in the linked list after the head
    if (this->nextLevel != nullptr) {
        LevelHandler* temp = this->nextLevel;
        this->nextLevel = this->nextLevel->nextLevel;
        temp->nextLevel = nullptr;
        delete temp;
    }
}

void LevelHandler::removeFromLast() { //this removes a node in the linked list from the end of the list
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

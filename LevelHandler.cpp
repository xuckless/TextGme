// LevelHandler.cpp
// This implementation manages a linked list of game levels, where each level is connected in a unidirectional sequence.
// Players can only progress forward through the levels. It includes methods to add and remove levels dynamically.

#include "LevelHandler.h"

// Constructor: Initializes the LevelHandler node with a given level and a pointer to the next level in the sequence.
LevelHandler::LevelHandler(Level* level, LevelHandler* nextLevel) : level(level), nextLevel(nextLevel) {}

// Destructor: Deletes the current level and all subsequent levels recursively.
LevelHandler::~LevelHandler() {
    delete level;       // Free memory allocated for the level.
    delete nextLevel;   // Recursively delete the next levels in the sequence.
}

// Getter: Returns the pointer to the next level in the sequence.
LevelHandler* LevelHandler::getNextLevel() {
    return nextLevel;
}

// Getter: Returns the pointer to the current level.
Level* LevelHandler::getLevel() {
    return level;
}

// Adds a new level immediately after the current level.
void LevelHandler::addLevelAfter(Level* level) {
    // Creates a new LevelHandler node and inserts it between the current and the next level.
    this->nextLevel = new LevelHandler(level, this->nextLevel);
}

// Adds a new level at the end of the linked list.
void LevelHandler::addLevelInLast(Level* level) {
    LevelHandler* current = this; // Start at the current node.
    // Traverse to the last node in the linked list.
    while (current->nextLevel != nullptr) {
        current = current->nextLevel;
    }
    // Add the new level after the last node.
    current->addLevelAfter(level);
}

// Removes the level immediately after the current level.
void LevelHandler::removeLevelAfter() {
    if (this->nextLevel != nullptr) { // Check if a next level exists.
        LevelHandler* temp = this->nextLevel; // Store the node to be removed.
        this->nextLevel = this->nextLevel->nextLevel; // Update the pointer to skip the removed node.
        temp->nextLevel = nullptr; // Isolate the removed node.
        delete temp; // Free the memory for the removed node.
    }
}

// Removes the last level in the linked list.
void LevelHandler::removeFromLast() {
    LevelHandler* current = this; // Start at the current node.
    LevelHandler* prev = nullptr; // Keep track of the previous node.

    // Traverse to the last node while keeping track of the previous node.
    while (current->nextLevel != nullptr) {
        prev = current;
        current = current->nextLevel;
    }

    // If there is a previous node, remove its next level (the last node).
    if (prev != nullptr) {
        prev->removeLevelAfter();
    }
}
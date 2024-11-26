#ifndef LEVELS_H
#define LEVELS_H

#include "LevelHandler.h"
#include "LevelOne.h"
#include <memory>

// The `Levels` class manages the sequence of levels in the game.
// It serves as the entry point to set up and traverse through the levels.
class Levels {
private:
    LevelHandler* firstLevel; // Pointer to the first level in the linked list of levels.

public:
    // Constructor: Initializes the Levels class and sets up the level sequence.
    Levels();

    // Destructor: Cleans up memory for all levels in the linked list.
    ~Levels();

    // Sets up the linked list of levels, starting with LevelOne.
    void setUp();

    // Starts the gameplay by iterating through the linked list of levels
    // and calling their `proceed()` methods.
    void startLevels();
};

#endif // LEVELS_H
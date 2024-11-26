#include "Levels.h"
#include "LevelOne.h"
#include <memory>

// Constructor: Initializes the Levels class and sets up the linked list of levels.
Levels::Levels() {
    setUp();
}

// Destructor: Cleans up the linked list of levels by iterating through the nodes and deleting them.
Levels::~Levels() {
    LevelHandler* current = firstLevel;
    while (current != nullptr) { // Traverse the linked list.
        LevelHandler* next = current->getNextLevel(); // Store the next level.
        delete current; // Delete the current level handler.
        current = next; // Move to the next level.
    }
}

// Sets up the sequence of levels in the linked list.
void Levels::setUp() {
    // Create a shared Player object to be passed to all levels.
    std::shared_ptr<Player> player = std::make_shared<Player>();

    // Initialize the first level and set it as the start of the linked list.
    firstLevel = new LevelHandler(new LevelOne(player), nullptr);

    // Example: Add additional levels by extending the linked list.
    // Uncomment and implement this section to add more levels:
    // firstLevel->setNext(new LevelHandler(new LevelTwo(player), nullptr));
    // firstLevel->getNextLevel()->setNext(new LevelHandler(new LevelThree(player), nullptr));
}

// Starts the gameplay by traversing the linked list of levels.
// Each level's `proceed()` method is called in sequence.
void Levels::startLevels() {
    LevelHandler* current = firstLevel; // Start from the first level.
    while (current != nullptr) { // Iterate through all levels.
        Level* level = current->getLevel(); // Get the current level.
        level->proceed(); // Execute the level's logic.
        current = current->getNextLevel(); // Move to the next level.
    }
}
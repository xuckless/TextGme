#include "BaseLevel.h"
#include <limits>

// Constructor
BaseLevel::BaseLevel() : player("Player 1", 100, 100) { // Correctly using the 3-argument constructor
    // Initialization moved to derived classes
}

// Destructor
BaseLevel::~BaseLevel() {
    delete scenarioHandler;
}

// Adds actions to the scenario handler
void BaseLevel::addAction(const std::string& description, std::function<void()> action) {
    actionMap[description] = action;
}

// Navigates the decision tree for the current level
void BaseLevel::navigateDecisionTree(Scenes<std::string>* node, std::function<bool()> isCompleteFlag) {
    while (node != nullptr && !isCompleteFlag()) {
        std::cout << node->data << std::endl;

        // Execute action associated with the current node if not already executed
        if (actionMap.find(node->data) != actionMap.end() && !node->actionExecuted) {
            actionMap[node->data]();
            node->actionExecuted = true; // Mark action as executed
        }

        // Check if level is complete
        if (isCompleteFlag()) {
            std::cout << "Congratulations! You have completed this level." << std::endl;
            break;
        }

        // Check if the player is dead
        if (this->player.isDead()) {
            std::cout << "Game Over! You have been defeated." << std::endl;
            exit(0);
        }

        // Display options for the next scenes
        auto& children = node->getChildren();
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << (i + 1) << ": " << children[i]->data << std::endl;
        }

        // Get user input and validate choice
        int choice;
        std::cin >> choice;
        choice -= 1;

        if (choice >= 0 && choice < static_cast<int>(children.size())) {
            node = children[choice];
        } else {
            std::cout << "Invalid choice, try again." << std::endl;
        }
    }
}

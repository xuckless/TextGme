// BaseLevel.cpp
#include "BaseLevel.h"
#include <limits>

BaseLevel::BaseLevel() : player("Player 1", 100) {
    // Initialization moved to derived classes
}

BaseLevel::~BaseLevel() {
    delete scenarioHandler;
}

void BaseLevel::addAction(const std::string& description, std::function<void()> action) {
    actionMap[description] = action;
}

void BaseLevel::navigateDecisionTree(Scenes<std::string>* node, std::function<bool()> isCompleteFlag) {
    while (node != nullptr && !isCompleteFlag()) {
        std::cout << node->data << std::endl;

        // Execute any action associated with this scene's description only if not already executed
        if (actionMap.find(node->data) != actionMap.end() && !node->actionExecuted) {
            actionMap[node->data]();
            node->actionExecuted = true; // Mark the action as executed
        }

        // Check if the level is now marked complete, and break out of the loop if so
        if (isCompleteFlag()) {
            std::cout << " " << std::endl;
            break;
        }

        if (this->player.isDead()) {
            exit(0);
        }

        // Display options for the next scenes and get user input
        auto& children = node->getChildren();
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << (i + 1) << ": " << children[i]->data << std::endl;
        }

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

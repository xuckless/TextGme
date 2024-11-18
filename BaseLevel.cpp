//BaseLevel.cpp

#include "BaseLevel.h"
#include <limits>
#include <iostream>
#include "AsciiArt.h"


void displayEndeavorArt() {
    std::cout << AsciiArt::ENDEAVOR_ASCII << std::endl;
}
// Constructor
BaseLevel::BaseLevel(Player& player) : player(player) {
    // Initialize player with default values

    displayEndeavorArt();
    // Character selection at the start
    std::cout << "Choose your character:" << std::endl;
    std::cout << "1. Ban (Steal Life)" << std::endl;
    std::cout << "2. Gojo (Starts with more aura)" << std::endl;
    std::cout << "3. Madara (Deals extra damage)" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            player = Player::createCharacter("Ban");
            break;
        case 2:
            player = Player::createCharacter("Gojo");
            break;
        case 3:
            player = Player::createCharacter("Madara");
            break;
        default:
            std::cout << "Invalid choice. Defaulting to a generic player." << std::endl;
            player = Player::createCharacter("Default");
            break;
    }

    std::cout << "You have chosen: " << player.getName() << std::endl;
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

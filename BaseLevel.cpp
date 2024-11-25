// BaseLevel.cpp

#include "BaseLevel.h"
#include "AsciiArt.h"
#include <stack>
#include <limits>

void displayEndeavorArt() {
    std::cout << AsciiArt::ENDEAVOR_ASCII << std::endl;
}

// Constructor
BaseLevel::BaseLevel(std::shared_ptr<Player> player) : player(player) {
    displayEndeavorArt();
    // Character selection at the start

    std::cout << "Choose your character:" << std::endl;
    std::cout << "1. 🦊 Ban (Ability: Steal Life)" << std::endl;
    std::cout << "2. ⚪ Gojo (Ability: Starts with more aura)" << std::endl;
    std::cout << "3. 🔥 Madara (Ability: Deals extra damage)" << std::endl;
    std::cout << "4. For the default character without ability" << std::endl;

    int choice;
    while (true) {
        std::cout << "Enter your choice (1-4): ";
        if (!(std::cin >> choice)) {
            // Input failed, clear error flags and ignore the rest of the line
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            continue;
        }

        if (choice >= 1 && choice <= 4)
            break;
        else
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
    }

    switch (choice) {
        case 1:
            *player = Player::createCharacter("Ban");
            break;
        case 2:
            *player = Player::createCharacter("Gojo");
            break;
        case 3:
            *player = Player::createCharacter("Madara");
            break;
        case 4:
            *player = Player::createCharacter("Default");
            break;
        default:
            std::cout << "Invalid choice. Defaulting to a generic player." << std::endl;
            *player = Player::createCharacter("Default");
            break;
    }

    std::cout << "You have chosen: " << player->getName() << std::endl;
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
    std::stack<Scenes<std::string>*> nodeStack; // Stack to keep track of previous nodes

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
        if (this->player->isDead()) {
            std::cout << "Game Over! You have been defeated." << std::endl;
            exit(0);
        }

        // Display options for the next scenes
        auto& children = node->getChildren();

        // Determine if "Go Back" option should be available
        bool canGoBack = !nodeStack.empty();

        // Display child options
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << (i + 1) << ": " << children[i]->data << std::endl;
        }

        // If not at root, add "Go Back" option
        if (canGoBack) {
            std::cout << (children.size() + 1) << ": Go Back" << std::endl;
        }

        // Determine the valid range for user input
        int minChoice = 1;
        int maxChoice = children.size() + (canGoBack ? 1 : 0);

        int choice;
        while (true) {
            std::cout << "Enter your choice (" << minChoice << "-" << maxChoice << "): ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between " << minChoice << " and " << maxChoice << "." << std::endl;
                continue;
            }

            if (choice >= minChoice && choice <= maxChoice)
                break;
            else
                std::cout << "Invalid choice. Please enter a number between " << minChoice << " and " << maxChoice << "." << std::endl;
        }

        if (canGoBack && choice == static_cast<int>(children.size()) + 1) {
            // User chose to go back
            node = nodeStack.top();
            nodeStack.pop();
        } else {
            // Push the current node to the stack before moving to the next node
            nodeStack.push(node);
            // Adjust for zero-based indexing
            choice -= 1;
            node = children[choice];
        }
    }
}

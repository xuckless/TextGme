// BaseLevel.cpp
// Implements the BaseLevel class, which serves as an abstract base class for game levels.
// This class uses a decision tree to handle scenarios and allows player progression based on choices.

#include "BaseLevel.h"
#include "AsciiArt.h"
#include <stack>
#include <limits>

// Function to display ASCII art for visual appeal at the start of the game.
void displayEndeavorArt() {
    std::cout << AsciiArt::ENDEAVOR_ASCII << std::endl;
}

// Constructor: Initializes the BaseLevel with a shared Player instance.
// Displays ASCII art and handles character selection at the beginning of the level.
BaseLevel::BaseLevel(std::shared_ptr<Player> player) : player(player) {
    displayEndeavorArt();
    // Prompt player to choose their character.
    std::cout << "Choose your character:" << std::endl;
    std::cout << "1. 🦊 Ban (Ability: Steal Life)" << std::endl;
    std::cout << "2. ⚪ Gojo (Ability: Starts with more aura)" << std::endl;
    std::cout << "3. 🔥 Madara (Ability: Deals extra damage)" << std::endl;
    std::cout << "4. Default character without ability" << std::endl;

    int choice;
    while (true) {
        // Validate user input for character selection.
        std::cout << "Enter your choice (1-4): ";
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear invalid input flags.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input.
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            continue;
        }
        if (choice >= 1 && choice <= 4)
            break; // Exit loop for valid input.
        else
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
    }

    // Create the chosen character.
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

// Destructor: Cleans up resources, including the scenario handler.
BaseLevel::~BaseLevel() {
    delete scenarioHandler; // Free memory allocated to scenario handler.
}

// Adds a new action to the action map for the decision tree.
// The action is associated with a specific scenario description.
void BaseLevel::addAction(const std::string& description, std::function<void()> action) {
    actionMap[description] = action;
}

// Navigates the decision tree for the current level.
// Uses a stack to allow the player to "go back" to previous nodes.
void BaseLevel::navigateDecisionTree(Scenes<std::string>* node, std::function<bool()> isCompleteFlag) {
    std::stack<Scenes<std::string>*> nodeStack; // Stack for navigating back through the tree.

    while (node != nullptr && !isCompleteFlag()) {
        // Display the current scenario description.
        std::cout << node->data << std::endl;

        // Execute the associated action if it hasn't been executed already.
        if (actionMap.find(node->data) != actionMap.end() && !node->actionExecuted) {
            actionMap[node->data](); // Execute the action.
            node->actionExecuted = true; // Mark the action as executed.
        }

        // Check if the level is complete.
        if (isCompleteFlag()) {
            std::cout << "Congratulations! You have completed this level." << std::endl;
            break;
        }

        // Check if the player is dead.
        if (this->player->isDead()) {
            std::cout << "Game Over! You have been defeated." << std::endl;
            exit(0); // End the game.
        }

        // Display options for transitioning to the next scenes.
        auto& children = node->getChildren();
        bool canGoBack = !nodeStack.empty(); // Determine if "Go Back" option is available.

        // Display child nodes as options.
        for (size_t i = 0; i < children.size(); ++i) {
            std::cout << (i + 1) << ": " << children[i]->data << std::endl;
        }

        // If "Go Back" is an option, display it.
        if (canGoBack) {
            std::cout << (children.size() + 1) << ": Go Back" << std::endl;
        }

        // Validate user input for selecting the next node.
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
                break; // Exit loop for valid input.
            else
                std::cout << "Invalid choice. Please enter a number between " << minChoice << " and " << maxChoice << "." << std::endl;
        }

        if (canGoBack && choice == static_cast<int>(children.size()) + 1) {
            // Go back to the previous node.
            node = nodeStack.top();
            nodeStack.pop();
        } else {
            // Push the current node onto the stack before moving to the next node.
            nodeStack.push(node);
            node = children[choice - 1]; // Move to the chosen child node (adjust for zero-based index).
        }
    }
}
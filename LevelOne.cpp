//LevelOne.cpp

#include "LevelOne.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilities.h"

// Constructor
LevelOne::LevelOne(std::shared_ptr<Player> player)
    : BaseLevel(player), isComplete(false), enemy("Nightmare", 200) {
    setUpDecisionTree();
}

// Setup Decision Tree
void LevelOne::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>("Welcome to Level One");

    // Create the first branching path with a "Look around" prompt
    auto lookAround = scenarioHandler->addChild(scenarioHandler->root, "Look around");
    auto rareChest = scenarioHandler->addChild(lookAround, "Open the Rare Chest");
    auto chestOpenRare = scenarioHandler->addChild(rareChest, "Chest Open, continue to the door");
    auto nextRoom = scenarioHandler->addChild(lookAround, "Open the door");

    // Link "chestOpenRare" to "nextRoom" to allow progression
    scenarioHandler->linkChild(chestOpenRare, nextRoom);

    // Add an action to "chestOpenRare" for a Rare Chest
    addChestAction("Chest Open, continue to the door", 75, "Rare");

    // Create another branching path within the "nextRoom" scenario
    auto newLookAround = scenarioHandler->addChild(nextRoom, "Look around - Press 1");
    auto legendaryChest = scenarioHandler->addChild(newLookAround, "Open the Legendary Chest");
    auto chestOpenLegendary = scenarioHandler->addChild(legendaryChest, "Chest Open, continue to the hallway");
    auto hallway = scenarioHandler->addChild(newLookAround, "Go to the end of the hallway");

    // Link "chestOpenLegendary" to "hallway" for continuity
    scenarioHandler->linkChild(chestOpenLegendary, hallway);

    // Add an action to "chestOpenLegendary" for a Legendary Chest
    addChestAction("Chest Open, continue to the hallway", 150, "Legendary");

    // Boss Room Setup
    auto bossRoom = scenarioHandler->addChild(hallway, "You are approaching the boss room! Continue");
    auto peek = scenarioHandler->addChild(bossRoom, "Peek at the boss");
    auto noPeek = scenarioHandler->addChild(bossRoom, "Run away (Nowhere to go)");

    // Link "noPeek" back to "hallway" for a loop
    scenarioHandler->linkChild(noPeek, hallway);

    // Define the final boss battle scenario
    auto complete = scenarioHandler->addChild(peek, "Battle the boss");
    addAction("Battle the boss", [this]() {
        battleBoss();
    });

    auto progression = scenarioHandler->addChild(complete, "Complete Level");

    // Mark level as complete
    addAction("Complete Level", std::bind(&LevelOne::completeLevel, this));
}

// Add Chest Action with Rewards
void LevelOne::addChestAction(const std::string& actionName, int auraReward, const std::string& chestType) {
    addAction(actionName, [this, auraReward, chestType]() {
        player->increaseAura(auraReward);
        std::cout << "You opened a " << chestType << " Chest! Aura increased by " << auraReward << "!" << std::endl;
    });
}

// Boss Battle Logic
void LevelOne::battleBoss() {
    std::cout << "The boss, " << enemy.getName() << ", stands before you!" << std::endl;

    while (!player->isDead() && !enemy.isDead()) {
        std::cout << "Choose your action: (actual aura)" << player->getAura() << std::endl;
        std::cout << "1. Attack (Cost: 50 Aura)" << std::endl;
        std::cout << "2. Heal (Cost: 30 Aura)" << std::endl;
        std::cout << "3. Use Ability" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 50) {
                    int damage = (player->getName() == "Madara") ? (rand() % 20 + 30) : (rand() % 20 + 10);
                    enemy.decreaseHealth(damage);
                    player->decreaseAura(50);
                } else {
                    std::cout << "Not enough aura to attack!" << std::endl;
                }
                break;

            case 2:
                if (player->getAura() >= 30) {
                    player->increaseHealth(20);
                    player->decreaseAura(30);
                } else {
                    std::cout << "Not enough aura to heal!" << std::endl;
                }
                break;

            case 3:
                player->useAbility(enemy); // Pass the enemy instance
                break;

            default:
                std::cout << "Invalid action. Try again!" << std::endl;
                break;
        }

        if (!enemy.isDead()) {
            int enemyAction = rand() % 3; // Randomly choose between 0, 1, or 2

            switch (enemyAction) {
                case 0: { // Enemy attacks
                    int damage = enemy.attack();
                    player->decreaseHealth(damage);
                    break;
                }
                case 1: { // Enemy heals
                    enemy.heal();
                    break;
                }
                case 2: { // Enemy defends
                    enemy.defend();
                    break;
                }
                default:
                    std::cout << enemy.getName() << " seems confused and does nothing!" << std::endl;
                    break;
            }
        }
    }

    if (enemy.isDead()) {
        std::cout << "You have defeated the boss! Congratulations " << player->getName() << std::endl;
    } else if (player->isDead()) {
        std::cout << "You have been defeated by the boss..." << std::endl;
    }
}

// Complete Level
void LevelOne::completeLevel() {
    std::cout << "Level One Complete!" << std::endl;
    this->isComplete = true;
}

// Proceed with Scenario Navigation
void LevelOne::proceed() {
    // Display level transition
    displayLevelTransition(1);

    std::cout << "Starting Level One..." << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}


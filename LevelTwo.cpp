#include "LevelTwo.h"
#include <iostream>
#include <cstdlib>
#include "Utilities.h"
#include <ctime>

// Constructor
LevelTwo::LevelTwo(Player& player) : BaseLevel(player), isComplete(false), enemy("Ancient Dragon", 300) {
    setUpDecisionTree();
}

void LevelTwo::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>("Welcome to Level Two");

    // Initial Scenario: Crossroads
    auto crossroads = scenarioHandler->addChild(scenarioHandler->root, "You arrive at a crossroads. Do you go left or right?");
    auto leftPath = scenarioHandler->addChild(crossroads, "Go left");
    auto rightPath = scenarioHandler->addChild(crossroads, "Go right");

    // Left Path Scenarios
    auto leftEncounter = scenarioHandler->addChild(leftPath, "You encounter a mysterious merchant");
    auto tradeOption = scenarioHandler->addChild(leftEncounter, "Trade with the merchant");
    auto ignoreMerchant = scenarioHandler->addChild(leftEncounter, "Ignore the merchant and continue");

    // Trade Action
    addAction("Trade with the merchant", [this]() {
        std::cout << "The merchant offers you a choice:" << std::endl;
        std::cout << "1. Buy a health potion (Cost: 50 Aura)" << std::endl;
        std::cout << "2. Buy a Mystical Artifact (Cost: 100 Aura)" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            if (player.getAura() >= 50) {
                player.decreaseAura(50);
                player.increaseHealth(50);
                std::cout << "You bought a health potion and restored 50 health!" << std::endl;
            } else {
                std::cout << "Not enough aura to buy the health potion." << std::endl;
            }
        } else if (choice == 2) {
            if (player.getAura() >= 100) {
                player.decreaseAura(100);
                player.acquireArtifact("Mystical Artifact");
                std::cout << "You acquired a Mystical Artifact! It might come in handy later." << std::endl;
            } else {
                std::cout << "Not enough aura to buy the Mystical Artifact." << std::endl;
            }
        } else {
            std::cout << "Invalid choice. The merchant disappears." << std::endl;
        }
    });

    // Continue Left Path
    auto leftContinue = scenarioHandler->addChild(tradeOption, "Continue down the left path");
    scenarioHandler->linkChild(ignoreMerchant, leftContinue);

    // Add a chest on the left path
    auto leftChest = scenarioHandler->addChild(leftContinue, "You find a chest on the side of the road");
    auto openLeftChest = scenarioHandler->addChild(leftChest, "Open the chest");
    auto leftChestOpened = scenarioHandler->addChild(openLeftChest, "Chest opened, continue on your way");

    // Link leftChestOpened to next scenario
    scenarioHandler->linkChild(leftChestOpened, leftContinue);

    // Add chest action
    addChestAction("Chest opened, continue on your way", 75, "Rare");

    // Puzzle Challenge
    auto puzzleChallenge = scenarioHandler->addChild(leftContinue, "You encounter an ancient puzzle door");
    auto attemptPuzzle = scenarioHandler->addChild(puzzleChallenge, "Attempt to solve the puzzle");
    auto forceDoor = scenarioHandler->addChild(puzzleChallenge, "Try to force the door open");

    addAction("Attempt to solve the puzzle", [this]() {
        std::cout << "To open the door, you must solve a riddle:" << std::endl;
        std::cout << "'I speak without a mouth and hear without ears. I have nobody, but I come alive with wind. What am I?'" << std::endl;
        std::string answer;
        std::cin.ignore();
        std::getline(std::cin, answer);

        if (answer == "Echo" || answer == "echo" || answer == "An echo" || answer == "an echo") {
            std::cout << "Correct! The door opens." << std::endl;
            player.increaseAura(100);
            std::cout << "You gained 100 aura for solving the puzzle!" << std::endl;
        } else {
            std::cout << "Incorrect. The door remains closed." << std::endl;
            std::cout << "You decide to try forcing the door open." << std::endl;
            // Proceed to forceDooraa
        }
    });

    addAction("Try to force the door open", [this]() {
        std::cout << "You attempt to force the door open..." << std::endl;
        if (player.getStrength() >= 50) {
            std::cout << "Using your strength, you break the door open." << std::endl;
        } else {
            std::cout << "You are not strong enough. You hurt yourself in the attempt." << std::endl;
            player.decreaseHealth(20);
        }
    });

    // Right Path Scenarios
    auto rightEncounter = scenarioHandler->addChild(rightPath, "You walk into a dark forest");
    auto exploreForest = scenarioHandler->addChild(rightEncounter, "Explore the forest");
    auto avoidForest = scenarioHandler->addChild(rightEncounter, "Avoid the forest and continue");

    // Forest Chest
    auto forestChest = scenarioHandler->addChild(exploreForest, "You find a chest hidden among the trees");
    auto openForestChest = scenarioHandler->addChild(forestChest, "Open the chest");
    auto forestChestOpened = scenarioHandler->addChild(openForestChest, "Chest opened, proceed deeper into the forest");

    // Link forestChestOpened to next scenario
    scenarioHandler->linkChild(forestChestOpened, exploreForest);

    // Add chest action
    addChestAction("Chest opened, proceed deeper into the forest", 50, "Common");

    // Forest Battle
    auto forestBattle = scenarioHandler->addChild(exploreForest, "You are ambushed by forest bandits!");
    addAction("You are ambushed by forest bandits!", [this]() {
        battleBandits();
    });

    // Continue Right Path
    auto rightContinue = scenarioHandler->addChild(forestBattle, "Continue down the right path");
    scenarioHandler->linkChild(avoidForest, rightContinue);

    // Paths Merge
    auto pathsMerge = scenarioHandler->addChild(leftContinue, "The paths merge");
    scenarioHandler->linkChild(rightContinue, pathsMerge);

    // Boss Encounter
    auto bossEncounter = scenarioHandler->addChild(pathsMerge, "You reach the dragon's lair");
    auto battleDragon = scenarioHandler->addChild(bossEncounter, "Battle the Ancient Dragon");

    addAction("Battle the Ancient Dragon", [this]() {
        battleBoss();
    });

    auto levelComplete = scenarioHandler->addChild(battleDragon, "Complete Level");

    addAction("Complete Level", std::bind(&LevelTwo::completeLevel, this));
}

// Battle with Bandits
void LevelTwo::battleBandits() {
    Enemy bandit("Bandit", 100);
    std::cout << "You are attacked by a bandit!" << std::endl;

    while (!player.isDead() && !bandit.isDead()) {
        // Player's turn
        std::cout << "Choose your action:" << std::endl;
        std::cout << "1. Attack (Cost: 30 Aura)" << std::endl;
        std::cout << "2. Defend (Cost: 20 Aura)" << std::endl;
        std::cout << "3. Run away" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1 && player.getAura() >= 30) {
            int damage = rand() % 15 + 10;
            bandit.decreaseHealth(damage);
            player.decreaseAura(30);
        } else if (choice == 2 && player.getAura() >= 20) {
            std::cout << "You defend against the next attack." << std::endl;
            player.decreaseAura(20);
            // Implement defense logic
        } else if (choice == 3) {
            std::cout << "You attempt to run away..." << std::endl;
            if (rand() % 2 == 0) {
                std::cout << "You successfully escaped!" << std::endl;
                return;
            } else {
                std::cout << "You failed to escape!" << std::endl;
            }
        } else {
            std::cout << "Invalid choice or insufficient aura." << std::endl;
        }

        // Bandit's turn
        if (!bandit.isDead()) {
            int damage = rand() % 10 + 5;
            player.decreaseHealth(damage);
            std::cout << "The bandit attacks you for " << damage << " damage!" << std::endl;
        }
    }

    if (bandit.isDead()) {
        std::cout << "You have defeated the bandit!" << std::endl;
        player.increaseAura(50);
        std::cout << "You gained 50 aura." << std::endl;
    } else if (player.isDead()) {
        std::cout << "You have been defeated by the bandit..." << std::endl;
    }
}

// Boss Battle Logic
void LevelTwo::battleBoss() {
    std::cout << "The Ancient Dragon, " << enemy.getName() << ", looms before you!" << std::endl;

    // Check for Mystical Artifact
    if (player.hasArtifact("Mystical Artifact")) {
        std::cout << "Your Mystical Artifact glows, weakening the dragon!" << std::endl;
        enemy.decreaseHealth(50);
    }

    while (!player.isDead() && !enemy.isDead()) {
        std::cout << "Choose your action: (Current aura: " << player.getAura() << ")" << std::endl;
        std::cout << "1. Attack (Cost: 60 Aura)" << std::endl;
        std::cout << "2. Heal (Cost: 40 Aura)" << std::endl;
        std::cout << "3. Use Ability" << std::endl;
        std::cout << "4. Use Mystical Artifact" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player.getAura() >= 60) {
                    int damage = (player.getName() == "Madara") ? (rand() % 30 + 40) : (rand() % 25 + 15);
                    enemy.decreaseHealth(damage);
                    player.decreaseAura(60);
                } else {
                    std::cout << "Not enough aura to attack!" << std::endl;
                }
                break;
            case 2:
                if (player.getAura() >= 40) {
                    player.increaseHealth(30);
                    player.decreaseAura(40);
                } else {
                    std::cout << "Not enough aura to heal!" << std::endl;
                }
                break;
            case 3:
                player.useAbility(enemy);
                break;
            case 4:
                if (player.hasArtifact("Mystical Artifact")) {
                    std::cout << "You use the Mystical Artifact to unleash a powerful attack!" << std::endl;
                    enemy.decreaseHealth(100);
                    player.removeArtifact("Mystical Artifact");
                    std::cout << "The Mystical Artifact shatters after use." << std::endl;
                } else {
                    std::cout << "You don't have the Mystical Artifact!" << std::endl;
                }
                break;
            default:
                std::cout << "Invalid action. Try again!" << std::endl;
                break;
        }

        if (!enemy.isDead()) {
            int enemyAction = rand() % 3;

            switch (enemyAction) {
                case 0: { // Enemy attacks
                    int damage = enemy.attack();
                    player.decreaseHealth(damage);
                    break;
                }
                case 1: { // Enemy breathes fire
                    std::cout << enemy.getName() << " breathes fire!" << std::endl;
                    int damage = rand() % 40 + 20;
                    player.decreaseHealth(damage);
                    break;
                }
                case 2: { // Enemy heals
                    enemy.heal();
                    break;
                }
                default:
                    std::cout << enemy.getName() << " hesitates and does nothing!" << std::endl;
                    break;
            }
        }
    }

    if (enemy.isDead()) {
        std::cout << "You have defeated the Ancient Dragon!" << std::endl;
    } else if (player.isDead()) {
        std::cout << "You have been defeated by the Ancient Dragon..." << std::endl;
    }
}

// Complete Level
void LevelTwo::completeLevel() {
    std::cout << "Level Two Complete!" << std::endl;
    this->isComplete = true;
}

// Proceed with Scenario Navigation
void LevelTwo::proceed() {
    // Display level transition
    displayLevelTransition(2);

    std::cout << "Starting Level Two..." << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

// Add Chest Action with Rewards
void LevelTwo::addChestAction(const std::string& actionName, int auraReward, const std::string& chestType) {
    addAction(actionName, [this, auraReward, chestType]() {
        player.increaseAura(auraReward);
        std::cout << "You opened a " << chestType << " Chest! Aura increased by " << auraReward << "!" << std::endl;
    });
}

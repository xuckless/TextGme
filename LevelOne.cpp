// LevelOne.cpp
#include "LevelOne.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilities.h"

// Constructor remains unchanged
LevelOne::LevelOne(std::shared_ptr<Player> player)
    : BaseLevel(player), isComplete(false), enemy("Nightmare", 250),
      hasKey(false), chestOpened(false), isDefending(false) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed
    setUpDecisionTree();
}

// Destructor remains unchanged
LevelOne::~LevelOne() {
    delete scenarioHandler;
}

// Updated helper function implementation
Scenes<std::string>* LevelOne::addInspectionOption(const std::string& optionText,
                                                    const std::string& actionText,
                                                    Scenes<std::string>* parent,
                                                    int auraBoost) {
    // Add the inspection option as a child of the parent node
    Scenes<std::string>* inspectionNode = scenarioHandler->addChild(parent, optionText);

    // Define the action for the inspection with corrected lambda capture and auraBoost
    addAction(optionText, [this, actionText, optionText, auraBoost]() {
        std::cout << actionText << std::endl;
        // Perform any specific logic based on the inspection
        if (optionText.find("chest") != std::string::npos && !chestOpened) {
            std::cout << "You attempt to open the chest..." << std::endl;
            // Example logic: player finds a key or aura
            if (auraBoost > 0) {
                player->increaseAura(auraBoost);
                std::cout << "Inside the chest, you find an aura crystal! Your aura increases by "
                          << auraBoost << "!" << std::endl;
            } else {
                hasKey = true;
                chestOpened = true;
                std::cout << "Inside the chest, you find a small, rusty key!" << std::endl;
            }
        }
        else if (optionText.find("straw") != std::string::npos) {
            std::cout << "You sift through the pile of straw and find nothing of interest." << std::endl;
        }
        else if (optionText.find("altar") != std::string::npos) {
            std::cout << "You approach the ancient altar..." << std::endl;
            player->increaseAura(auraBoost);
            std::cout << "A surge of energy flows through you! Your aura increases by "
                      << auraBoost << "!" << std::endl;
        }
        // Add more conditions as needed for different interactions
    });

    // Link the inspection node back to "Choose your path"
    Scenes<std::string>* choosePathNode = scenarioHandler->getChildByData("Choose your path");
    if (choosePathNode != nullptr) {
        scenarioHandler->linkChild(inspectionNode, choosePathNode);
    } else {
        std::cerr << "Error: 'Choose your path' node not found!" << std::endl;
    }

    return inspectionNode;
}


// LevelOne.cpp

// LevelOne.cpp

void LevelOne::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>(
        "You find yourself in a dimly lit dungeon cell. The air is damp, and the walls are covered with moss."
    );

    // First scene: The starting cell
    auto lookAround = scenarioHandler->addChild(scenarioHandler->root, "Look around the cell");
    addAction("Look around the cell", [this]() {
        std::cout << "You see a rusty door, an old wooden chest, and a pile of straw in the corner." << std::endl;
    });

    // **Create "Choose your path" node first**
    auto choosePath = scenarioHandler->addChild(lookAround, "Choose your path");
    addAction("Choose your path", [this]() {
        std::cout << "Will you try to unlock the door with the key, or descend through the trapdoor?" << std::endl;
    });

    // Now add inspection options, which can link back to "Choose your path"
    addInspectionOption("Inspect the wooden chest",
                        "The wooden chest is old and worn. It seems to be locked.",
                        lookAround, 0); // No aura boost, just a key
    addInspectionOption("Inspect the pile of straw",
                        "The pile of straw looks undisturbed. There's nothing valuable here.",
                        lookAround, 0);

    // Additional inspection options
    auto inspectHiddenDoor = scenarioHandler->addChild(lookAround, "Inspect the hidden door");
    addAction("Inspect the hidden door", [this]() {
        std::cout << "A concealed door partially opens as you touch the wall." << std::endl;
    });

    // Use the helper function to add an aura-boosting interaction behind the hidden door
    addInspectionOption("Inspect the ancient altar",
                        "You place your hands on the altar, feeling a warm energy flow into you.",
                        inspectHiddenDoor, 50); // Aura boost of 50

    // Inspect aura stone behind the altar
    addInspectionOption("Inspect the aura stone",
                        "The aura stone glows with a mystical light, pulsating with energy.",
                        inspectHiddenDoor, 30); // Aura boost of 30

    // Door interaction
    auto inspectDoor = scenarioHandler->addChild(lookAround, "Inspect the rusty door");
    addAction("Inspect the rusty door", [this]() {
        std::cout << "The door is locked from the outside. You might need a key or another way to open it." << std::endl;
    });

    // Define "Use the key on the door" node
    auto useKeyOnDoor = scenarioHandler->addChild(choosePath, "Use the key on the door");
    addAction("Use the key on the door", [this]() {
        if (hasKey) {
            std::cout << "You use the key to unlock the door. It creaks open, revealing a dimly lit hallway." << std::endl;
            // Unlock the door logic here (e.g., set a flag)
        } else {
            std::cout << "You don't have a key to unlock the door."  << std::endl;
        }
    });

    // Define "Proceed through the door" node
    auto proceedThroughDoor = scenarioHandler->addChild(useKeyOnDoor, "Proceed through the door");
    addAction("Proceed through the door", [this]() {
        if (hasKey) {
            std::cout << "You enter the hallway. The walls are lined with torches, and you hear distant sounds." << std::endl;
        } else {
            std::cout  << "You cannot proceed through the door without unlocking it first." << std::endl;
        }
    });

    // Define "Proceed through the tunnel" node
    auto proceedThroughTunnel = scenarioHandler->addChild(choosePath, "Proceed through the tunnel");
    addAction("Proceed through the tunnel", [this]() {
        std::cout << "You walk through the dark tunnel. The air is musty, and you feel uneasy." << std::endl;
    });

    auto tunnel = scenarioHandler->addChild(proceedThroughTunnel, "Explore the tunnel");
    auto findSecretRoom = scenarioHandler->addChild(tunnel, "Find a secret room");

    // Secret room
    addAction("Find a secret room", [this]() {
        std::cout << "You discover a hidden room filled with ancient artifacts." << std::endl;
        player->increaseAura(100);
        std::cout << "Your aura increases significantly by 100!" << std::endl;
    });

    auto proceedToBoss = scenarioHandler->addChild(findSecretRoom, "Proceed to the boss chamber");
    addAction("Proceed to the boss chamber", [this]() {
        std::cout << "You walk further into the dungeon, approaching the boss chamber." << std::endl;
    });

    // Boss interaction
    addAction("Proceed to the boss chamber", [this]() {
        std::cout << "You enter a large chamber. The boss, " << enemy.getName() << ", awaits you." << std::endl;
    });

    auto battleBossNode = scenarioHandler->addChild(proceedToBoss, "Confront the boss");
    addAction("Confront the boss", [this]() {
        battleBoss();
    });

    // After defeating the boss
    auto collectReward = scenarioHandler->addChild(battleBossNode, "Collect your reward");
    addAction("Collect your reward", [this]() {
        std::cout << "You find a treasure chest containing a powerful artifact!" << std::endl;
        player->acquireArtifact("Amulet of Strength");
        std::cout << "Your strength has increased by 20!" << std::endl;
        player->increaseStrength(20);
    });

    auto completeLevelNode = scenarioHandler->addChild(collectReward, "Exit the dungeon");
    addAction("Exit the dungeon", [this]() {
        completeLevel();
    });

    // Link "Try to force the door open" back to "Choose your path"
    // Ensure that this option is meaningful and not duplicated

    // Optional: Add "Go Back" option after failing to force the door open
    // Instead of duplicating "Proceed through the door", provide distinct options
    auto tryToOpenDoor = scenarioHandler->addChild(inspectDoor, "Try to force the door open");
    addAction("Try to force the door open", [this]() {
        std::cout << "You try to force the door open, but it's too sturdy. You need to find another way." << std::endl;
    });

    auto goBackFromForceDoor = scenarioHandler->addChild(tryToOpenDoor, "Go back to Choose your path");
    addAction("Go back to Choose your path", [this]() {
        std::cout << "You decide to explore other options available to you." << std::endl;
    });

    // Link "Go back to Choose your path" to "Choose your path" node
    scenarioHandler->linkChild(goBackFromForceDoor, choosePath);
}


// Battle with a guard
void LevelOne::battleGuard() {
    Enemy guard("Dungeon Guard", 100);
    std::cout << "You engage in battle with the " << guard.getName() << "!" << std::endl;

    while (!player->isDead() && !guard.isDead()) {
        std::cout << "\nChoose your action: (Current Aura: " << player->getAura() << ")\n";
        std::cout << "1. Attack (Cost: 30 Aura)\n";
        std::cout << "2. Heal (Cost: 20 Aura)\n";
        std::cout << "3. Use Ability\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 30) {
                    int damage = player->attack();
                    guard.decreaseHealth(damage);
                    player->decreaseAura(30);
                } else {
                    std::cout << "Not enough aura to attack!" << std::endl;
                }
                break;

            case 2:
                if (player->getAura() >= 20) {
                    player->increaseHealth(15);
                    player->decreaseAura(20);
                } else {
                    std::cout << "Not enough aura to heal!" << std::endl;
                }
                break;

            case 3:
                player->useAbility(guard);
                break;

            default:
                std::cout << "Invalid action. Try again!" << std::endl;
                continue;
        }

        if (!guard.isDead()) {
            int damage = guard.attack();
            player->decreaseHealth(damage);
        }
    }

    if (guard.isDead()) {
        std::cout << "You have defeated the " << guard.getName() << "!" << std::endl;
    } else if (player->isDead()) {
        std::cout << "You have been defeated by the " << guard.getName() << "..." << std::endl;
        exit(0);
    }
}

// Boss Battle Logic
void LevelOne::battleBoss() {
    std::cout << enemy.getName() << " snarls and prepares to attack!" << std::endl;

    while (!player->isDead() && !enemy.isDead()) {
        std::cout << "\nChoose your action: (Current Aura: " << player->getAura() << ")\n";
        std::cout << "1. Attack (Cost: 50 Aura)\n";
        std::cout << "2. Heal (Cost: 30 Aura)\n";
        std::cout << "3. Use Ability\n";
        std::cout << "4. Defend\n";
        std::cout << "5. Special Move\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 50) {
                    int damage = player->attack();
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
                player->useAbility(enemy);
                break;

            case 4:
                defendPlayer();
                break;

            case 5:
                specialMove();
                break;

            default:
                std::cout << "Invalid action. Try again!" << std::endl;
                continue;
        }

        if (!enemy.isDead()) {
            enemyTurn();
        }
    }

    if (enemy.isDead()) {
        std::cout << "You have defeated " << enemy.getName() << "!" << std::endl;
    } else if (player->isDead()) {
        std::cout << "You have been defeated..." << std::endl;
        exit(0);
    }
}

// Additional Player Actions
void LevelOne::defendPlayer() {
    std::cout << "You brace yourself, reducing damage from the next attack." << std::endl;
    isDefending = true;
}

void LevelOne::specialMove() {
    if (player->getAura() >= 100) {
        int damage = player->getStrength() * 2;
        std::cout << "You unleash a powerful special move, dealing " << damage << " damage to " << enemy.getName() << "!" << std::endl;
        enemy.decreaseHealth(damage);
        player->decreaseAura(100);
    } else {
        std::cout << "Not enough aura to perform a special move!" << std::endl;
    }
}

// Enemy's Turn Logic
void LevelOne::enemyTurn() {
    int enemyAction = rand() % 2; // Randomly choose between attack or special attack

    switch (enemyAction) {
        case 0: { // Enemy attacks
            int damage = enemy.attack();
            if (isDefending) {
                damage /= 2;
                std::cout << "Your defense reduces the damage to " << damage << "!" << std::endl;
                isDefending = false; // Reset defense
            }
            player->decreaseHealth(damage);
            break;
        }
        case 1: { // Enemy uses special attack
            int damage = enemy.specialAttack();
            if (isDefending) {
                damage /= 2;
                std::cout << "Your defense reduces the damage to " << damage << "!" << std::endl;
                isDefending = false; // Reset defense
            }
            player->decreaseHealth(damage);
            break;
        }
        default:
            std::cout << enemy.getName() << " hesitates and does nothing!" << std::endl;
            break;
    }
}

// Complete Level
void LevelOne::completeLevel() {
    std::cout << "You have successfully escaped the dungeon. Level One Complete!" << std::endl;
    this->isComplete = true;
}

// Proceed with Scenario Navigation
void LevelOne::proceed() {
    // Display level transition
    displayLevelTransition(1);

    std::cout << "Starting Level One..." << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

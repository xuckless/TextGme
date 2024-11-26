#include "LevelOne.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilities.h"

// Constructor: Initializes Level One, sets up the decision tree, and other state variables.
LevelOne::LevelOne(std::shared_ptr<Player> player)
    : BaseLevel(player), isComplete(false), enemy("Nightmare", 250),
      hasKey(false), chestOpened(false), isDefending(false) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed for randomness.
    setUpDecisionTree(); // Configure the scenario decision tree for the level.
}

// Destructor: Cleans up dynamically allocated memory for the scenario handler.
LevelOne::~LevelOne() {
    delete scenarioHandler; // Delete scenarioHandler to prevent memory leaks.
}

// Helper function: Adds an inspection option to the decision tree.
// Includes logic for aura boosts, finding keys, or other interactions.
Scenes<std::string>* LevelOne::addInspectionOption(const std::string& optionText,
                                                    const std::string& actionText,
                                                    Scenes<std::string>* parent,
                                                    int auraBoost) {
    // Add the inspection node to the parent.
    Scenes<std::string>* inspectionNode = scenarioHandler->addChild(parent, optionText);

    // Define the action for the inspection option.
    addAction(optionText, [this, actionText, optionText, auraBoost]() {
        std::cout << actionText << std::endl;

        if (optionText.find("chest") != std::string::npos && !chestOpened) {
            std::cout << "You attempt to open the chest..." << std::endl;
            if (auraBoost > 0) {
                player->increaseAura(auraBoost);
                std::cout << "Inside the chest, you find an aura crystal! Aura increased by " << auraBoost << "." << std::endl;
            } else {
                hasKey = true;
                chestOpened = true;
                std::cout << "Inside the chest, you find a rusty key!" << std::endl;
            }
        } else if (optionText.find("altar") != std::string::npos) {
            player->increaseAura(auraBoost);
            std::cout << "The altar's energy boosts your aura by " << auraBoost << "." << std::endl;
        }
    });

    // Link the inspection node back to the "Choose your path" node if it exists.
    Scenes<std::string>* choosePathNode = scenarioHandler->getChildByData("Choose your path");
    if (choosePathNode != nullptr) {
        scenarioHandler->linkChild(inspectionNode, choosePathNode);
    } else {
        std::cerr << "Error: 'Choose your path' node not found!" << std::endl;
    }

    return inspectionNode;
}

// Sets up the decision tree for Level One.
void LevelOne::setUpDecisionTree() {
    // Root node: Describes the starting point of the level.
    scenarioHandler = new ScenarioHandler<std::string>(
        "You find yourself in a dimly lit dungeon cell. The air is damp, and the walls are covered with moss."
    );

    auto lookAround = scenarioHandler->addChild(scenarioHandler->root, "Look around the cell");
    addAction("Look around the cell", [this]() {
        std::cout << "You see a rusty door, an old wooden chest, and a pile of straw in the corner." << std::endl;
    });

    // Create "Choose your path" node.
    auto choosePath = scenarioHandler->addChild(lookAround, "Choose your path");
    addAction("Choose your path", [this]() {
        std::cout << "Will you try to unlock the door with the key, or descend through the trapdoor?" << std::endl;
    });

    // Add interactive inspection options.
    addInspectionOption("Inspect the wooden chest", "The chest is old and locked.", lookAround, 0);
    addInspectionOption("Inspect the pile of straw", "The straw pile seems undisturbed.", lookAround, 0);
    addInspectionOption("Inspect the ancient altar", "The altar emits a faint glow.", lookAround, 50);

    // Door interaction node.
    auto inspectDoor = scenarioHandler->addChild(lookAround, "Inspect the rusty door");
    addAction("Inspect the rusty door", [this]() {
        std::cout << "The door is locked from the outside. You might need a key to open it." << std::endl;
    });

    // Use the key to unlock the door.
    auto useKeyOnDoor = scenarioHandler->addChild(choosePath, "Use the key on the door");
    addAction("Use the key on the door", [this]() {
        if (hasKey) {
            std::cout << "The door creaks open, revealing a dimly lit hallway." << std::endl;
        } else {
            std::cout << "You don't have a key to unlock the door." << std::endl;
        }
    });

    // Add paths to continue through the dungeon.
    auto proceedThroughTunnel = scenarioHandler->addChild(choosePath, "Proceed through the tunnel");
    addAction("Proceed through the tunnel", [this]() {
        std::cout << "You walk through the dark tunnel, feeling uneasy." << std::endl;
    });

    // Define secret interactions.
    auto findSecretRoom = scenarioHandler->addChild(proceedThroughTunnel, "Find a secret room");
    addAction("Find a secret room", [this]() {
        player->increaseAura(100);
        std::cout << "You find a hidden room filled with artifacts. Aura increased by 100!" << std::endl;
    });

    auto proceedToBoss = scenarioHandler->addChild(findSecretRoom, "Proceed to the boss chamber");
    addAction("Proceed to the boss chamber", [this]() {
        std::cout << "You approach the boss chamber, ready for battle." << std::endl;
    });

    // Confront the boss and link the completion path.
    auto battleBossNode = scenarioHandler->addChild(proceedToBoss, "Confront the boss");
    addAction("Confront the boss", [this]() {
        battleBoss();
    });

    auto collectReward = scenarioHandler->addChild(battleBossNode, "Collect your reward");
    addAction("Collect your reward", [this]() {
        player->acquireArtifact("Amulet of Strength");
        player->increaseStrength(20);
        std::cout << "You acquired the Amulet of Strength! Strength increased by 20." << std::endl;
    });

    auto completeLevelNode = scenarioHandler->addChild(collectReward, "Exit the dungeon");
    addAction("Exit the dungeon", [this]() {
        completeLevel();
    });
}

// Handles combat with a dungeon guard.
void LevelOne::battleGuard() {
    Enemy guard("Dungeon Guard", 100);
    std::cout << "You engage the " << guard.getName() << "!" << std::endl;

    while (!player->isDead() && !guard.isDead()) {
        std::cout << "Choose your action:\n1. Attack\n2. Heal\n3. Use Ability\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 30) {
                    guard.decreaseHealth(player->attack());
                    player->decreaseAura(30);
                }
                break;
            case 2:
                if (player->getAura() >= 20) {
                    player->increaseHealth(15);
                    player->decreaseAura(20);
                }
                break;
            case 3:
                player->useAbility(guard);
                break;
        }

        if (!guard.isDead()) {
            player->decreaseHealth(guard.attack());
        }
    }
}

// Handles the boss battle sequence.
void LevelOne::battleBoss() {
    while (!player->isDead() && !enemy.isDead()) {
        std::cout << "Choose your action:\n1. Attack\n2. Heal\n3. Use Ability\n4. Defend\n5. Special Move\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 50) {
                    enemy.decreaseHealth(player->attack());
                    player->decreaseAura(50);
                }
                break;
            case 2:
                if (player->getAura() >= 30) {
                    player->increaseHealth(20);
                    player->decreaseAura(30);
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
        }

        if (!enemy.isDead()) {
            enemyTurn();
        }
    }

    if (enemy.isDead()) {
        std::cout << "You defeated " << enemy.getName() << "!" << std::endl;
    } else {
        std::cout << "You were defeated..." << std::endl;
        exit(0);
    }
}

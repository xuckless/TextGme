// LevelTwo.cpp
#include "LevelTwo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilities.h" // Assuming there is a Utilities.h for utility functions

// Constructor
LevelTwo::LevelTwo(std::shared_ptr<Player> player)
    : BaseLevel(player), isComplete(false), enemy("Forest Guardian", 300), isDefending(false) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed
    setUpDecisionTree();
}

// Destructor
LevelTwo::~LevelTwo() {
    delete scenarioHandler;
}

void LevelTwo::setUpDecisionTree() {
    // Initialize the scenario handler with the starting scene description
    scenarioHandler = new ScenarioHandler<std::string>(
        "You emerge from the dungeon into an enchanted forest. The trees are tall and the air is filled with magical energy. 🌲✨"
    );

    // First scene: At the forest entrance
    auto exploreForest = scenarioHandler->addChild(scenarioHandler->root, "Explore the forest");
    addAction("Explore the forest", [this]() {
        std::cout << "As you delve deeper into the forest, you notice the paths are winding and the trees seem to move. 🍃" << std::endl;
    });

    // Create options for exploration
    auto followLight = scenarioHandler->addChild(exploreForest, "Follow the mysterious light");
    addAction("Follow the mysterious light", [this]() {
        std::cout << "You decide to follow the glowing light flickering between the trees. It leads you to a clearing. ✨" << std::endl;
    });

    auto inspectClearing = scenarioHandler->addChild(followLight, "Inspect the clearing");
    addAction("Inspect the clearing", [this]() {
        std::cout << "In the clearing, you find an ancient stone with inscriptions. 📜" << std::endl;
    });

    // Interact with the stone
    auto readInscriptions = scenarioHandler->addChild(inspectClearing, "Read the inscriptions");
    addAction("Read the inscriptions", [this]() {
        std::cout << "You read the inscriptions and feel a surge of energy flow through you. Your aura increases! ⚡" << std::endl;
        player->increaseAura(50);
    });

    // Proceed further
    auto continuePath = scenarioHandler->addChild(readInscriptions, "Continue along the path");
    addAction("Continue along the path", [this]() {
        std::cout << "You continue along the path, feeling more confident with your newfound energy. 💪" << std::endl;
    });

    // Encounter with a mystical creature
    auto encounterCreature = scenarioHandler->addChild(continuePath, "Encounter a mystical creature");
    addAction("Encounter a mystical creature", [this]() {
        std::cout << "A mystical creature appears in front of you, blocking your path. It looks both curious and cautious. 🦄" << std::endl;
    });

    auto interactCreature = scenarioHandler->addChild(encounterCreature, "Interact with the creature");
    addAction("Interact with the creature", [this]() {
        std::cout << "You approach the creature gently. It allows you to pet it and grants you a blessing. 🙏" << std::endl;
        player->increaseAura(30);
    });

    // Option to battle the creature
    auto battleCreature = scenarioHandler->addChild(encounterCreature, "Battle the creature");
    addAction("Battle the creature", [this]() {
        std::cout << "You prepare to battle the creature. It seems hesitant but ready to defend itself. ⚔️" << std::endl;
        battleEnemy();
    });

    // Proceed to the forest guardian
    auto proceedToGuardian = scenarioHandler->addChild(interactCreature, "Proceed to the heart of the forest");
    addAction("Proceed to the heart of the forest", [this]() {
        std::cout << "You make your way to the heart of the forest, where the Forest Guardian awaits. 🌳" << std::endl;
    });

    // Boss battle
    auto confrontGuardian = scenarioHandler->addChild(proceedToGuardian, "Confront the Forest Guardian");
    addAction("Confront the Forest Guardian", [this]() {
        std::cout << "The Forest Guardian stands tall before you, its eyes glowing with ancient wisdom. 😠" << std::endl;
        battleEnemy();
    });

    // After defeating the guardian
    auto collectReward = scenarioHandler->addChild(confrontGuardian, "Collect your reward");
    addAction("Collect your reward", [this]() {
        std::cout << "The Forest Guardian acknowledges your strength and grants you the Amulet of the Forest. 🌿" << std::endl;
        player->acquireArtifact("Amulet of the Forest");
        player->increaseStrength(30);
        std::cout << "Your strength has increased by 30! 💪" << std::endl;
    });

    auto completeLevelNode = scenarioHandler->addChild(collectReward, "Exit the forest");
    addAction("Exit the forest", [this]() {
        completeLevel();
    });

    // Alternative path: Ignore the light
    auto ignoreLight = scenarioHandler->addChild(exploreForest, "Ignore the mysterious light");
    addAction("Ignore the mysterious light", [this]() {
        std::cout << "You decide to ignore the light and take a different path through the forest. 🌲" << std::endl;
    });

    // Encounter bandits
    auto encounterBandits = scenarioHandler->addChild(ignoreLight, "Encounter forest bandits");
    addAction("Encounter forest bandits", [this]() {
        std::cout << "A group of bandits emerge from the shadows, demanding your valuables. 🦹" << std::endl;
        enemy = Enemy("Forest Bandits", 200); // Update enemy
        battleEnemy();
    });

    // Proceed after defeating bandits
    auto proceedAfterBandits = scenarioHandler->addChild(encounterBandits, "Proceed deeper into the forest");
    addAction("Proceed deeper into the forest", [this]() {
        std::cout << "After defeating the bandits, you continue your journey. 🏞️" << std::endl;
    });

    // Arrive at an ancient temple
    auto findTemple = scenarioHandler->addChild(proceedAfterBandits, "Find an ancient temple");
    addAction("Find an ancient temple", [this]() {
        std::cout << "You discover an ancient temple hidden among the trees. 🛕" << std::endl;
    });

    auto exploreTemple = scenarioHandler->addChild(findTemple, "Explore the temple");
    addAction("Explore the temple", [this]() {
        std::cout << "Inside the temple, you find inscriptions and relics from a bygone era. 📜" << std::endl;
        player->increaseAura(70);
        std::cout << "Your aura increases by 70! ⚡" << std::endl;
    });

    // Proceed to the forest guardian from temple
    auto proceedToGuardianFromTemple = scenarioHandler->addChild(exploreTemple, "Proceed to the heart of the forest");
    scenarioHandler->linkChild(proceedToGuardianFromTemple, proceedToGuardian);
}

void LevelTwo::battleEnemy() {
    // Implement battle logic similar to LevelOne
    std::cout << "⚔️ You engage in battle with the " << enemy.getName() << "! 🛡️" << std::endl;

    while (!player->isDead() && !enemy.isDead()) {
        std::cout << "\n💥 Choose your action: (Current Aura: " << player->getAura() << " ⚡)\n";
        std::cout << "1. Attack (Cost: 40 Aura) 🗡️\n";
        std::cout << "2. Heal (Cost: 25 Aura) 💊\n";
        std::cout << "3. Use Ability ✨\n";
        std::cout << "4. Defend 🛡️\n";
        std::cout << "5. Special Move 🌟\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 40) {
                    int damage = player->attack();
                    enemy.decreaseHealth(damage);
                    player->decreaseAura(40);
                    std::cout << "🗡️ You attack " << enemy.getName() << ", dealing " << damage << " damage!" << std::endl;
                } else {
                    std::cout << "❌ Not enough aura to attack! ⚡" << std::endl;
                }
                break;

            case 2:
                if (player->getAura() >= 25) {
                    player->increaseHealth(20);
                    player->decreaseAura(25);
                    std::cout << "💊 You heal yourself, restoring 20 health points! ❤️" << std::endl;
                } else {
                    std::cout << "❌ Not enough aura to heal! ⚡" << std::endl;
                }
                break;

            case 3:
                std::cout << "✨ You use your special ability! ⚡" << std::endl;
                player->useAbility(enemy);
                break;

            case 4:
                defendPlayer();
                break;

            case 5:
                specialMove();
                break;

            default:
                std::cout << "❌ Invalid action. Try again! 🔄" << std::endl;
                continue;
        }

        if (!enemy.isDead()) {
            enemyTurn();
        }
    }

    if (enemy.isDead()) {
        std::cout << "🎉 You have defeated the " << enemy.getName() << "! 🏆" << std::endl;
    } else if (player->isDead()) {
        std::cout << "💀 You have been defeated by the " << enemy.getName() << "... Game Over. ⚰️" << std::endl;
        exit(0);
    }
}

// Additional Player Actions
void LevelTwo::defendPlayer() {
    std::cout << "🛡️ You brace yourself, reducing damage from the next attack. 🛡️" << std::endl;
    isDefending = true;
}

void LevelTwo::specialMove() {
    if (player->getAura() >= 90) {
        int damage = player->getStrength() * 2;
        std::cout << "🌟 You unleash a powerful special move, dealing " << damage << " damage to "
                  << enemy.getName() << "! 💥" << std::endl;
        enemy.decreaseHealth(damage);
        player->decreaseAura(90);
    } else {
        std::cout << "❌ Not enough aura to perform a special move! ⚡" << std::endl;
    }
}

// Enemy's Turn Logic
void LevelTwo::enemyTurn() {
    int enemyAction = rand() % 2; // Randomly choose between attack or special attack

    switch (enemyAction) {
        case 0: { // Enemy attacks
            int damage = enemy.attack();
            if (isDefending) {
                damage /= 2;
                std::cout << "🛡️ Your defense reduces the damage to " << damage << "! 💪" << std::endl;
                isDefending = false; // Reset defense
            }
            std::cout << "💔 The " << enemy.getName() << " attacks, dealing " << damage << " damage! 💥" << std::endl;
            player->decreaseHealth(damage);
            break;
        }
        case 1: { // Enemy uses special attack
            int damage = enemy.specialAttack();
            if (isDefending) {
                damage /= 2;
                std::cout << "🛡️ Your defense reduces the damage to " << damage << "! 💪" << std::endl;
                isDefending = false; // Reset defense
            }
            std::cout << "🔥 The " << enemy.getName() << " uses a special attack, dealing "
                      << damage << " damage! 💥" << std::endl;
            player->decreaseHealth(damage);
            break;
        }
        default:
            std::cout << "😕 " << enemy.getName() << " hesitates and does nothing! ❌" << std::endl;
            break;
    }
}

// Complete Level
void LevelTwo::completeLevel() {
    std::cout << "🎉 You have successfully navigated the enchanted forest. Level Two Complete! 🏆" << std::endl;
    this->isComplete = true;
}

// Proceed with Scenario Navigation
void LevelTwo::proceed() {
    // Display level transition
    displayLevelTransition(2);

    std::cout << "Starting Level Two..." << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

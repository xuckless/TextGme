// LevelThree.cpp
#include "LevelThree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utilities.h" // Assuming there is a Utilities.h for utility functions

// Constructor
LevelThree::LevelThree(std::shared_ptr<Player> player)
    : BaseLevel(player), isComplete(false), enemy("Desert Serpent", 350), isDefending(false), hasMapPiece(false), puzzleSolved(false) {
    srand(static_cast<unsigned int>(time(0))); // Initialize random seed
    setUpDecisionTree();
}

// Destructor
LevelThree::~LevelThree() {
    delete scenarioHandler;
}

void LevelThree::setUpDecisionTree() {
    // Initialize the scenario handler with the starting scene description
    scenarioHandler = new ScenarioHandler<std::string>(
        "You arrive at the edge of a vast, mystical desert. The sun beats down, and the sands stretch endlessly before you. 🏜️"
    );

    // First scene: Decide how to proceed into the desert
    auto enterDesert = scenarioHandler->addChild(scenarioHandler->root, "Enter the desert");
    addAction("Enter the desert", [this]() {
        std::cout << "You step into the desert, feeling the heat and seeing mirages in the distance. ☀️" << std::endl;
    });

    // Options for navigating the desert
    auto followOasis = scenarioHandler->addChild(enterDesert, "Head towards a distant oasis");
    addAction("Head towards a distant oasis", [this]() {
        std::cout << "You decide to head towards what appears to be an oasis. As you approach, it remains ever distant. 🌴" << std::endl;
    });

    auto inspectMirage = scenarioHandler->addChild(followOasis, "Inspect the mirage");
    addAction("Inspect the mirage", [this]() {
        std::cout << "Realizing it's a mirage, you conserve your energy and look for another path. 🌫️" << std::endl;
    });

    auto findMapPiece = scenarioHandler->addChild(inspectMirage, "Find a piece of an ancient map");
    addAction("Find a piece of an ancient map", [this]() {
        std::cout << "You find a tattered piece of parchment partially buried in the sand. It seems to be part of a map. 🗺️" << std::endl;
        hasMapPiece = true;
    });

    // Alternative path: Navigate by the stars
    auto navigateByStars = scenarioHandler->addChild(enterDesert, "Wait until night and navigate by the stars");
    addAction("Wait until night and navigate by the stars", [this]() {
        std::cout << "You wait until nightfall. The stars shine brightly, providing guidance. ✨" << std::endl;
    });

    // Encounter with a desert nomad
    auto meetNomad = scenarioHandler->addChild(navigateByStars, "Meet a desert nomad");
    addAction("Meet a desert nomad", [this]() {
        std::cout << "A desert nomad approaches, offering to trade. 🧕" << std::endl;
    });

    auto tradeWithNomad = scenarioHandler->addChild(meetNomad, "Trade with the nomad");
    addAction("Trade with the nomad", [this]() {
        if (!hasMapPiece) {
            std::cout << "You trade some supplies for a piece of an ancient map. 🗺️" << std::endl;
            hasMapPiece = true;
        } else {
            std::cout << "You have nothing more to trade. The nomad wishes you well and departs. 👋" << std::endl;
        }
    });

    // Proceed to the ancient pyramid
    auto proceedToPyramid = scenarioHandler->addChild(findMapPiece, "Proceed to the ancient pyramid");
    scenarioHandler->linkChild(tradeWithNomad, proceedToPyramid);
    addAction("Proceed to the ancient pyramid", [this]() {
        if (hasMapPiece) {
            std::cout << "Using the map piece, you locate an ancient pyramid rising from the sands. 🏜️" << std::endl;
        } else {
            std::cout << "Without a map, you wander aimlessly and decide to turn back. 🔄" << std::endl;
            // Link back to previous choices or end the game
        }
    });

    // Inside the pyramid
    auto enterPyramid = scenarioHandler->addChild(proceedToPyramid, "Enter the pyramid");
    addAction("Enter the pyramid", [this]() {
        std::cout << "You step inside the pyramid. It's dark and the air is thick with mystery. 🏺" << std::endl;
    });

    // Solve a puzzle
    auto solvePyramidPuzzle = scenarioHandler->addChild(enterPyramid, "Solve the ancient puzzle");
    addAction("Solve the ancient puzzle", [this]() {
        solvePuzzle();
    });

    // After solving the puzzle
    auto descendDeeper = scenarioHandler->addChild(solvePyramidPuzzle, "Descend deeper into the pyramid");
    addAction("Descend deeper into the pyramid", [this]() {
        if (puzzleSolved) {
            std::cout << "A passage opens, and you descend deeper into the pyramid's heart. 🌀" << std::endl;
        } else {
            std::cout << "The passage remains sealed. You need to solve the puzzle first. 🔒" << std::endl;
        }
    });

    // Encounter the desert serpent
    auto encounterSerpent = scenarioHandler->addChild(descendDeeper, "Encounter the Desert Serpent");
    addAction("Encounter the Desert Serpent", [this]() {
        std::cout << "A massive serpent emerges, its scales shimmering like the sands. 🐍" << std::endl;
        battleEnemy();
    });

    // After defeating the serpent
    auto collectTreasure = scenarioHandler->addChild(encounterSerpent, "Collect the hidden treasure");
    addAction("Collect the hidden treasure", [this]() {
        std::cout << "You discover a hidden chamber filled with treasure and the Scepter of Sands. 💎" << std::endl;
        player->acquireArtifact("Scepter of Sands");
        player->increaseAura(100);
        std::cout << "Your aura increases by 100! ⚡" << std::endl;
    });

    auto completeLevelNode = scenarioHandler->addChild(collectTreasure, "Exit the pyramid");
    addAction("Exit the pyramid", [this]() {
        completeLevel();
    });

    // Alternative path: Sandstorm
    auto faceSandstorm = scenarioHandler->addChild(enterDesert, "Navigate through a sudden sandstorm");
    addAction("Navigate through a sudden sandstorm", [this]() {
        std::cout << "A sandstorm engulfs you, limiting your visibility and testing your endurance. 🌪️" << std::endl;
        player->decreaseHealth(20);
        std::cout << "You lose 20 health due to harsh conditions. 💔" << std::endl;
    });

    auto findShelter = scenarioHandler->addChild(faceSandstorm, "Find shelter");
    addAction("Find shelter", [this]() {
        std::cout << "You find a small cave to wait out the storm. Inside, you discover ancient carvings. 🕳️" << std::endl;
        player->increaseAura(50);
        std::cout << "Your aura increases by 50! ⚡" << std::endl;
    });

    // Link to the pyramid path
    scenarioHandler->linkChild(findShelter, proceedToPyramid);
}

void LevelThree::battleEnemy() {
    // Implement battle logic similar to previous levels
    std::cout << "⚔️ You engage in battle with the " << enemy.getName() << "! 🛡️" << std::endl;

    while (!player->isDead() && !enemy.isDead()) {
        std::cout << "\n💥 Choose your action: (Current Aura: " << player->getAura() << " ⚡)\n";
        std::cout << "1. Attack (Cost: 45 Aura) 🗡️\n";
        std::cout << "2. Heal (Cost: 30 Aura) 💊\n";
        std::cout << "3. Use Ability ✨\n";
        std::cout << "4. Defend 🛡️\n";
        std::cout << "5. Special Move 🌟\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (player->getAura() >= 45) {
                    int damage = player->attack();
                    enemy.decreaseHealth(damage);
                    player->decreaseAura(45);
                    std::cout << "🗡️ You attack " << enemy.getName() << ", dealing " << damage << " damage!" << std::endl;
                } else {
                    std::cout << "❌ Not enough aura to attack! ⚡" << std::endl;
                }
                break;

            case 2:
                if (player->getAura() >= 30) {
                    player->increaseHealth(25);
                    player->decreaseAura(30);
                    std::cout << "💊 You heal yourself, restoring 25 health points! ❤️" << std::endl;
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
void LevelThree::defendPlayer() {
    std::cout << "🛡️ You brace yourself, reducing damage from the next attack. 🛡️" << std::endl;
    isDefending = true;
}

void LevelThree::specialMove() {
    if (player->getAura() >= 95) {
        int damage = player->getStrength() * 2 + 20; // Extra damage for LevelThree
        std::cout << "🌟 You unleash a powerful special move, dealing " << damage << " damage to "
                  << enemy.getName() << "! 💥" << std::endl;
        enemy.decreaseHealth(damage);
        player->decreaseAura(95);
    } else {
        std::cout << "❌ Not enough aura to perform a special move! ⚡" << std::endl;
    }
}

// Enemy's Turn Logic
void LevelThree::enemyTurn() {
    int enemyAction = rand() % 3; // Randomly choose between attack, special attack, or heal

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
        case 2: { // Enemy heals
            enemy.heal();
            break;
        }
        default:
            std::cout << "😕 " << enemy.getName() << " hesitates and does nothing! ❌" << std::endl;
            break;
    }
}

// Puzzle Solving Logic
void LevelThree::solvePuzzle() {
    std::cout << "🧩 An ancient mechanism presents a puzzle with hieroglyphs. You need to arrange them in the correct order. 🗿" << std::endl;
    // Simple puzzle: The player needs to input the correct sequence
    std::cout << "Enter the correct sequence of numbers (1-3): " << std::endl;
    std::cout << "1. Sun ☀️" << std::endl;
    std::cout << "2. Water 💧" << std::endl;
    std::cout << "3. Sand 🏖️" << std::endl;

    int sequence[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> sequence[i];
    }

    if (sequence[0] == 3 && sequence[1] == 2 && sequence[2] == 1) {
        std::cout << "✅ The puzzle clicks into place, and a passage opens! 🛣️" << std::endl;
        puzzleSolved = true;
    } else {
        std::cout << "❌ The sequence is incorrect. Try again later. 🔄" << std::endl;
        puzzleSolved = false;
    }
}

// Complete Level
void LevelThree::completeLevel() {
    std::cout << "🎉 You have successfully conquered the desert's challenges. Level Three Complete! 🏆" << std::endl;
    this->isComplete = true;
}

// Proceed with Scenario Navigation
void LevelThree::proceed() {
    // Display level transition
    displayLevelTransition(3);

    std::cout << "Starting Level Three..." << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

// LevelThree.cpp
#include "LevelThree.h"
#include <iostream>

LevelThree::LevelThree() : isComplete(false), finalBoss(500) {
    setUpDecisionTree();
}

void LevelThree::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>("Welcome to Level Three");

    // Starting exploration
    auto exploreArea = scenarioHandler->addChild(scenarioHandler->root, "Investigate the strange area");
    auto chestOne = scenarioHandler->addChild(exploreArea, "Find and open the first chest");
    auto chestOneAura = scenarioHandler->addChild(chestOne, "First chest found! Gain aura");

    // Increase aura upon finding the first chest
    addAction("First chest found! Gain aura", [this]() { player.increaseAura(120); });

    // Corridor exploration
    auto darkCorridor = scenarioHandler->addChild(exploreArea, "Enter a dark corridor");
    scenarioHandler->linkChild(chestOneAura, darkCorridor);

    auto secondChest = scenarioHandler->addChild(darkCorridor, "Discover a chest partially hidden");
    auto secondChestAura = scenarioHandler->addChild(secondChest, "Aura found in the hidden chest");

    // Aura boost action for the second chest
    addAction("Aura found in the hidden chest", [this]() { player.increaseAura(200); });

    // Encounter with a powerful enemy
    auto enemyEncounter = scenarioHandler->addChild(darkCorridor, "Encounter a powerful enemy");
    scenarioHandler->linkChild(secondChestAura, enemyEncounter);

    addAction("Encounter a powerful enemy", [this]() {
        if (!player.battle(300)) {
            std::cout << "The enemy defeated you." << std::endl;
            exit(0); // Ends the game if player loses
        } else {
            std::cout << "Enemy defeated! Aura remains." << std::endl;
        }
    });

    // Rejoin exploration after enemy encounter
    auto proceed = scenarioHandler->addChild(enemyEncounter, "Continue exploring deeper");

    // Additional rooms and final preparation
    auto ominousRoom = scenarioHandler->addChild(proceed, "You enter an ominous room");
    auto auraBoostChest = scenarioHandler->addChild(ominousRoom, "Open another aura-boosting chest");
    auto boostedAura = scenarioHandler->addChild(auraBoostChest, "Found aura boost in the chest");

    // Final aura boost action
    addAction("Found aura boost in the chest", [this]() { player.increaseAura(250); });

    // Final boss room encounter
    auto bossRoom = scenarioHandler->addChild(ominousRoom, "Enter the final boss's lair");
    scenarioHandler->linkChild(boostedAura, bossRoom);

    auto bossBattle = scenarioHandler->addChild(bossRoom, "Engage in battle with the final boss");

    // Boss battle outcome based on player's remaining aura
    addAction("Engage in battle with the final boss", [this]() {
        if (player.battle(finalBoss.getAura())) {
            std::cout << "Victory! The boss has fallen!" << std::endl;
        } else {
            std::cout << "You lost to the final boss." << std::endl;
        }
    });

    // Level Three completion point
    auto complete = scenarioHandler->addChild(bossBattle, "Complete Level");
    addAction("Complete Level", std::bind(&LevelThree::completeLevel, this));
}

void LevelThree::completeLevel() {
    std::cout << "Level Three Complete!" << std::endl;
    this->isComplete = true;
}

void LevelThree::proceed() {
    std::cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

// LevelTwo.cpp
#include "LevelTwo.h"
#include <iostream>

LevelTwo::LevelTwo() : isComplete(false), miniBoss(300) {
    setUpDecisionTree();
}

void LevelTwo::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>("Welcome to Level Two");

    // Initial exploration
    auto startExploration = scenarioHandler->addChild(scenarioHandler->root, "Explore the surroundings");
    auto openChest = scenarioHandler->addChild(startExploration, "Open a mysterious chest");
    auto foundAura = scenarioHandler->addChild(openChest, "Chest found! Increase aura");

    // Add an action to increase aura when the chest is found
    addAction("Chest found! Increase aura", [this]() { player.increaseAura(100); });

    // Enter the hallway
    auto hallwayEntrance = scenarioHandler->addChild(startExploration, "Enter the hallway");
    scenarioHandler->linkChild(foundAura, hallwayEntrance); // Return to exploration

    auto inspectRoom = scenarioHandler->addChild(hallwayEntrance, "Inspect a room with a faint light");
    auto hiddenChest = scenarioHandler->addChild(inspectRoom, "Open hidden chest in the corner");
    auto auraBoost = scenarioHandler->addChild(hiddenChest, "Aura boost found in the hidden chest!");

    // Add an action to increase aura from the hidden chest
    addAction("Aura boost found in the hidden chest!", [this]() { player.increaseAura(150); });

    // Final encounter with mini-boss
    auto bossRoom = scenarioHandler->addChild(hallwayEntrance, "Approach the mini-boss room");
    scenarioHandler->linkChild(auraBoost, bossRoom);

    auto battleMiniBoss = scenarioHandler->addChild(bossRoom, "Battle the mini-boss");

    // Battle outcome based on player’s aura
    addAction("Battle the mini-boss", [this]() {
        if (player.battle(miniBoss.getAura())) {
            std::cout << "Mini-boss defeated!" << std::endl;
        } else {
            std::cout << "You lost the battle" << std::endl;
        }
    });

    // Define the completion point for Level Two
    auto complete = scenarioHandler->addChild(battleMiniBoss, "Complete Level");
    addAction("Complete Level", std::bind(&LevelTwo::completeLevel, this));
}

void LevelTwo::completeLevel() {
    std::cout << "Level Two Complete!" << std::endl;
    this->isComplete = true;
}

void LevelTwo::proceed() {
    std::cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

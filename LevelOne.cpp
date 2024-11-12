// LevelOne.cpp
#include "LevelOne.h"
#include <iostream>

LevelOne::LevelOne() : isComplete(false), enemy(200) {
    setUpDecisionTree();
}

void LevelOne::setUpDecisionTree() {
    scenarioHandler = new ScenarioHandler<std::string>("Welcome to Level One");

    // Create the first branching path with a "Look around" prompt
    auto lookAround = scenarioHandler->addChild(scenarioHandler->root, "Look around");
    auto chest = scenarioHandler->addChild(lookAround, "Open the chest");
    auto chestOpen = scenarioHandler->addChild(chest, "Chest Open, continue to the door");
    auto nextRoom = scenarioHandler->addChild(lookAround, "Open the door");

    // Link "chestOpen" to "nextRoom" to allow progression
    scenarioHandler->linkChild(chestOpen, nextRoom);

    // Add an action to "chestOpen" to display a message
    addAction("Chest Open, continue to the door", [this]() { player.increaseAura(75); });

    // Create another branching path within the "nextRoom" scenario
    auto newLookAround = scenarioHandler->addChild(nextRoom, "Look Around - Press 1");
    auto chest2 = scenarioHandler->addChild(newLookAround, "Open the chest");
    auto chestOpen2 = scenarioHandler->addChild(chest2, "Chest Open, continue to the hallway");
    auto hallway = scenarioHandler->addChild(newLookAround, "Go to the end of the hallway");

    // Link "chestOpen2" to "hallway" to create continuity
    scenarioHandler->linkChild(chestOpen2, hallway);

    // Add an action to "chestOpen2" to display a message
    addAction("Chest Open, continue to the hallway", [this]() { player.increaseAura(75); });

    // Create the final part of the tree with a suspenseful "boss room" scenario
    auto bossRoom = scenarioHandler->addChild(hallway, "You are approaching the boss room! continue");
    auto peek = scenarioHandler->addChild(bossRoom, "peek the boss");
    auto noPeek = scenarioHandler->addChild(bossRoom, "run away (Nowhere)");

    // Link "noPeek" back to "hallway" for a looped scenario
    scenarioHandler->linkChild(noPeek, hallway);

    // Define the completion point of the level
    auto complete = scenarioHandler->addChild(peek, "Battle the boss");
    addAction("Battle the boss", [this]() {
        if (player.battle(enemy.getAura())) {
            std::cout << "You won" << std::endl;
        } else {
            std::cout << "You died" << std::endl;
        }
    });

    auto progression = scenarioHandler->addChild(complete, "Complete Level");

    // Add an action to the completion point to mark the level as complete
    addAction("Complete Level", std::bind(&LevelOne::completeLevel, this));
}

void LevelOne::completeLevel() {
    std::cout << "Level One Complete!" << std::endl;
    this->isComplete = true;
}

void LevelOne::proceed() {
    std::cout << " " << std::endl;
    navigateDecisionTree(scenarioHandler->root, [this]() { return isComplete; });
}

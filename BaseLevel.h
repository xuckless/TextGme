//BaseLevel.h

#ifndef BASELEVEL_H
#define BASELEVEL_H

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <memory>
#include "Level.h"
#include "ScenarioHandler.h"
#include "Player.h"

class BaseLevel : public Level {
protected:
    std::shared_ptr<Player> player; // Use shared_ptr for shared ownership
    ScenarioHandler<std::string>* scenarioHandler; // Handles the decision tree structure
    std::map<std::string, std::function<void()>> actionMap; // Lookup table for actions

public:
    BaseLevel(std::shared_ptr<Player> player); // Constructor takes shared_ptr
    virtual ~BaseLevel();

    virtual void setUpDecisionTree() = 0; // Forces derived classes to implement
    void addAction(const std::string& description, std::function<void()> action); // Adds actions to scenes
    void navigateDecisionTree(Scenes<std::string>* node, std::function<bool()> isCompleteFlag); // Handles navigation logic
};

#endif // BASELEVEL_H

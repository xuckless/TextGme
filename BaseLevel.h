// BaseLevel.h
#ifndef BASELEVEL_H
#define BASELEVEL_H

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include "Level.h"
#include "ScenarioHandler.h"
#include "Player.h"

class BaseLevel : public Level {
protected:
    ScenarioHandler<std::string>* scenarioHandler; // Handles the decision tree structure
    std::map<std::string, std::function<void()>> actionMap; // Lookup table for actions
    Player player;

public:
    BaseLevel();
    virtual ~BaseLevel();
    virtual void setUpDecisionTree() = 0;
    void addAction(const std::string& description, std::function<void()> action);
    void navigateDecisionTree(Scenes<std::string>* node, std::function<bool()> isCompleteFlag);
};

#endif // BASELEVEL_H

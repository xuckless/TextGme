#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "BaseLevel.h"
#include "Enemy.h"

class LevelTwo : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;

public:
    LevelTwo(Player& player);
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;

    // Methods for battles and actions
    void battleBoss();
    void battleBandits();
    void addChestAction(const std::string& actionName, int auraReward, const std::string& chestType);
};

#endif // LEVELTWO_H

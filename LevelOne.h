#ifndef LEVELONE_H
#define LEVELONE_H

#include "BaseLevel.h"
#include "Enemy.h"

class LevelOne : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;

public:
    LevelOne(std::shared_ptr<Player> player); // Constructor takes shared_ptr
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;

    // Declaration of the battleBoss method
    void battleBoss();

    // Declaration of addChestAction
    void addChestAction(const std::string& actionName, int auraReward, const std::string& chestType);
};

#endif // LEVELONE_H

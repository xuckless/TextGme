// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "BaseLevel.h"
#include "Enemy.h"
#include <memory>
#include <string>

class LevelOne : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;
    bool hasKey;
    bool chestOpened;
    bool legendaryChestOpened; // Added: Flag for legendary chest
    bool doorUnlocked;         // Added: Flag for door unlock status
    bool isDefending;

    void battleGuard();
    void defendPlayer();
    void specialMove();
    void enemyTurn();

    // Updated helper function declaration with auraBoost
    Scenes<std::string>* addInspectionOption(const std::string& optionText,
                                            const std::string& actionText,
                                            Scenes<std::string>* parent,
                                            int auraBoost = 0);

public:
    LevelOne(std::shared_ptr<Player> player);
    ~LevelOne();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
    void battleBoss();
};

#endif // LEVELONE_H

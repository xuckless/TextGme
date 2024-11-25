// LevelTwo.h
#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "BaseLevel.h"
#include "Enemy.h"
#include <memory>
#include <string>

class LevelTwo : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;
    bool isDefending;

    // Additional variables specific to LevelTwo can be added here

    void battleEnemy();
    void defendPlayer();
    void specialMove();
    void enemyTurn();

public:
    LevelTwo(std::shared_ptr<Player> player);
    ~LevelTwo();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
};

#endif // LEVELTWO_H

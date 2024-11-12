// LevelTwo.h
#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "BaseLevel.h"
#include "Enemy.h"

class LevelTwo : public BaseLevel {
private:
    bool isComplete;
    Enemy miniBoss;

public:
    LevelTwo();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
};

#endif // LEVELTWO_H

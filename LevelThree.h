// LevelThree.h
#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "BaseLevel.h"
#include "Enemy.h"

class LevelThree : public BaseLevel {
private:
    bool isComplete;
    Enemy finalBoss;

public:
    LevelThree();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
};

#endif // LEVELTHREE_H

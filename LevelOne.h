// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "BaseLevel.h"
#include "Enemy.h"

class LevelOne : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;

public:
    LevelOne();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
};

#endif // LEVELONE_H

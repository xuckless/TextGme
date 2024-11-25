// LevelThree.h
#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "BaseLevel.h"
#include "Enemy.h"
#include <memory>
#include <string>

class LevelThree : public BaseLevel {
private:
    bool isComplete;
    Enemy enemy;
    bool isDefending;
    bool hasMapPiece;
    bool puzzleSolved;

    // Additional methods specific to LevelThree
    void battleEnemy();
    void defendPlayer();
    void specialMove();
    void enemyTurn();
    void solvePuzzle();

public:
    LevelThree(std::shared_ptr<Player> player);
    ~LevelThree();
    void setUpDecisionTree() override;
    void completeLevel();
    void proceed() override;
};

#endif // LEVELTHREE_H

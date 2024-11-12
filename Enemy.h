// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
private:
    std::string name;
    int aura; // Enemy's health bar

public:
    Enemy(int aura);
    std::string toString() const;
    int getAura() const;
};

#endif // ENEMY_H

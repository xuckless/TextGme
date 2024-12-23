// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
private:
    std::string name;
    int health;

public:
    Enemy(const std::string& name, int initialHealth);
    // Enemy status functions
    std::string getName() const;
    int getHealth() const;
    void decreaseHealth(int amount);
    void increaseHealth(int amount);
    bool isDead() const;

    // Enemy actions
    int attack();
    void defend();
    void heal();

    // Add the specialAttack method
    int specialAttack();
};

#endif // ENEMY_H

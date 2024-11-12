// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int aura;
    int maxAura;

public:
    Player(const std::string& name, int initialAura);
    Player(const std::string& name);

    std::string getName() const;
    int getAura() const;
    int getMaxAura() const;
    int increaseAura(int amount);
    void decreaseAura(int amount);
    bool isDead() const;
    bool battle(int enemyAura);
};

#endif // PLAYER_H

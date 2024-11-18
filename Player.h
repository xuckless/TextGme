#ifndef PLAYER_H
#define PLAYER_H

#include <string>

// Forward declaration of the Enemy class
class Enemy;

class Player {
private:
    std::string name;
    int aura;
    int maxAura;
    int health;

public:
    Player(const std::string& name, int initialAura, int initialHealth);
    Player(const std::string& name);

    static Player createCharacter(const std::string& characterChoice);

    std::string getName() const;
    int getAura() const;
    int getMaxAura() const;
    int getHealth() const;
    int increaseHealth(int amount);
    void decreaseHealth(int amount);
    int increaseAura(int amount);
    void decreaseAura(int amount);
    bool isDead() const;
    bool battle(int enemyAura);

    // Add this declaration
    void useAbility(Enemy& enemy);
};

#endif // PLAYER_H

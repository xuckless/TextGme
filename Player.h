// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

// Forward declaration of the Enemy class
class Enemy;

class Player {
private:
    std::string name;
    int aura;
    int maxAura;
    int health;
    int strength;
    std::vector<std::string> artifacts;

public:
    Player(); // Default constructor declaration
    Player(const std::string& name, int initialAura, int initialHealth);
    Player(const std::string& name);

    static Player createCharacter(const std::string& characterChoice);

    std::string getName() const;
    int getAura() const;
    int getMaxAura() const;
    int attack();
    void increaseStrength(int amount);
    int getHealth() const;
    int increaseHealth(int amount);
    void decreaseHealth(int amount);
    int increaseAura(int amount);
    void decreaseAura(int amount);
    bool isDead() const;
    bool battle(int enemyAura);

    void useAbility(Enemy& enemy);

    // New methods for artifacts
    void acquireArtifact(const std::string& artifactName);
    bool hasArtifact(const std::string& artifactName) const;
    void removeArtifact(const std::string& artifactName);

    int getStrength() const;
};

#endif // PLAYER_H

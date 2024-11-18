#include "Player.h"
#include <iostream>

#include "Enemy.h"

Player::Player(const std::string& name, int initialAura, int initialHealth)
    : name(name), aura(initialAura), maxAura(1000000000), health(initialHealth) {}

Player::Player(const std::string& name) : Player(name, 0, 100) {}

Player Player::createCharacter(const std::string& characterChoice) {
    if (characterChoice == "Ban") {
        return Player("Ban", 50, 120); // Ban starts with extra health
    } else if (characterChoice == "Gojo") {
        return Player("Gojo", 150, 100); // Gojo starts with extra aura
    } else if (characterChoice == "Madara") {
        return Player("Madara", 100, 100); // Madara has normal stats
    } else {
        return Player("Default", 100, 100); // Default fallback
    }
}

std::string Player::getName() const {
    return name;
}

int Player::getAura() const {
    return aura;
}

int Player::getMaxAura() const {
    return maxAura;
}

int Player::getHealth() const {
    return health;
}

int Player::increaseHealth(int amount) {
    health += amount;
    std::cout << "Health increased by " << amount << std::endl;
    return health;
}

void Player::decreaseHealth(int amount) {
    health -= amount;
    std::cout << "Health decreased by " << amount << std::endl;
}

int Player::increaseAura(int amount) {
    if (aura + amount > maxAura) {
        aura = maxAura;
    } else {
        aura += amount;
    }
    return aura;
}

void Player::decreaseAura(int amount) {
    aura -= (aura < amount) ? aura : amount;
}

bool Player::isDead() const {
    return health <= 0;
}

void Player::useAbility(Enemy& enemy) {
    if (name == "Ban") {
        if (enemy.getHealth() >= 50) {
            int stealAmount = 20; // Amount to steal
            enemy.decreaseHealth(stealAmount);
            increaseHealth(stealAmount);

            std::cout << "Ban uses Steal Life and drains " << stealAmount << " health from the enemy!" << std::endl;
            std::cout << "Enemy's remaining health: " << enemy.getHealth() << std::endl;
            std::cout << "Ban's current health: " << health << std::endl;
        } else {
            std::cout << "The enemy's health is too low to steal (less than 50)." << std::endl;
        }
    } else if (name == "Madara") {
        std::cout << "Madara deals extra damage!" << std::endl;
        // Logic for extra damage is already handled in battleBoss()
    } else if (name == "Gojo") {
        std::cout << "Gojo's aura replenishes!" << std::endl;
        increaseAura(50);
    } else {
        std::cout << name << " does not have a unique ability to use." << std::endl;
    }
}

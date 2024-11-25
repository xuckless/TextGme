// Player.cpp

#include "Player.h"
#include <iostream>
#include <algorithm>
#include "Enemy.h"

// Default constructor definition
Player::Player() : Player("Default", 100, 100) {
    // Delegating constructor
}

Player::Player(const std::string& name, int initialAura, int initialHealth)
    : name(name), aura(initialAura), maxAura(1000000000), health(initialHealth) {
    if (name == "Madara") {
        strength = 70;
    } else {
        strength = 40;
    }
}

Player::Player(const std::string& name) : Player(name, 0, 100) {
    // Delegating constructor
}

Player Player::createCharacter(const std::string& characterChoice) {
    if (characterChoice == "Ban") {
        return Player("Ban", 100000, 120);
    } else if (characterChoice == "Gojo") {
        return Player("Gojo", 150, 100);
    } else if (characterChoice == "Madara") {
        return Player("Madara", 100, 100);
    } else {
        return Player("Default", 100, 100);
    }
}

void Player::increaseStrength(int amount) {
    strength += amount;
    std::cout << "Your strength has increased by " << amount << "! Current strength: " << strength << "." << std::endl;
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

int Player::attack() {
    int baseDamage = rand() % 20 + 10; // Base damage between 10 and 30
    int damage = baseDamage + (strength / 2); // Adjust damage based on strength
    std::cout << name << " attacks and deals " << damage << " damage!" << std::endl;
    return damage;
}


void Player::decreaseAura(int amount) {
    if (aura >= amount) {
        aura -= amount;
        std::cout << "Aura decreased by " << amount << ". Remaining aura: " << aura << "." << std::endl;
    } else {
        std::cout << "Not enough aura! Current aura: " << aura << ".\nNo aura was deducted." << std::endl;
    }
}


bool Player::isDead() const {
    return health <= 0;
}

void Player::useAbility(Enemy& enemy) {
    if (name == "Ban") {
        if (enemy.getHealth() >= 50) {
            int stealAmount = 20;
            enemy.decreaseHealth(stealAmount);
            increaseHealth(stealAmount);

            std::cout << "Ban uses Steal Life and drains " << stealAmount << " health from the enemy!" << std::endl;
        } else {
            std::cout << "The enemy's health is too low to steal (less than 50)." << std::endl;
        }
    } else if (name == "Madara") {
        std::cout << "Madara deals extra damage!" << std::endl;
        // Extra damage logic handled elsewhere
    } else if (name == "Gojo") {
        std::cout << "Gojo's aura replenishes!" << std::endl;
        increaseAura(50);
    } else {
        std::cout << name << " does not have a unique ability to use." << std::endl;
    }
}

// Artifact Methods
void Player::acquireArtifact(const std::string& artifactName) {
    if (std::find(artifacts.begin(), artifacts.end(), artifactName) == artifacts.end()) {
        artifacts.push_back(artifactName);
        std::cout << "You have acquired the artifact: " << artifactName << "!" << std::endl;
    } else {
        std::cout << "You already have the artifact: " << artifactName << "." << std::endl;
    }
}


bool Player::hasArtifact(const std::string& artifactName) const {
    return std::find(artifacts.begin(), artifacts.end(), artifactName) != artifacts.end();
}

void Player::removeArtifact(const std::string& artifactName) {
    auto it = std::find(artifacts.begin(), artifacts.end(), artifactName);
    if (it != artifacts.end()) {
        artifacts.erase(it);
    }
}

int Player::getStrength() const {
    return strength;
}

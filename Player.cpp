#include "Player.h"
#include <iostream>
#include <algorithm>
#include "Enemy.h"

// Default constructor: Initializes a "Default" player with default aura and health values.
Player::Player() : Player("Default", 100, 100) {
    // Delegating constructor to avoid duplicate initialization logic.
}

// Constructor: Initializes the player with a name, aura, and health.
// Also initializes player-specific attributes based on the character name.
Player::Player(const std::string& name, int initialAura, int initialHealth)
    : name(name), aura(initialAura), maxAura(1000000000), health(2342342) {
    // Assign strength based on the character name.
    if (name == "Madara") {
        strength = 70; // Higher strength for Madara.
    } else {
        strength = 40; // Default strength for others.
    }
}

// Constructor: Initializes the player with a name and default aura and health values.
Player::Player(const std::string& name) : Player(name, 0, 100) {
    // Delegating constructor to reuse initialization logic.
}

// Factory method to create specific character types based on the choice.
Player Player::createCharacter(const std::string& characterChoice) {
    if (characterChoice == "Ban") {
        return Player("Ban", 100000, 120);
    } else if (characterChoice == "Gojo") {
        return Player("Gojo", 150, 100);
    } else if (characterChoice == "Madara") {
        return Player("Madara", 100, 100);
    } else {
        return Player("Default", 100, 100); // Fallback for unrecognized characters.
    }
}

// Increases the player's strength by a specified amount and displays the updated value.
void Player::increaseStrength(int amount) {
    strength += amount;
    std::cout << "Your strength has increased by " << amount << "! Current strength: " << strength << "." << std::endl;
}

// Getter for the player's name.
std::string Player::getName() const {
    return name;
}

// Getter for the player's current aura.
int Player::getAura() const {
    return aura;
}

// Getter for the player's maximum aura.
int Player::getMaxAura() const {
    return maxAura;
}

// Getter for the player's current health.
int Player::getHealth() const {
    return health;
}

// Increases the player's health by a specified amount and returns the updated value.
int Player::increaseHealth(int amount) {
    health += amount;
    std::cout << "Health increased by " << amount << std::endl;
    return health;
}

// Decreases the player's health by a specified amount and displays the updated value.
void Player::decreaseHealth(int amount) {
    health -= amount;
    std::cout << "Health decreased by " << amount << std::endl;
}

// Increases the player's aura, ensuring it does not exceed the maximum aura limit.
int Player::increaseAura(int amount) {
    if (aura + amount > maxAura) {
        aura = maxAura; // Cap aura at maxAura.
    } else {
        aura += amount; // Increment aura by the specified amount.
    }
    return aura;
}

// Executes an attack, calculates damage based on strength, and returns the damage dealt.
int Player::attack() {
    int baseDamage = rand() % 20 + 10; // Random base damage between 10 and 30.
    int damage = baseDamage + (strength / 2); // Adjust damage based on player's strength.
    std::cout << name << " attacks and deals " << damage << " damage!" << std::endl;
    return damage;
}

// Decreases the player's aura by a specified amount if sufficient aura is available.
void Player::decreaseAura(int amount) {
    if (aura >= amount) {
        aura -= amount;
        std::cout << "Aura decreased by " << amount << ". Remaining aura: " << aura << "." << std::endl;
    } else {
        std::cout << "Not enough aura! Current aura: " << aura << ".\nNo aura was deducted." << std::endl;
    }
}

// Checks if the player is dead (health is 0 or less).
bool Player::isDead() const {
    return health <= 0;
}

// Uses a unique ability based on the player's character type.
// Interacts with an enemy to demonstrate the ability's effect.
void Player::useAbility(Enemy& enemy) {
    if (name == "Ban") {
        if (enemy.getHealth() >= 50) {
            int stealAmount = 20;
            enemy.decreaseHealth(stealAmount); // Decrease enemy health.
            increaseHealth(stealAmount);      // Increase player's health.
            std::cout << "Ban uses Steal Life and drains " << stealAmount << " health from the enemy!" << std::endl;
        } else {
            std::cout << "The enemy's health is too low to steal (less than 50)." << std::endl;
        }
    } else if (name == "Madara") {
        std::cout << "Madara deals extra damage!" << std::endl;
        // Extra damage logic can be implemented elsewhere.
    } else if (name == "Gojo") {
        std::cout << "Gojo's aura replenishes!" << std::endl;
        increaseAura(50); // Gojo restores 50 aura points.
    } else {
        std::cout << name << " does not have a unique ability to use." << std::endl;
    }
}

// Artifact Methods

// Adds a unique artifact to the player's collection.
void Player::acquireArtifact(const std::string& artifactName) {
    // Ensure the artifact is not already in the collection.
    if (std::find(artifacts.begin(), artifacts.end(), artifactName) == artifacts.end()) {
        artifacts.push_back(artifactName); // Add the artifact.
        std::cout << "You have acquired the artifact: " << artifactName << "!" << std::endl;
    } else {
        std::cout << "You already have the artifact: " << artifactName << "." << std::endl;
    }
}

// Checks if the player owns a specific artifact.
bool Player::hasArtifact(const std::string& artifactName) const {
    return std::find(artifacts.begin(), artifacts.end(), artifactName) != artifacts.end();
}

// Removes a specific artifact from the player's collection if it exists.
void Player::removeArtifact(const std::string& artifactName) {
    auto it = std::find(artifacts.begin(), artifacts.end(), artifactName);
    if (it != artifacts.end()) {
        artifacts.erase(it); // Remove the artifact from the collection.
    }
}

// Getter for the player's current strength.
int Player::getStrength() const {
    return strength;
}
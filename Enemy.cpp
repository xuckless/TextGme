#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor: Initializes the enemy with a name and starting health.
Enemy::Enemy(const std::string& name, int initialHealth)
    : name(name), health(initialHealth) {}

// Getter for the enemy's name.
std::string Enemy::getName() const {
    return name;
}

// Getter for the enemy's current health.
int Enemy::getHealth() const {
    return health;
}

// Decreases the enemy's health by a specified amount.
// Displays the damage taken and the updated health.
void Enemy::decreaseHealth(int amount) {
    health -= amount;
    std::cout << name << " took " << amount << " damage!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

// Increases the enemy's health by a specified amount.
// Displays the healing amount and the updated health.
void Enemy::increaseHealth(int amount) {
    health += amount;
    std::cout << name << " healed by " << amount << " points!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

// Checks if the enemy is dead (health is 0 or less).
bool Enemy::isDead() const {
    return health <= 0;
}

// Performs a basic attack and calculates random damage.
// Returns the damage dealt, which ranges from 10 to 30.
int Enemy::attack() {
    int damage = rand() % 20 + 10; // Random damage between 10 and 30.
    std::cout << name << " attacks and deals " << damage << " damage!" << std::endl;
    return damage;
}

// Defends against the next incoming attack, reducing damage.
// The actual implementation for damage reduction would be handled in game logic.
void Enemy::defend() {
    std::cout << name << " defends, reducing incoming damage by half on the next turn!" << std::endl;
}

// Heals the enemy by a random amount between 5 and 20.
// Displays the healing action and updated health.
void Enemy::heal() {
    int healAmount = rand() % 15 + 5; // Random healing between 5 and 20.
    increaseHealth(healAmount);
    std::cout << name << " heals!" << std::endl;
}

// Performs a special attack with higher damage.
// Returns the damage dealt, which ranges from 20 to 50.
int Enemy::specialAttack() {
    int damage = rand() % 30 + 20; // Random damage between 20 and 50.
    std::cout << name << " uses a special attack, dealing " << damage << " damage!" << std::endl;
    return damage;
}
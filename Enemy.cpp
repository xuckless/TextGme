#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(const std::string& name, int initialHealth)
    : name(name), health(initialHealth) {}

std::string Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

void Enemy::decreaseHealth(int amount) {
    health -= amount;
    std::cout << name << " took " << amount << " damage!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

void Enemy::increaseHealth(int amount) {
    health += amount;
    std::cout << name << " healed by " << amount << " points!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

bool Enemy::isDead() const {
    return health <= 0;
}

int Enemy::attack() {
    // Basic random damage
    int damage = rand() % 20 + 10; // Damage range: 10 to 30
    std::cout << name << " attacks and deals " << damage << " damage!" << std::endl;
    return damage;
}

void Enemy::defend() {
    std::cout << name << " defends, reducing incoming damage by half on the next turn!" << std::endl;
    // Implementation for reducing damage could be handled in the game logic
}

void Enemy::heal() {
    int healAmount = rand() % 15 + 5; // Heal range: 5 to 20
    increaseHealth(healAmount);
    std::cout << name << " heals!" << std::endl;
}

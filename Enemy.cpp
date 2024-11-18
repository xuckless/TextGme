// Enemy.cpp

#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(const std::string& name, int initialHealth)
    : name(name), health(initialHealth) {} //this intizles the enemys name and health

std::string Enemy::getName() const { //this returns the enemys name
    return name;
}

int Enemy::getHealth() const { //this returns the enemys health
    return health;
}

void Enemy::decreaseHealth(int amount) { //this decreases the health of the enemy when called
    health -= amount; //this will decrase the enemys health based on amount
    std::cout << name << " took " << amount << " damage!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

void Enemy::increaseHealth(int amount) { //this addsa health to the enemy
    health += amount; //this adds health to the enemy
    std::cout << name << " healed by " << amount << " points!" << std::endl;
    std::cout << name << "'s current health: " << health << std::endl;
}

bool Enemy::isDead() const { //this will return if the enemys health is equal to zero
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

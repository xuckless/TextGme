// Player.cpp
#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int initialAura, int initialHealth)
    : name(name), aura(initialAura), maxAura(1000000000), health(initialHealth) {
    if (name == "Gojo Satoru") {
        std::cout << "He's the honored one" << std::endl;
    }
}

Player::Player(const std::string& name) : Player(name, 0, 100) {}

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

int Player::increaseAura(int amount) {
    if (aura + amount > maxAura) {
        std::cout << "Aura is full" << std::endl;
        return 0;
    }
    aura += amount;
    std::cout << "Aura increased by " << amount << std::endl;
    std::cout << "Current aura: " << aura << std::endl;
    return aura;
}

void Player::decreaseAura(int amount) {
    if (aura - amount < 0) {
        aura = 0;
        std::cout << "Aura is empty, you lost against Sukuna" << std::endl;
    } else {
        aura -= amount;
        std::cout << "Aura decreased by " << amount << std::endl;
        std::cout << "Current aura: " << aura << std::endl;
    }
}

int Player::increaseHealth(int amount) {
    health += amount;
    std::cout << "Health increased by " << amount << std::endl;
    std::cout << "Current health: " << health << std::endl;
    return health;
}

void Player::decreaseHealth(int amount) {
    health -= amount;
    std::cout << "Health decreased by " << amount << std::endl;
    std::cout << "Current health: " << health << std::endl;
}

bool Player::isDead() const {
    return health <= 0;
}

bool Player::battle(int enemyAura) {
    this->decreaseAura(enemyAura);
    return aura > 0;
}

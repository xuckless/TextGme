// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(int aura) : name("Nightmare"), aura(aura) {
}

std::string Enemy::toString() const {
    return "Enemy " + name + " has aura " + std::to_string(aura);
}

int Enemy::getAura() const {
    return aura;
}

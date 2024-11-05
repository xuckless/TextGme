// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "Level.h"
#include <iostream>
#include "Player.cpp"
#include "Enemy.cpp"

class LevelOne : public Level {
private:
    bool isComplete = false;

public:
    LevelOne() = default;

    void proceed() override {
        std::cout << "Hello, welcome to Level 1" << std::endl;

        std::cout << "What's your name?" << std::endl;
        std::string name;
        std::cin >> name;

        // Using smart pointers to manage memory
        auto player = std::make_shared<Player>(name, 20);
        auto enemy = std::make_shared<Enemy>(150);

        int choice;

        std::cout << "Do you want to look around? (1 (yes)/2 (no))" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "You found a chest and a door" << std::endl;
            std::cout << "Do you want to open the chest or the door? (1 (chest)/2 (door))" << std::endl;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "You got 75 aura" << std::endl;
                player->increaseAura(75);
            } else if (choice == 2) {
                std::cout << "Welcome to the hallway" << std::endl;
                std::cout << "Do you want to look around? (1 (yes)/2 (no))" << std::endl;
                std::cin >> choice;

                if (choice == 1) {
                    std::cout << "You found a chest and a door" << std::endl;
                    std::cout << "Do you want to open the chest or the door? (1 (chest)/2 (door))" << std::endl;
                    std::cin >> choice;

                    if (choice == 1) {
                        std::cout << "You got 80 aura" << std::endl;
                        player->increaseAura(80);
                        std::cout << "You have " << player->getAura() << " aura" << std::endl;
                    } else {
                        std::cout << "There is a monster behind the door, and he has 150 aura. Do you want to pass the door and fight him?" << std::endl;
                        std::cout << "1 (yes)/2 (no)" << std::endl;
                        std::cin >> choice;

                        if (choice == 1) {
                            std::cout << "You have defeated the monster" << std::endl;
                            isComplete = true;
                        } else {
                            std::cout << "You're just standing there, buddy" << std::endl;
                        }
                    }
                }
            }
        }

        isComplete = true;
    }
};

#endif // LEVELONE_H
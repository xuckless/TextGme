// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "Level.h"
#include <iostream>
#include <memory> // Include memory for smart pointers
#include "Player.cpp"
#include "Enemy.cpp"

class LevelOne : public Level {
private:
    bool isComplete = false;

public:
    LevelOne() = default;

    void proceed() override {
        std::cout << "Hello, welcome to Level 1!" << std::endl;

        std::cout << "What's your name?" << std::endl;
        std::string name;
        std::cin >> name;

        // Using smart pointers to manage memory
        auto player = std::make_shared<Player>(name, 20);
        auto enemy = std::make_shared<Enemy>(150);

        int choice;

        std::cout << "\nDo you want to look around? (1 - Yes / 2 - No)" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\nYou found a chest and a door." << std::endl;
            std::cout << "Do you want to open the chest or the door? (1 - Chest / 2 - Door)" << std::endl;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nYou opened the chest and found 75 aura!" << std::endl;
                player->increaseAura(75);
                std::cout << "You now have " << player->getAura() << " aura." << std::endl;
            } else if (choice == 2) {
                std::cout << "\nYou opened the door and proceed to the hallway." << std::endl;
            } else {
                std::cout << "\nInvalid choice. You decide to proceed to the hallway." << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "\nYou chose not to look around and proceed forward." << std::endl;
        } else {
            std::cout << "\nInvalid choice. You decide to proceed forward." << std::endl;
        }

        // Proceed to the hallway
        std::cout << "\nYou arrive at the hallway." << std::endl;

        std::cout << "\nDo you want to look around? (1 - Yes / 2 - No)" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\nYou found another chest and a door." << std::endl;
            std::cout << "Do you want to open the chest or the door? (1 - Chest / 2 - Door)" << std::endl;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nYou opened the chest and found 80 aura!" << std::endl;
                player->increaseAura(80);
                std::cout << "You now have " << player->getAura() << " aura." << std::endl;
            } else if (choice == 2) {
                // Proceed to fight the boss
                std::cout << "\nYou opened the door and see a monster with 150 aura!" << std::endl;
            } else {
                std::cout << "\nInvalid choice. You decide to proceed through the door." << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "\nYou chose not to look around and proceed forward." << std::endl;
        } else {
            std::cout << "\nInvalid choice. You decide to proceed forward." << std::endl;
        }

        // Proceed to fight the boss
        std::cout << "\nYou encounter a monster with 150 aura. Do you want to fight it? (1 - Yes / 2 - No)" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            if (player->getAura() >= enemy->getAura()) {
                std::cout << "\nYou have defeated the monster!" << std::endl;
                isComplete = true;
            } else {
                std::cout << "\nThe monster defeated you. Game over." << std::endl;
                isComplete = false;
            }
        } else if (choice == 2) {
            std::cout << "\nYou chose not to fight the monster. You cannot proceed without defeating it." << std::endl;
            isComplete = false;
        } else {
            std::cout << "\nInvalid choice. The monster attacks you!" << std::endl;
            std::cout << "\nYou have been defeated. Game over." << std::endl;
            isComplete = false;
        }

        if (isComplete) {
            std::cout << "\nCongratulations, " << player->getName() << "! You have completed Level 1." << std::endl;
        } else {
            std::cout << "\nLevel 1 incomplete. Better luck next time, " << player->getName() << "." << std::endl;
        }
    }
};

#endif // LEVELONE_H

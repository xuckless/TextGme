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
                std::cout << "You now have " << player->getAura() << " aura" << std::endl;
                // Proceed to the hallway after opening the chest
                std::cout << "You proceed to the hallway." << std::endl;
            } else if (choice == 2) {
                std::cout << "Welcome to the hallway" << std::endl;
            } else {
                std::cout << "Invalid choice. Proceeding to the hallway by default." << std::endl;
            }

            // Common code for proceeding in the hallway
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
                } else if (choice == 2) {
                    std::cout << "There is a monster behind the door, and he has 150 aura. Do you want to pass the door and fight him?" << std::endl;
                    std::cout << "1 (yes)/2 (no)" << std::endl;
                    std::cin >> choice;

                    if (choice == 1) {
                        std::cout << "You have defeated the monster" << std::endl;
                        isComplete = true;
                    } else {
                        std::cout << "You're just standing there, buddy" << std::endl;
                    }
                } else {
                    std::cout << "Invalid choice. You decide to rest for a while." << std::endl;
                }
            } else if (choice == 2) {
                std::cout << "You decided not to look around. Do you want to proceed to the door ahead? (1 (yes)/2 (no))" << std::endl;
                std::cin >> choice;
                if (choice == 1) {
                    std::cout << "There is a monster behind the door, and he has 150 aura. Do you want to fight him?" << std::endl;
                    std::cout << "1 (yes)/2 (no)" << std::endl;
                    std::cin >> choice;

                    if (choice == 1) {
                        std::cout << "You have defeated the monster" << std::endl;
                        isComplete = true;
                    } else {
                        std::cout << "You're just standing there, buddy" << std::endl;
                    }
                } else {
                    std::cout << "Game over. You chose not to proceed." << std::endl;
                }
            } else {
                std::cout << "Invalid choice. Game over." << std::endl;
            }
        } else if (choice == 2) {
            // Player chooses not to look around initially
            std::cout << "You decided not to look around." << std::endl;
            std::cout << "Do you want to proceed to the hallway? (1 (yes)/2 (no))" << std::endl;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "Welcome to the hallway" << std::endl;
                // Similar code as above for the hallway
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
                    } else if (choice == 2) {
                        std::cout << "There is a monster behind the door, and he has 150 aura. Do you want to pass the door and fight him?" << std::endl;
                        std::cout << "1 (yes)/2 (no)" << std::endl;
                        std::cin >> choice;

                        if (choice == 1) {
                            std::cout << "You have defeated the monster" << std::endl;
                            isComplete = true;
                        } else {
                            std::cout << "You're just standing there, buddy" << std::endl;
                        }
                    } else {
                        std::cout << "Invalid choice. You decide to rest for a while." << std::endl;
                    }
                } else if (choice == 2) {
                    std::cout << "You decided not to look around. Do you want to proceed to the door ahead? (1 (yes)/2 (no))" << std::endl;
                    std::cin >> choice;
                    if (choice == 1) {
                        std::cout << "There is a monster behind the door, and he has 150 aura. Do you want to fight him?" << std::endl;
                        std::cout << "1 (yes)/2 (no)" << std::endl;
                        std::cin >> choice;

                        if (choice == 1) {
                            std::cout << "You have defeated the monster" << std::endl;
                            isComplete = true;
                        } else {
                            std::cout << "You're just standing there, buddy" << std::endl;
                        }
                    } else {
                        std::cout << "Game over. You chose not to proceed." << std::endl;
                    }
                } else {
                    std::cout << "Invalid choice. Game over." << std::endl;
                }
            } else {
                std::cout << "Game over. You chose not to proceed." << std::endl;
            }
        } else {
            std::cout << "Invalid choice. Game over." << std::endl;
        }

        if (isComplete) {
            std::cout << "Congratulations! You have completed Level 1." << std::endl;
        } else {
            std::cout << "Level 1 incomplete. Try again." << std::endl;
        }
    }
};

#endif // LEVELONE_H

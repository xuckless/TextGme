// LevelOne.h
#ifndef LEVELONE_H
#define LEVELONE_H

#include "Level.h"
#include <iostream>
#include "Player.cpp"

class LevelOne : public Level {
private:
    bool isComplete = false; 

public:
    LevelOne() = default;

    void proceed() override {
        std::cout << "Hello, welcome to the Level 1" << std::endl;

        std::cout<<"Whats your name?"<<std::endl;
        std::string name;

        std::cin>>name;

        Player *player = new Player(name, 20);

        int choice;

        std::cout<<"Do you want to look around? (1 (yes)/2 (no))"<<std::endl;
        std::cin>>choice;

        if (choice == 1) {
            std::cout<<"You found a chest and a door"<<std::endl;
            std::cout<<"Do you want to open the chest or the door? (1 (chest)/2 (door))"<<std::endl;
            std::cin>>choice;

            if (choice == 1) {
                std::cout<<"You got 75 aura"<<std::endl;
                player->increaseAura(75);
            }
        }
        isComplete = true;
    }
};

#endif // LEVELONE_H

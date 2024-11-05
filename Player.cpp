#include <iostream>
#include <string>  // Include this for std::string


using namespace std;
class Player {
private:
    std::string name;
    int aura; //this is the power level of the player
    int maxAura; //this is the max amount of power the player can have

public:
    Player(std::string name, int initialAura = 0) :name{name}, aura{initialAura}, maxAura{1000000000} { //this sets the players name intial aura and the max amount od aura
        std::cout << "Player " << name << " created with aura " << aura << std::endl; //this prints all the player infromation
        if (name == "Gojo Satoru") { //little easter egg
            std::cout << "He's the honored one" << std::endl;
        }
    }

    std::string getName() {
        return name; // returns name
    }

    int getAura() {
        return aura; //returns aura
    }

    int getMaxAura() {
        return maxAura; //retruns max aura
    }

    int increaseAura(int amount) {
        if (aura + amount > maxAura) { //this enfocres the aura cap 
            cout << "Aura is full" << endl;
            return 0;
        }
        aura += amount; //this adds more aura to the plater and prints the amount it increased by and your new aura level
        cout << "Aura increased by " << amount << endl;
        cout << "Current aura: " << aura << endl;
    }

    void decreaseAura(int amount) {
        if (aura - amount < 0) {
            aura = 0; //this checks if your aura is equal to zero if it is the game ends
            cout << "Aura is empty, you lost against sukunaa" << endl;
        } else {
            aura-=amount; //if aura isnt zero this decreases the amount of aura and prints how much it was decreased by
            cout << "Aura decreased by " << amount << endl;
            cout << "Current aura: " << aura << endl;
        }
    }
};

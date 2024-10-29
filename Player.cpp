#include <iostream>
#include <string>  // Include this for std::string


using namespace std;
class Player {
private:
    std::string name;
    int aura;
    int maxAura;

public:
    Player(std::string name, int initialAura = 0) :name{name}, aura{initialAura}, maxAura{1000000000} {
        std::cout << "Player " << name << " created with aura " << aura << std::endl;
        if (name == "Gojo Satoru") {
            std::cout << "He's the honored one" << std::endl;
        }
    }

    std::string getName() {
        return name;
    }

    int getAura() {
        return aura;
    }

    int getMaxAura() {
        return maxAura;
    }

    int increaseAura(int amount) {
        if (aura + amount > maxAura) {
            cout << "Aura is full" << endl; return 0;
        }
        aura += amount;
        cout << "Aura increased by " << amount << endl;
        cout << "Current aura: " << aura << endl;
    }

    void decreaseAura(int amount) {
        if (aura - amount < 0) {
            aura = 0;
            cout << "Aura is empty, you lost against sukunaa" << endl;
        }
    }
};
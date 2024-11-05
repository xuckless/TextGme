#include <iostream>


using namespace std;

class Enemy {
private:
    std::string name;
    const int aura; //this is the enemys health bar

public:
    Enemy(int aura) :name{"Nightmare"}, aura{aura} { //delacrtion of a new enemy
    }

    virtual std::string toString( ) const {
        return "Enemy " + name + " has aura " + std::to_string(aura); //this will display the name of the enemy and the "aura" or power level of the enemy
    }

    int getAura() const { //this just returns the enemys aura
        return aura;
    }
};

#include <iostream>


using namespace std;

class Enemy {
private:
    std::string name;
    const int aura;

public:
    Enemy(int aura) :name{"Nightmare"}, aura{aura} {
    }

    virtual std::string toString( ) const {
        return "Enemy " + name + " has aura " + std::to_string(aura);
    }

    int getAura() const {
        return aura;
    }
};

#include <iostream>
#include <memory>
#include <string>

class Levels {
public:
    Levels() {
        // Constructor logic (if any)
    }

    virtual ~Levels() = default;

    // Define a virtual function to mimic Java's toString()
    virtual std::string toString() const {
        return "Levels{}";
    }
};

class LevelOne : public Levels {
public:
    LevelOne() : Levels() {
        // Constructor logic specific to LevelOne (if any)
    }

    // Override toString() if you want a different string representation
    std::string toString() const override {
        return "LevelOne{}";
    }
};
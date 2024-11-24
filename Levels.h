#ifndef LEVELS_H
#define LEVELS_H

#include "LevelHandler.h"
#include "LevelOne.h"
#include <memory>

class Levels {
private:
    LevelHandler* firstLevel;

public:
    Levels();
    ~Levels();

    void setUp();
    void startLevels();
};

#endif // LEVELS_H

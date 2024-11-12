// Levels.h
#ifndef LEVELS_H
#define LEVELS_H

#include "LevelHandler.h"

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

// LevelHandler.h
#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include "Level.h"

class LevelHandler {
private:
    Level* level;
    LevelHandler* nextLevel;

public:
    LevelHandler(Level* level, LevelHandler* nextLevel = nullptr);
    ~LevelHandler();

    LevelHandler* getNextLevel();
    Level* getLevel();
    void addLevelAfter(Level* level);
    void addLevelInLast(Level* level);
    void removeLevelAfter();
    void removeFromLast();
};

#endif // LEVELHANDLER_H

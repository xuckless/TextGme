#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include "Level.h"
#include <memory>

class LevelHandler : public std::enable_shared_from_this<LevelHandler> {
private:
    std::shared_ptr<Level> level;
    std::shared_ptr<LevelHandler> nextLevel;

public: //this is a linked list that handles all the levels allowing us to have easier time calling them 
    LevelHandler(std::shared_ptr<Level> level, std::shared_ptr<LevelHandler> nextLevel = nullptr)
        : level(level), nextLevel(nextLevel) {}

    std::shared_ptr<LevelHandler> getNextLevel() { //this returns the next level
        return nextLevel;
    }

    std::shared_ptr<Level> getLevel() { //this returns the current level
        return level;
    }

    void addLevelAfter(std::shared_ptr<Level> newLevel) { //this function adds a level after the head of the linked list 
        nextLevel = std::make_shared<LevelHandler>(newLevel, nextLevel);
    }

    void addLevelInLast(std::shared_ptr<Level> newLevel) { //this function adds a level at the end of the linked list
        auto current = shared_from_this();
        while (current->nextLevel) { 
            current = current->nextLevel;
        }
        current->addLevelAfter(newLevel);
    }

    void removeLevelAfter() { //this function removes a level however this function will most likely never be used
        if (nextLevel) {
            nextLevel = nextLevel->getNextLevel();
        }
    }

    void removeFromLast() { //this function is the same case as the one above
        auto current = shared_from_this();
        while (current->nextLevel && current->nextLevel->nextLevel) {
            current = current->nextLevel;
        }
        current->removeLevelAfter();
    }
};

#endif // LEVELHANDLER_H

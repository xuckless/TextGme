#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include "Level.h"
#include <memory>

class LevelHandler : public std::enable_shared_from_this<LevelHandler> {
private:
    std::shared_ptr<Level> level;
    std::shared_ptr<LevelHandler> nextLevel;

public:
    LevelHandler(std::shared_ptr<Level> level, std::shared_ptr<LevelHandler> nextLevel = nullptr)
        : level(level), nextLevel(nextLevel) {}

    std::shared_ptr<LevelHandler> getNextLevel() {
        return nextLevel;
    }

    std::shared_ptr<Level> getLevel() {
        return level;
    }

    void addLevelAfter(std::shared_ptr<Level> newLevel) {
        nextLevel = std::make_shared<LevelHandler>(newLevel, nextLevel);
    }

    void addLevelInLast(std::shared_ptr<Level> newLevel) {
        auto current = shared_from_this();
        while (current->nextLevel) {
            current = current->nextLevel;
        }
        current->addLevelAfter(newLevel);
    }

    void removeLevelAfter() {
        if (nextLevel) {
            nextLevel = nextLevel->getNextLevel();
        }
    }

    void removeFromLast() {
        auto current = shared_from_this();
        while (current->nextLevel && current->nextLevel->nextLevel) {
            current = current->nextLevel;
        }
        current->removeLevelAfter();
    }
};

#endif // LEVELHANDLER_H
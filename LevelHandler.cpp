#include <memory>

class Levels {
    // Implement the Levels class as needed.
};

class LevelHandler {
private:
    Levels level;
    std::unique_ptr<LevelHandler> nextLevel;

public:
    LevelHandler(Levels level, std::unique_ptr<LevelHandler> nextLevel)
        : level(std::move(level)), nextLevel(std::move(nextLevel)) {}

    LevelHandler* getNextLevel() {
        return nextLevel.get();
    }

    Levels getLevel() {
        return level;
    }

    void addLevelAfter(Levels newLevel) {
        nextLevel = std::make_unique<LevelHandler>(std::move(newLevel), std::move(nextLevel));
    }

    void addLevelInLast(Levels newLevel) {
        LevelHandler* current = this;
        while (current->nextLevel) {
            current = current->getNextLevel();
        }
        current->nextLevel = std::make_unique<LevelHandler>(std::move(newLevel), nullptr);
    }

    void removeLevelAfter() {
        if (nextLevel) {
            nextLevel = std::move(nextLevel->nextLevel);
        }
    }

    void removeFromLast() {
        LevelHandler* current = this;
        LevelHandler* previous = nullptr;
        while (current->nextLevel) {
            previous = current;
            current = current->getNextLevel();
        }
        if (previous) {
            previous->nextLevel.reset();
        } else {
            // Can't remove the only node. Handle accordingly if needed.
        }
    }
};
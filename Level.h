// Level.h
#ifndef LEVEL_H
#define LEVEL_H

// Abstract base class representing a game level.
// This interface ensures that all levels implement the proceed functionality,
// allowing the game to progress through levels in a consistent manner.
class Level {
public:
    // Pure virtual function that must be implemented by derived classes.
    // This function defines the behavior or action taken when progressing through the level.
    virtual void proceed() = 0;

    // Virtual destructor to ensure proper cleanup of derived classes.
    virtual ~Level() {}
};

#endif // LEVEL_H
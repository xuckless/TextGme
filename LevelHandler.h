// LevelHandler.h
#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include "Level.h"

class LevelHandler { //this adds the elements needed for a linked list
private:
    Level* level; //this is the pointer for the current level
    LevelHandler* nextLevel; //this allows you to search through the list

public: //these fucntions allow the utlilty of the linked list
    LevelHandler(Level* level, LevelHandler* nextLevel = nullptr);
    ~LevelHandler();

    LevelHandler* getNextLevel();
    Level* getLevel(); //this returns the current level
    void addLevelAfter(Level* level); //this adds a node to a list after the head of the list
    void addLevelInLast(Level* level); //this adds one at the end of the list
    void removeLevelAfter(); //this removes a node after the head of the list
    void removeFromLast(); //this removes the last node of the list
};

#endif // LEVELHANDLER_H

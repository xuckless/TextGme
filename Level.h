// Level.h
#ifndef LEVEL_H
#define LEVEL_H

class Level { 
public:
    virtual void proceed() = 0; // Pure virtual function
    virtual ~Level() = default; // Virtual destructor
};

#endif // LEVEL_H

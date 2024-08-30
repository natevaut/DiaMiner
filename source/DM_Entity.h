// Nate Evans 21144882
#ifndef DM_ENTITY_H
#define DM_ENTITY_H

#include "defs.h"

class DM_Entity
{
    //methods
public:
    DM_Entity(int x, int y, int health, int money);
    virtual ~DM_Entity();
    
    virtual void tick() = 0;

    // instance variables
public:
    byte health;
    int money;
    int xTile;
    int yTile;
};

#endif // DM_ENTITY_H
// Nate Evans 21144882
#ifndef DM_ENTITY_H
#define DM_ENTITY_H

#include "defs.h"
class DM_Game;

class DM_Entity
{
    //methods
public:
    DM_Entity(float x, float y, int health, int money);
    virtual ~DM_Entity();
    
    virtual void Tick(DM_Game* pGame) = 0;
    virtual void Move(float dx, float dy) = 0;
    virtual void EnsureBounds(DM_Game* pGame);

    // instance variables
public:
    byte health;
    int money;
    float xTile;
    float yTile;
};

#endif // DM_ENTITY_H
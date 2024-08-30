// Nate Evans 21144882
#ifndef DM_ENTITY_H
#define DM_ENTITY_H

#include "defs.h"

class DM_Entity
{
    //methods
public:
    DM_Entity(int x, int y, int health, int money)
        : m_xTile(x)
        , m_yTile(y)
        , m_health(health)
        , m_money(money)
    {
    }

    virtual ~DM_Entity()
    {
    }
    
    virtual void tick() = 0;

    // instance variables
public:
    byte m_health;
    int m_money;

protected:
    int m_xTile;
    int m_yTile;
};

#endif // DM_ENTITY_H
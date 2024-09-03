// Nate Evans 21144882
#ifndef DM_PLAYER_H
#define DM_PLAYER_H

#include "DM_Entity.h"

class DM_World;

enum DamageCause {
    NONE,
    BOMB,
    ENEMY
};

class DM_Player : public DM_Entity
{
    //methods:
public:
    DM_Player();

    void tick() override;
    void move(float dx, float dy);
    void mineBelow(DM_World* pWorld);

protected:
    void diamond(int worth);
    void explosion(int value);
    void attacked(int value);

    // instance variables:
public:
    enum DamageCause damageCause;
protected:

};

#endif //DM_PLAYER_H
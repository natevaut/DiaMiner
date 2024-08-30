// Nate Evans 21144882
#ifndef DM_PLAYER_H
#define DM_PLAYER_H

#include "DM_Entity.h"

class DM_World;

class DM_Player : public DM_Entity
{
    //methods:
public:
    DM_Player();

    void tick() override;

    void diamond(int worth);

    void damage(int value);

    void move(float dx, float dy);

    void mineBelow(DM_World* pWorld);

    // instance variables:
protected:

};

#endif //DM_PLAYER_H
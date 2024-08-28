// Nate Evans 21144882
#ifndef DM_PLAYER_H
#define DM_PLAYER_H

#include "DM_Entity.h"

class DM_Player : public DM_Entity
{
    //methods:
public:
    DM_Player(int x, int y, int health, int money)
        : DM_Entity(x, y, health, money)
    {
    }

    void tick() override;

    void diamond(int worth);

    void damage(int value);

    void move(int dx, int dy);

    void mineBelow();

    // instance variables:

};

#endif //DM_PLAYER_H
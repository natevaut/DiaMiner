// Nate Evans 21144882
#ifndef DM_PLAYER_H
#define DM_PLAYER_H

#include "DM_Entity.h"

class DM_World;
class DM_Game;

enum LatestAction {
    NONE,
    BOMB,
    ENEMY,
    COLLECTED
};

class DM_Player : public DM_Entity
{
    //methods:
public:
    DM_Player();

    void Tick(DM_Game* pGame);
    void Move(float dx, float dy);
    void MineBelow(DM_World* pWorld);

protected:
    void diamond(int worth);
    void explosion(int value);
    void attacked(int value);

    // instance variables:
public:
    enum LatestAction latestAction;
protected:

};

#endif //DM_PLAYER_H
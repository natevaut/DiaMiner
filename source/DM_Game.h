// Nate Evans 21144881
#ifndef DM_GAME_H
#define DM_GAME_H

#include "DM_Player.h"
#include "DM_World.h"
#include "DM_Enemy.h"

class DM_Game
{
    //methods:
public:
    DM_Game(DM_Player* player, DM_World* world, DM_Enemy**enemies)
        : pPlayer(player), pWorld(world), pEnemies(enemies)
    {
    }

    ~DM_Game()
    {
        delete pPlayer;
        delete pWorld;
        delete[] pEnemies;
    }

    //instance variables:

protected:
    DM_Player* pPlayer;
    DM_World* pWorld;
    DM_Enemy** pEnemies;

};

#endif //DM_GAME_H
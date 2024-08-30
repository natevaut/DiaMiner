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
        : m_pPlayer(player)
        , m_pWorld(world)
        , m_pEnemies(enemies)
    {
    }

    ~DM_Game()
    {
        delete m_pPlayer;
        delete m_pWorld;
        delete[] m_pEnemies;
    }

    //instance variables:

protected:
    DM_Player* m_pPlayer;
    DM_World* m_pWorld;
    DM_Enemy** m_pEnemies;

};

#endif //DM_GAME_H
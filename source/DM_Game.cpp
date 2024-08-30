// Nate Evans 21144881
#include "DM_Game.h"

DM_Game::DM_Game()
    : pWorld(new DM_World(15, 10)) // 15x10 tile world
    , pPlayer(new DM_Player())
    , pEnemies(new DM_Enemy*[10])
{
}

DM_Game::~DM_Game()
{
    delete pPlayer;
    delete pWorld;
    delete[] pEnemies;
}

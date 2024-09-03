// Nate Evans 21144881
#include "DM_Game.h"

DM_Game::DM_Game()
    : pWorld(new DM_World(15, 10, 5)) // 15x10x5 tile world
    , pPlayer(new DM_Player())
    , pEnemies(new DM_Enemy*[10])
    , outcome(Outcome::IN_PLAY)
{
}

DM_Game::~DM_Game()
{
    delete pPlayer;
    delete pWorld;
    delete[] pEnemies;
}

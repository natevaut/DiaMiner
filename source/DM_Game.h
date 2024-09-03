// Nate Evans 21144881
#ifndef DM_GAME_H
#define DM_GAME_H

#include "DM_Player.h"
#include "DM_World.h"
#include "DM_Enemy.h"

enum Outcome
{
    IN_PLAY,
    PLAYER_WINS,
    PLAYER_LOSES
};

class DM_Game
{
    //methods:
public:
    DM_Game();
    ~DM_Game();

    //instance variables:

public:
    DM_Player* pPlayer;
    DM_World* pWorld;
    DM_Enemy** pEnemies;
    enum Outcome outcome;

};

#endif //DM_GAME_H
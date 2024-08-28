// Nate Evans 21144881
#ifndef DM_ENEMY_H
#define DM_ENEMY_H

#include "DM_Entity.h"

enum class Personality
{
    AGGRESSIVE,
    PASSIVE
};


class DM_Enemy : public DM_Entity
{
    //methods:
public:
    DM_Enemy(int x, int y, int health, int money, Personality personality)
        : DM_Entity(x, y, health, money)
        , personality(personality)
        , isAttacking(false)
    {
    }

    void tick() override;

private:
    void randomMove();

    void mineBelow();

    //instance variables:
public:
    Personality personality;
    bool isAttacking;
};

#endif // DM_ENEMY_H
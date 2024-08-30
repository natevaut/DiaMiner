// Nate Evans 21144881
#include "DM_Enemy.h"

DM_Enemy::DM_Enemy(float x, float y, int health, int money, Personality personality)
    : DM_Entity(x, y, health, money)
    , m_personality(personality)
    , m_isAttacking(false)
{
}

void DM_Enemy::tick()
{
    randomMove();
}

void DM_Enemy::randomMove()
{
}

void DM_Enemy::mineBelow()
{
}

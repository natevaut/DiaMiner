// Nate Evans 21144881
#include "DM_Enemy.h"

#include "inlinehelper.h"

DM_Enemy::DM_Enemy(float x, float y)
    : DM_Entity(x, y, 100, 0)
    , m_personality(randPersonality())
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

DM_Personality DM_Enemy::randPersonality()
{
    if (GetRandomPercentage() < 0.50f)
        return DM_Personality::AGGRESSIVE;
    else
        return DM_Personality::PASSIVE;
}

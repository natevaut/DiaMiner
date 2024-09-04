// Nate Evans 21144881
#include "DM_Enemy.h"

#include "inlinehelper.h"

DM_Enemy::DM_Enemy(float x, float y)
    : DM_Entity(x, y, 100, 0)
    , m_personality(randPersonality())
    , m_isAttacking(false)
    , m_direction(DM_Direction::UP)
{
}

void DM_Enemy::Tick(DM_Game* pGame)
{
    randomMove();
    EnsureBounds(pGame);
}

void DM_Enemy::Move(float x, float y)
{
    randomMove();
}

void DM_Enemy::randomMove()
{
    float mvChangeChance = 0.01f;
    if (GetRandomPercentage() < mvChangeChance / 4) m_direction = DM_Direction::UP;
    if (GetRandomPercentage() < mvChangeChance / 4) m_direction = DM_Direction::DOWN;
    if (GetRandomPercentage() < mvChangeChance / 4) m_direction = DM_Direction::LEFT;
    if (GetRandomPercentage() < mvChangeChance / 4) m_direction = DM_Direction::RIGHT;

    float mvAmt = 0.1f;
    float mvChance = 0.05f;
    if (GetRandomPercentage() < mvChance)
    {
        switch (m_direction)
        {
        case UP: xTile -= mvAmt; break;
        case DOWN: xTile += mvAmt; break;
        case LEFT: yTile -= mvAmt; break;
        case RIGHT: yTile += mvAmt; break;
        }
    }
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

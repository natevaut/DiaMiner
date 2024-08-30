// Nate Evans 21144882

#include "DM_Player.h"

DM_Player::DM_Player()
    : DM_Entity(0, 0, 100, 0)
{
}

void DM_Player::tick()
{
}

void DM_Player::diamond(int worth)
{
    m_money += worth;
}

void DM_Player::damage(int value)
{
    m_health -= value;
}

void DM_Player::move(int dx, int dy)
{
    m_xTile += dx;
    m_yTile += dy;
}

void DM_Player::mineBelow()
{
}

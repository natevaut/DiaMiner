// Nate Evans 21144882

#include "DM_Player.h"

void DM_Player::tick()
{
}

void DM_Player::diamond(int worth)
{
    money += worth;
}

void DM_Player::damage(int value)
{
    health -= value;
}

void DM_Player::move(int dx, int dy)
{
    xTile += dx;
    yTile += dy;
}

void DM_Player::mineBelow()
{
}

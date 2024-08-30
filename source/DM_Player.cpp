// Nate Evans 21144882

#include "DM_Player.h"
#include "DM_World.h"

DM_Player::DM_Player()
    : DM_Entity(0, 0, 100, 0)
{
}

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

void DM_Player::move(float dx, float dy)
{
    xTile += dx;
    yTile += dy;
}

void DM_Player::mineBelow(DM_World *pWorld)
{
    pWorld->mineBelow((int)xTile, (int)yTile);
}

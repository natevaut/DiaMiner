// Nate Evans 21144882

#include "DM_Player.h"

#include <SDL.h>

#include "logmanager.h"

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

void DM_Player::move(int dx, int dy)
{
    xTile += dx;
    yTile += dy;

    LogManager::GetInstance().Log("Player movement");
}

void DM_Player::mineBelow()
{
}

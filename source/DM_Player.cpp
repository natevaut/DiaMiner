// Nate Evans 21144882

#include "logmanager.h"

#include "DM_Player.h"
#include "DM_World.h"
#include "DM_Tile.h"

const int BOMB_DAMAGE = 10;

DM_Player::DM_Player()
    : DM_Entity(0, 0, 100, 0)
    , damageCause(DamageCause::NONE)
{
}

void DM_Player::tick()
{
}

void DM_Player::diamond(int worth)
{
    money += worth;
}

void DM_Player::explosion(int value)
{
    health -= value;

    damageCause = DamageCause::BOMB;
}

void DM_Player::attacked(int value)
{
    health -= value;

    damageCause = DamageCause::ENEMY;
}

void DM_Player::move(float dx, float dy)
{
    xTile += dx;
    yTile += dy;

    damageCause = DamageCause::NONE;
}

void DM_Player::mineBelow(DM_World *pWorld)
{
    DM_Tile tile = pWorld->mineBelow((int) (xTile + 0.5), (int) (yTile + 0.5));
    switch (tile.type) {
    case DM_TileType::DIAMOND:
        diamond(tile.reward);
        LogManager::GetInstance().Log("Diamond mined!");
        break;
    case DM_TileType::EXPLOSIVE:
        explosion(BOMB_DAMAGE);
        LogManager::GetInstance().Log("Explosive hit!");
        break;
    default:
        break;
    }
}

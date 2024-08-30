// Nate Evans 21144882
#include "DM_Entity.h"

DM_Entity::DM_Entity(int x, int y, int health, int money)
    : m_xTile(x)
    , m_yTile(y)
    , m_health(health)
    , m_money(money)
{
}

DM_Entity::~DM_Entity()
{
}

// Nate Evans 21144882
#include "DM_Entity.h"

DM_Entity::DM_Entity(float x, float y, int health, int money)
    : xTile(x)
    , yTile(y)
    , health(health)
    , money(money)
{
}

DM_Entity::~DM_Entity()
{
}

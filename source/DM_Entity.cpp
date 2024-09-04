// Nate Evans 21144882
#include "DM_Entity.h"
#include "DM_Game.h"

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

void DM_Entity::EnsureBounds(DM_Game* pGame)
{
	int width = pGame->pWorld->width;
	int height = pGame->pWorld->height;
	if (xTile < 0.0f)
		xTile = 0.0f;
	if (xTile > width - 1)
		xTile = width - 1;
	if (yTile < 0.0f)
		yTile = 0.0f;
	if (yTile > height - 1)
		yTile = height - 1;
}
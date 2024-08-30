// Nate Evans 21144881
#include "DM_tile.h"

#include "inlinehelper.h"

const int MAX_DIAM_WORTH = 1000;
const float DIAM_CHANCE = 0.05f; //  5% chance of diamond
const float BOMB_CHANCE = 0.05f; //  5% chance of bomb
                                 // 90% chance of stone

void DM_Tile::WeightedRandTile(DM_Tile* tile)
{
	float rand = GetRandomPercentage();
	if (rand -= DIAM_CHANCE < 0)
	{
		// Diamond
		tile->type = DM_TileType::DIAMOND;
		tile->reward = GetRandom(1, MAX_DIAM_WORTH);
	}
	else if (rand -= BOMB_CHANCE < 0)
	{
		// Bomb
		tile->type = DM_TileType::EXPLOSIVE;
		tile->reward = 0; // default
	}
	else
	{
		// Stone
		tile->type = DM_TileType::STONE; // default
		tile->reward = 0; // default
	}
}

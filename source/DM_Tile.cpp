// Nate Evans 21144881
#include "DM_tile.h"

#include "inlinehelper.h"

const int MAX_DIAM_WORTH = 1000;
const float DIAM_CHANCE = 0.02f; //  2% chance of diamond
const float BOMB_CHANCE = 0.03f; //  3% chance of bomb
                                 // 95% chance of stone

DM_Tile::DM_Tile()
	: type(DM_TileType::STONE)
	, reward(0)
{
}

DM_Tile::DM_Tile(DM_TileType type, int reward)
	: type(type)
	, reward(reward)
{
}

DM_Tile DM_Tile::WeightedRandTile()
{
	DM_Tile tile;

	if (GetRandomPercentage() <= DIAM_CHANCE)
	{
		// Diamond
		tile.type = DM_TileType::DIAMOND;
		tile.reward = GetRandom(1, MAX_DIAM_WORTH);
	}
	else if (GetRandomPercentage() <= BOMB_CHANCE)
	{
		// Bomb
		tile.type = DM_TileType::EXPLOSIVE;
		tile.reward = 0; // default
	}
	else
	{
		// Stone
		tile.type = DM_TileType::STONE; // default
		tile.reward = 0; // default
	}

	return tile;
}

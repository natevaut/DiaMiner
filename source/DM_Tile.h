// Nate Evans 21144881
#ifndef DM_TILE_H
#define DM_TILE_H

enum class DM_TileType
{
    STONE,
    DIAMOND,
    EXPLOSIVE
};

class DM_Tile
{
    // methods:
public:

    DM_Tile()
        : type(DM_TileType::STONE), reward(0)
    {
    }

    DM_Tile(DM_TileType type, int reward)
        : type(type), reward(reward)
    {
    }

    static void WeightedRandTile(DM_Tile* tile);

    // instance variables:
public:
    DM_TileType type;
    int reward;
};

#endif // DM_TILE_H

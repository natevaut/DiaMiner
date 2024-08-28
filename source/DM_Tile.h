// Nate Evans 21144881
#ifndef DM_TILE_H
#define DM_TILE_H

enum class DM_TileType
{
    STONE,
    DIAMOND,
    EXPLOSIVE
};

struct DM_Tile
{
    DM_TileType type;
    int hardness;
    int reward;

    DM_Tile(DM_TileType type, int hardness, int reward)
        : type(type), hardness(hardness), reward(reward)
    {
    }
};

#endif // DM_TILE_H

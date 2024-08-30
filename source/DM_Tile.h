// Nate Evans 21144881
#ifndef DM_TILE_H
#define DM_TILE_H

#define TILE_SIZE_PX 16

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

    DM_Tile();
    DM_Tile(DM_TileType type, int reward);

    static DM_Tile WeightedRandTile();

    // instance variables:
public:
    DM_TileType type;
    int reward;
};

#endif // DM_TILE_H

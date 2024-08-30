// Nate Evans 21144881
#include "DM_World.h"

#include "inlinehelper.h"

DM_World::DM_World(int w, int h)
    : width(w), height(h), depth(TILE_DEPTH)
    , wOffset(0), hOffset(0)
{
    // mem allocate
    tiles = new DM_Tile**[sizeA];
    for (int i = 0; i < sizeA; ++i)
    {
        tiles[i] = new DM_Tile*[sizeB];

        for (int j = 0; j < sizeB; ++j)
        {
            tiles[i][j] = new DM_Tile[sizeC];

            for (int k = 0; k < sizeC; k++)
            {
                DM_Tile tile = DM_Tile::WeightedRandTile();
                if (k == TILE_DEPTH - 1) // top layer
                    tile = DM_Tile(); // clear tile (make it stone)
                tiles[i][j][k] = tile;
            }
        }
    }
}

DM_World::~DM_World()
{
    // free all mem alloc
    for (int i = 0; i < sizeA; ++i)
    {
        for (int j = 0; j < sizeB; ++j)
        {
            delete tiles[i][j];
        }
        delete[] tiles[i];
    }
    delete[] tiles;
}

void DM_World::move(int dx, int dy)
{
    wOffset += dx;
    hOffset += dy;
}

void DM_World::mineBelow()
{
}

int DM_World::getStack(int x, int y)
{
    
    return 0;
}

// Nate Evans 21144881
#include "DM_World.h"

#include "inlinehelper.h"

DM_World::DM_World(int w, int h)
    : width(w), height(h), depth(TILE_DEPTH)
    , wOffset(0), hOffset(0)
{
    // mem allocate
    pTiles = new DM_Tile***[sizeA];
    for (int i = 0; i < sizeA; ++i)
    {
        pTiles[i] = new DM_Tile**[sizeB];

        for (int j = 0; j < sizeB; ++j)
        {
            pTiles[i][j] = new DM_Tile*[sizeC];

            for (int k = 0; k < sizeC; k++)
            {
                DM_Tile *pTile = DM_Tile::WeightedRandTile();
                if (k == TILE_DEPTH - 1) // top layer
                    pTile = new DM_Tile; // clear (make stone)
                pTiles[i][j][k] = pTile;
            }
        }
    }
}

DM_World::~DM_World()
{
    // free all mem allocs
    for (int i = 0; i < sizeA; ++i)
    {
        for (int j = 0; j < sizeB; ++j)
        {
            for (int k = 0; k < sizeC; ++k)
                delete pTiles[i][j][k];
            delete[] pTiles[i][j];
        }
        delete[] pTiles[i];
    }
    delete[] pTiles;
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

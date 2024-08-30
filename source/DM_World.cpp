// Nate Evans 21144881
#include "DM_World.h"

#include <assert.h>

#include "inlinehelper.h"
#include "logmanager.h"

DM_World::DM_World(int w, int h)
    : width(w), height(h), depth(TILE_DEPTH)
    , wOffset(0), hOffset(0)
{
    // mem allocate
    pTiles = new DM_Tile***[width];
    for (int i = 0; i < width; ++i)
    {
        pTiles[i] = new DM_Tile**[height];

        for (int j = 0; j < height; ++j)
        {
            pTiles[i][j] = new DM_Tile*[depth];

            for (int k = 0; k < depth; k++)
            {
                DM_Tile *pTile = DM_Tile::WeightedRandTile();
                if (k == depth - 1) // top layer
                    pTile = new DM_Tile; // clear (make stone)
                else
                    pTile->type = DM_TileType::DIAMOND;
                pTiles[i][j][k] = pTile;
            }
        }
    }
}

DM_World::~DM_World()
{
    // free all mem allocs
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < depth; ++k)
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

void DM_World::mineBelow(int x, int y)
{
    assert(pTiles);
    assert(pTiles[x]);
    assert(pTiles[x][y]);

    // find top tile of stack
    for (int k = 0; k < depth; k++)
    {
        if (k == depth - 1 || pTiles[x][y][k + 1] == NULL) // if is top or above is empty
        {
            // break top tile
            pTiles[x][y][k] = NULL;
            LogManager::GetInstance().Log("Tile broken.");
            break;
        }
    }

}

int DM_World::getStack(int x, int y)
{
    
    return 0;
}

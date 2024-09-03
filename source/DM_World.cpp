// Nate Evans 21144881
#include "DM_World.h"

#include <assert.h>

#include "inlinehelper.h"
#include "logmanager.h"

DM_World::DM_World(int w, int h, int d)
    : width(w), height(h), depth(d)
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
                // make top and bottom layers stone
                if (k == depth - 1 || k == 0)
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

void DM_World::mineBelow(int x, int y)
{
    assert(pTiles);
    assert(pTiles[y]);
    assert(pTiles[y][x]);

    // find top tile of stack
    for (int k = 0; k < sizeC; k++)
    {
        if (k == sizeC - 1 || pTiles[y][x][k + 1] == NULL) // if is top or above is empty
        {
            // do nothing if is bottom tile
            if (k == 0) continue;
            // break top tile
            pTiles[y][x][k] = NULL;
            LogManager::GetInstance().Log("Tile broken.");
            break;
        }
    }

}

int DM_World::getStack(int x, int y)
{
    
    return 0;
}

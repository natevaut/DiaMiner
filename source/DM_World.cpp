// Nate Evans 21144881
#include "DM_World.h"

DM_World::DM_World(int w, int h)
    : width(w), height(h)
    , wOffset(0), hOffset(0)
{
    // mem allocate
    tiles = new DM_Tile**[width];
    for (int i = 0; i < width; ++i)
    {
        tiles[i] = new DM_Tile*[height];
        for (int j = 0; j < height; ++j)
        {
            // init
            tiles[i][j] = 0; // new DM_Tile...
        }
    }
}

DM_World::~DM_World()
{
    // free all mem alloc
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
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

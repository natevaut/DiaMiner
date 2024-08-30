// Nate Evans 21144881
#ifndef DM_WORLD_H
#define DM_WORLD_H

#include "DM_Tile.h"

#define TILE_DEPTH 10

class DM_World
{
    //methods:
public:

    DM_World(int width, int height);
    ~DM_World();

    void move(int dx, int dy);
    void mineBelow();

private:
    int getStack(int x, int y);

    // instance variables
public:
    const int m_width;
    const int m_height;
    int m_wOffset;
    int m_hOffset;
    DM_Tile**** m_pTiles;
};

#endif // DM_WORLD_H
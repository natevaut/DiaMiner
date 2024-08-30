// Nate Evans 21144881
#ifndef DM_WORLD_H
#define DM_WORLD_H

#include "DM_Tile.h"

#define TILE_DEPTH 3

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
    const int width;
    const int height;
    const int depth;
    int wOffset;
    int hOffset;
    DM_Tile*** tiles;
};
#define sizeA width
#define sizeB height
#define sizeC depth

#endif // DM_WORLD_H
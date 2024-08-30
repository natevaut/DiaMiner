// Nate Evans 21144881
#include "DM_World.h"

#include <random>

#include "inlinehelper.h"

DM_World::DM_World(int w, int h)
    : m_width(w), m_height(h)
    , m_wOffset(0), m_hOffset(0)
{
    srand(SEED);
    // mem allocate
    m_pTiles = new DM_Tile***[m_width];
    for (int i = 0; i < m_width; ++i)
    {
        m_pTiles[i] = new DM_Tile**[m_height];
        for (int j = 0; j < m_height; ++j)
        {
            m_pTiles[i][j] = new DM_Tile*[TILE_DEPTH];

            // fill world
            for (int k = 0; k < TILE_DEPTH; k++)
            {
                DM_Tile* pTile = new DM_Tile;
                DM_Tile::WeightedRandTile(pTile);
                m_pTiles[i][j][k] = pTile;
            }
        }
    }
}

DM_World::~DM_World()
{
    // free all mem alloc
    for (int i = 0; i < m_width; ++i)
    {
        for (int j = 0; j < m_height; ++j)
        {
            delete m_pTiles[i][j];
        }
        delete[] m_pTiles[i];
    }
    delete[] m_pTiles;
}

void DM_World::move(int dx, int dy)
{
    m_wOffset += dx;
    m_hOffset += dy;
}

void DM_World::mineBelow()
{
}

int DM_World::getStack(int x, int y)
{
    
    return 0;
}

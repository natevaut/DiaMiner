// COMP710 GP Framework 2022

#include "scene_main.h"

#include <random>

#include "animatedsprite.h"
#include "defs.h"
#include "renderer.h"
#include "sprite.h"
#include "logmanager.h"
#include "inlinehelper.h"

#include "DM_Game.h"
#include "DM_Tile.h"

const int NSPRITES = 500;
const int SCALE = 5;
const int WORLD_START_X = 100;
const int WORLD_START_Y = 300;

SceneMain::SceneMain(int width, int height)
	: Scene(width, height)
	, m_pSprites(NULL)
	, m_pAnimSprites(NULL)
	, m_pGame(NULL)
	, m_spriteN(0)
{
}
SceneMain::~SceneMain()
{
}
bool SceneMain::Initialise(Renderer& renderer)
{
	Renderer* pRenderer = &renderer;

	m_background = 0xdddddd;

	m_pSprites = new Sprite * [NSPRITES];
	m_pAnimSprites = new AnimatedSprite * [NSPRITES];
	for (int i = 0; i < NSPRITES; i++)
	{
		m_pSprites[i] = 0;
		m_pAnimSprites[i] = 0;
	}

	m_pGame = new DM_Game;
	m_pGame->pPlayer->tick();

	createWorldTileSprites(pRenderer);

	Sprite *player = pRenderer->CreateSprite(SPRITE_PATH "player.png");
	m_pSprites[0] = player;

	return true;
}

void SceneMain::Process(float deltaTime)
{
	// set player data
	m_pSprites[0]->SetX(m_pGame->pPlayer->xTile * SCALE);
	m_pSprites[0]->SetY(m_pGame->pPlayer->yTile * SCALE);

	// process all
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pSprites[i] != 0)
			m_pSprites[i]->Process(deltaTime);
		if (m_pAnimSprites[i] != 0)
			m_pAnimSprites[i]->Process(deltaTime);
	}
}

void SceneMain::Draw(Renderer &renderer)
{
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pSprites[i] != 0)
			m_pSprites[i]->Draw(renderer);
		if (m_pAnimSprites[i] != 0)
			m_pAnimSprites[i]->Draw(renderer);
	}
}

void SceneMain::createWorldTileSprites(Renderer* pRenderer) {
	DM_World* pWorld = m_pGame->pWorld;
	DM_Tile*** tiles = pWorld->tiles;
	bool loop = true;
	for (int i = 0; loop && i < pWorld->sizeA; i++)
		for (int j = 0; loop && j < pWorld->sizeB; j++)
			for (int k = 0; loop && k < pWorld->sizeC; k++)
			{
				DM_Tile tile = tiles[i][j][k];

				if (m_spriteN >= NSPRITES)
				{
					LogManager::GetInstance().Log("WARNING: Memory too small to load all sprites!");
					loop = false;
					break;
				}

				const char* filename;
				switch (tile.type)
				{
				case DM_TileType::STONE:
					filename = SPRITE_PATH "tile_stone.png";
					break;
				case DM_TileType::DIAMOND:
					filename = SPRITE_PATH "tile_diamond.png";
					break;
				case DM_TileType::EXPLOSIVE:
					filename = SPRITE_PATH "tile_bomb.png";
					break;
				default:
					filename = SPRITE_PATH "tile_stone.png";
				}
				LogManager::GetInstance().LogPart("Making new tile: ");
				LogManager::GetInstance().Log(filename);

				// create animated sprite
				AnimatedSprite* sprite = pRenderer->CreateAnimatedSprite(filename);
				sprite->SetX(WORLD_START_X + SCALE * TILE_SIZE_PX * j);
				sprite->SetY(WORLD_START_Y + SCALE * TILE_SIZE_PX * i);
				sprite->SetScale(SCALE);
				m_pAnimSprites[m_spriteN++] = sprite;
			}
}
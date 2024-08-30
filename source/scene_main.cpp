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
{
}
SceneMain::~SceneMain()
{
}
bool SceneMain::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	m_background = 0xdddddd;

	m_pSprites = new Sprite * [NSPRITES];
	for (int i = 0; i < NSPRITES; i++)
	{
		m_pSprites[i] = NULL;
	}

	m_pGame = new DM_Game;

	Sprite *player = m_pRenderer->CreateSprite(SPRITE_PATH "player.png");
	m_pSprites[0] = player;

	return true;
}

void SceneMain::Process(float deltaTime)
{
	// Player Tick
	DM_Player* pPlayer = m_pGame->pPlayer;

	// ensure bounds
	int width = m_pGame->pWorld->width;
	int height = m_pGame->pWorld->height;
	if (pPlayer->xTile < 0.0f)
		pPlayer->xTile = 0.0f;
	if (pPlayer->xTile > width)
		pPlayer->xTile = width;
	if (pPlayer->yTile < 0.0f)
		pPlayer->yTile = 0.0f;
	if (pPlayer->yTile > height)
		pPlayer->yTile = height;

	m_pSprites[0]->SetX(WORLD_START_X + pPlayer->xTile * SCALE * TILE_SIZE_PX);
	m_pSprites[0]->SetY(WORLD_START_Y + pPlayer->yTile * SCALE * TILE_SIZE_PX);

	createWorldTileSprites(m_pRenderer);

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
	// draw animated sprites (tiles)
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pAnimSprites[i] != 0)
			m_pAnimSprites[i]->Draw(renderer);
	}
	// then draw regular sprites (i.e. player and HUD) over animated ones (tiles)
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pSprites[i] != 0)
			m_pSprites[i]->Draw(renderer);
	}
}

void SceneMain::ProcessInput(const Uint8* state) {
	DM_Player* pPlayer = m_pGame->pPlayer;
	DM_World* pWorld = m_pGame->pWorld;
	if (state[SDL_SCANCODE_W]) pPlayer->move(0, -0.1f); // Move up
	if (state[SDL_SCANCODE_A]) pPlayer->move(-0.1f, 0); // Move left
	if (state[SDL_SCANCODE_S]) pPlayer->move(0, +0.1f); // Move down
	if (state[SDL_SCANCODE_D]) pPlayer->move(+0.1f, 0); // Move right
	if (state[SDL_SCANCODE_X]) pPlayer->mineBelow(pWorld); // Mine down
}

void SceneMain::createWorldTileSprites(Renderer* pRenderer) {
	DM_World* pWorld = m_pGame->pWorld;
	DM_Tile*** *pTiles = pWorld->pTiles;
	bool loop = true;

	int n = 0;
	m_pAnimSprites = new AnimatedSprite * [NSPRITES];
	for (int i = 0; i < NSPRITES; i++) {
		m_pAnimSprites[i] = NULL;
	}

	for (int i = 0; loop && i < pWorld->width; i++)
		for (int j = 0; loop && j < pWorld->height; j++)
			for (int k = 0; loop && k < pWorld->depth; k++)
			{
				DM_Tile *pTile = pTiles[i][j][k];
				if (pTile == NULL)
					break;

				if (n >= NSPRITES)
				{
					LogManager::GetInstance().Log("WARNING: Memory too small to load all sprites!");
					loop = false;
					break;
				}

				const char* filename;
				switch (pTile->type)
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
				m_pAnimSprites[n++] = sprite;
			}
}
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

#define seconds

#define NSPRITES 20
// static sprites:
#define SPRITEN_HEALTHTEXT 1
#define SPRITEN_HEALTHBALLBG 2
#define SPRITEN_HEALTHBALL 3
#define SPRITEN_MONEYTEXT 4
#define SPRITEN_MONEYBALLBG 5
#define SPRITEN_MONEYBALL 6
#define SPRITEN_WINMSG 10
#define SPRITEN_LOSEMSG 11
// animated sprites:
#define SPRITEN_EXPLOSION 0
#define SPRITEN_GLIMMER 1

const int SCALE = 5;
const int WORLD_START_X = 300;
const int WORLD_START_Y = 300;

SceneMain::SceneMain(int width, int height)
	: Scene(width, height)
	, m_pSprites(NULL)
	, m_pAnimSprites(NULL)
	, m_pTileSprites(NULL)
	, m_pRenderer(NULL)
	, m_pGame(NULL)
	, m_pfStateCooldowns(NULL)
	, m_pPlayerSprite(NULL)
{
}
SceneMain::~SceneMain()
{
}
bool SceneMain::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;
	m_pGame = new DM_Game;

	m_background = 0xdddddd;

	m_pSprites = new Sprite *[NSPRITES];
	m_pAnimSprites = new AnimatedSprite *[NSPRITES];
	for (int i = 0; i < NSPRITES; i++)
	{
		m_pSprites[i] = NULL;
		m_pAnimSprites[i] = NULL;
	}

	m_pPlayerSprite = m_pRenderer->CreateSprite(SPRITE_PATH "player.png");

	// Scene sprites:
	Sprite* pHealthLabel = m_pRenderer->CreateSprite(SPRITE_PATH "label_Health.png");
	pHealthLabel->SetX(400);
	pHealthLabel->SetY(200);
	pHealthLabel->SetScale(-1);
	m_pSprites[SPRITEN_HEALTHTEXT] = pHealthLabel;
	Sprite* pHealth = m_pRenderer->CreateSprite(SPRITE_PATH "ball.png");
	pHealth->SetX(600);
	pHealth->SetY(200);
	pHealth->SetRedTint(1);
	pHealth->SetGreenTint(0.2f);
	pHealth->SetBlueTint(0.2f);
	pHealth->SetScale(0.25f);
	m_pSprites[SPRITEN_HEALTHBALL] = pHealth;
	Sprite* pHealthBG = m_pRenderer->CreateSprite(SPRITE_PATH "ball.png");
	pHealthBG->SetX(600);
	pHealthBG->SetY(200);
	pHealthBG->SetScale(0.25f);
	m_pSprites[SPRITEN_HEALTHBALLBG] = pHealthBG;
	Sprite* pMoneyLabel = m_pRenderer->CreateSprite(SPRITE_PATH "label_Cash.png");
	pMoneyLabel->SetX(1000);
	pMoneyLabel->SetY(200);
	pMoneyLabel->SetScale(-1);
	m_pSprites[SPRITEN_MONEYTEXT] = pMoneyLabel;
	Sprite* pMoney = m_pRenderer->CreateSprite(SPRITE_PATH "ball.png");
	pMoney->SetX(1150);
	pMoney->SetY(200);
	pMoney->SetScale(0.0f);
	pMoney->SetRedTint(0.3f);
	pMoney->SetBlueTint(1.0f);
	pMoney->SetGreenTint(0.5f);
	m_pSprites[SPRITEN_MONEYBALL] = pMoney;
	Sprite* pMoneyBG = m_pRenderer->CreateSprite(SPRITE_PATH "ball.png");
	pMoneyBG->SetX(1150);
	pMoneyBG->SetY(200);
	pMoneyBG->SetScale(0.25f);
	m_pSprites[SPRITEN_MONEYBALLBG] = pMoneyBG;
	Sprite* pWinMsg = m_pRenderer->CreateSprite(SPRITE_PATH "outcome_Win.png");
	pWinMsg->SetX(800);
	pWinMsg->SetY(1200);
	pWinMsg->SetScale(0.0f);
	m_pSprites[SPRITEN_WINMSG] = pWinMsg;
	Sprite* pLoseMsg = m_pRenderer->CreateSprite(SPRITE_PATH "outcome_Loss.png");
	pLoseMsg->SetX(800);
	pLoseMsg->SetY(1200);
	pLoseMsg->SetScale(0.0f);
	m_pSprites[SPRITEN_LOSEMSG] = pLoseMsg;

	AnimatedSprite* pExplosion = m_pRenderer->CreateAnimatedSprite(SPRITE_PATH "explosion.png");
	m_pAnimSprites[SPRITEN_EXPLOSION] = pExplosion;
	AnimatedSprite* pGlimmer = m_pRenderer->CreateAnimatedSprite(SPRITE_PATH "glimmer.png");
	m_pAnimSprites[SPRITEN_GLIMMER] = pGlimmer;

	createWorldTileSprites();

	// Cooldown times
	m_pfStateCooldowns = new float[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		m_pfStateCooldowns[i] = 0 seconds;
	}

	return true;
}

void SceneMain::Process(float deltaTime seconds)
{
	// Process all sprites
	m_pPlayerSprite->Process(deltaTime);
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pSprites[i] != 0)
			m_pSprites[i]->Process(deltaTime);
		if (m_pAnimSprites[i] != 0)
			m_pAnimSprites[i]->Process(deltaTime);
	}

	// Win/lose
	if (m_pGame->outcome == Outcome::PLAYER_WINS)
	{
		m_pSprites[SPRITEN_WINMSG]->SetScale(-2.0f);
		return;
	}
	else if (m_pGame->outcome == Outcome::PLAYER_LOSES)
	{
		m_pSprites[SPRITEN_LOSEMSG]->SetScale(-2.0f);
		return;
	}

	// Cooldown times
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		m_pfStateCooldowns[i] += deltaTime seconds;
	}

	// Player Tick
	DM_Player* pPlayer = m_pGame->pPlayer;
	// win/lose conditions
	if (pPlayer->money > 1000)
		m_pGame->outcome = Outcome::PLAYER_WINS;
	if (pPlayer->health <= 0)
		m_pGame->outcome = Outcome::PLAYER_LOSES;
	// player health
	float health = pPlayer->health / 100.0f;
	Sprite* pHealth = m_pSprites[SPRITEN_HEALTHBALL];
	pHealth->SetScale(0.25f * pPlayer->health / 100.0f);
	// player cash
	Sprite* pCash = m_pSprites[SPRITEN_MONEYBALL];
	pCash->SetScale(0.25f * pPlayer->money / 1000.0f);
	// player action results
	m_pAnimSprites[SPRITEN_EXPLOSION]->SetScale(0);
	m_pAnimSprites[SPRITEN_GLIMMER]->SetScale(0);
	switch (pPlayer->latestAction)
	{
	case LatestAction::BOMB:
		m_pAnimSprites[SPRITEN_EXPLOSION]->SetScale(SCALE);
		m_pAnimSprites[SPRITEN_EXPLOSION]->SetX(WORLD_START_X + pPlayer->xTile * SCALE * TILE_SIZE_PX);
		m_pAnimSprites[SPRITEN_EXPLOSION]->SetY(WORLD_START_Y + pPlayer->yTile * SCALE * TILE_SIZE_PX);
		break;
	case LatestAction::COLLECTED:
		m_pAnimSprites[SPRITEN_GLIMMER]->SetScale(SCALE);
		m_pAnimSprites[SPRITEN_GLIMMER]->SetX(WORLD_START_X + pPlayer->xTile * SCALE * TILE_SIZE_PX);
		m_pAnimSprites[SPRITEN_GLIMMER]->SetY(WORLD_START_Y + pPlayer->yTile * SCALE * TILE_SIZE_PX);
		break;
	default: break;
	}
	// ensure bounds
	int width = m_pGame->pWorld->width;
	int height = m_pGame->pWorld->height;
	if (pPlayer->xTile < 0.0f)
		pPlayer->xTile = 0.0f;
	if (pPlayer->xTile > width - 1)
		pPlayer->xTile = width - 1;
	if (pPlayer->yTile < 0.0f)
		pPlayer->yTile = 0.0f;
	if (pPlayer->yTile > height - 1)
		pPlayer->yTile = height - 1;
	// update pos
	m_pPlayerSprite->SetX(WORLD_START_X + pPlayer->xTile * SCALE * TILE_SIZE_PX);
	m_pPlayerSprite->SetY(WORLD_START_Y + pPlayer->yTile * SCALE * TILE_SIZE_PX);
}

void SceneMain::Draw(Renderer &renderer)
{
	DM_World* pWorld = m_pGame->pWorld;

	// draw tile sprites
	for (int i = 0; i < pWorld->sizeA; ++i)
		for (int j = 0; j < pWorld->sizeB; ++j)
			for (int k = 0; k < pWorld->sizeC; ++k)
			{
				if (pWorld->pTiles[i][j][k] == NULL) continue;

				AnimatedSprite* pSprite = m_pTileSprites[i][j][k];
				pSprite->Draw(renderer);
			}
	// then draw regular sprites (i.e. player and HUD) over animated ones (tiles
	for (int i = 0; i < NSPRITES; i++)
	{
		if (m_pSprites[i] != 0)
			m_pSprites[i]->Draw(renderer);
		if (m_pAnimSprites[i] != 0)
			m_pAnimSprites[i]->Draw(renderer);
	}
	m_pPlayerSprite->Draw(renderer);
}

void SceneMain::ProcessInput(const Uint8* state) {
	DM_Player* pPlayer = m_pGame->pPlayer;
	DM_World* pWorld = m_pGame->pWorld;
	if (state[SDL_SCANCODE_W]) pPlayer->move(0, -0.1f); // Move up
	if (state[SDL_SCANCODE_A]) pPlayer->move(-0.1f, 0); // Move left
	if (state[SDL_SCANCODE_S]) pPlayer->move(0, +0.1f); // Move down
	if (state[SDL_SCANCODE_D]) pPlayer->move(+0.1f, 0); // Move right
	if (state[SDL_SCANCODE_X]) // Mine down
	{
		if (m_pfStateCooldowns[SDL_SCANCODE_X] > 1.0f seconds)
		{
			pPlayer->mineBelow(pWorld);
			m_pfStateCooldowns[SDL_SCANCODE_X] = 0 seconds;
		}
		
	}
}

void SceneMain::createWorldTileSprites() {
	DM_World* pWorld = m_pGame->pWorld;
	DM_Tile**** pTiles = pWorld->pTiles;

	// mem allocation for tile sprites
	m_pTileSprites = new AnimatedSprite***[pWorld->sizeA];
	for (int i = 0; i < pWorld->sizeA; ++i)
	{
		m_pTileSprites[i] = new AnimatedSprite**[pWorld->sizeB];
		for (int j = 0; j < pWorld->sizeB; ++j)
		{
			m_pTileSprites[i][j] = new AnimatedSprite*[pWorld->sizeC];
		}
	}

	bool loop = true;
	int n = 0;
	for (int i = 0; loop && i < pWorld->sizeA; i++)
		for (int j = 0; loop && j < pWorld->sizeB; j++)
			for (int k = 0; loop && k < pWorld->sizeC; k++)
			{
				DM_Tile *pTile = pTiles[i][j][k];
				if (pTile == NULL)
					break;

				const char* filename;
				float tintR = 1;
				float tintG = 1;
				float tintB = 1;
				switch (pTile->type)
				{
				case DM_TileType::STONE:
					filename = SPRITE_PATH "tile_stone.png";
					tintR = tintG = tintB = 1 - (pWorld->sizeC - k) / 10.0f;
					break;
				case DM_TileType::DIAMOND:
					filename = SPRITE_PATH "tile_diamond.png";
					tintR = tintG = 1 - pTile->reward / 1000.0f / 2;
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
				AnimatedSprite* sprite = m_pRenderer->CreateAnimatedSprite(filename);
				sprite->SetX(WORLD_START_X + SCALE * TILE_SIZE_PX * j);
				sprite->SetY(WORLD_START_Y + SCALE * TILE_SIZE_PX * i);
				sprite->SetScale(SCALE);
#ifdef _DEBUG
				sprite->SetScale(SCALE * (1 - k / 50.0f)); // makes outline
#endif
				sprite->SetAlpha(0.98f);
				sprite->SetRedTint(tintR);
				sprite->SetGreenTint(tintG);
				sprite->SetBlueTint(tintB);
				m_pTileSprites[i][j][k] = sprite;
				n++;
			}
}
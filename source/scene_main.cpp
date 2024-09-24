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
#include "DM_Player.h"
#include "DM_Enemy.h"

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
#define SPRITEN_RESTARTMSG 12
#define SPRITEN_CONTROLS 15
// animated sprites:
#define SPRITEN_EXPLOSION 0
#define SPRITEN_GLIMMER 1

#define SETSCREENX(val) SetX((int)(WORLD_START_X + val * SCALE * TILE_SIZE_PX))
#define SETSCREENY(val) SetY((int)(WORLD_START_Y + val * SCALE * TILE_SIZE_PX))

const int SCALE = 5;
const int WORLD_START_X = 300;
const int WORLD_START_Y = 300;
#if _DEBUG
const int ENEMY_CHANCE = /* 1 in */ 100;
#else
const int ENEMY_CHANCE = /* 1 in */ 10000;
#endif

SceneMain::SceneMain(int width, int height)
	: Scene(width, height)
	, m_pSprites(NULL)
	, m_pAnimSprites(NULL)
	, m_pTileSprites(NULL)
	, m_pRenderer(NULL)
	, m_pGame(NULL)
	, m_pfStateCooldowns(NULL)
	, m_pPlayerSprite(NULL)
	, m_pEnemies(NULL)
	, m_pEnemySprites(NULL)
	, m_iNumEnemies(0)
{
	srand((int)time(0));
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
	m_pEnemies = new DM_Enemy *[NSPRITES];
	m_pEnemySprites = new Sprite *[NSPRITES];
	for (int i = 0; i < NSPRITES; i++)
	{
		m_pSprites[i] = NULL;
		m_pAnimSprites[i] = NULL;
		m_pEnemies[i] = NULL;
		m_pEnemySprites[i] = NULL;
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
	Sprite* pControls = m_pRenderer->CreateSprite(SPRITE_PATH "label_Controls.png");
	pControls->SetX(800);
	pControls->SetY(1100);
	m_pSprites[SPRITEN_CONTROLS] = pControls;
	Sprite* pRestartMsg = m_pRenderer->CreateSprite(SPRITE_PATH "label_TryAgain.png");
	pRestartMsg->SetX(800);
	pRestartMsg->SetY(1300);
	m_pSprites[SPRITEN_RESTARTMSG] = pRestartMsg;

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
		m_pSprites[SPRITEN_RESTARTMSG]->SetScale(-1.0f);
		return;
	}
	else if (m_pGame->outcome == Outcome::PLAYER_LOSES)
	{
		m_pSprites[SPRITEN_LOSEMSG]->SetScale(-2.0f);
		m_pSprites[SPRITEN_RESTARTMSG]->SetScale(-1.0f);
		return;
	}
	else
	{
		m_pSprites[SPRITEN_WINMSG]->SetScale(0.0f);
		m_pSprites[SPRITEN_LOSEMSG]->SetScale(0.0f);
		m_pSprites[SPRITEN_RESTARTMSG]->SetScale(0.0f);
	}

	// Cooldown times
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		m_pfStateCooldowns[i] += deltaTime seconds;
	}

	// Player Tick
	DM_Player* pPlayer = m_pGame->pPlayer;
	pPlayer->Tick(m_pGame);
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
		m_pAnimSprites[SPRITEN_EXPLOSION]->SETSCREENX(pPlayer->xTile);
		m_pAnimSprites[SPRITEN_EXPLOSION]->SETSCREENY(pPlayer->yTile);
		break;
	case LatestAction::COLLECTED:
		m_pAnimSprites[SPRITEN_GLIMMER]->SetScale(SCALE);
		m_pAnimSprites[SPRITEN_GLIMMER]->SETSCREENX(pPlayer->xTile);
		m_pAnimSprites[SPRITEN_GLIMMER]->SETSCREENY(pPlayer->yTile);
		break;
	default: break;
	}
	// update pos
	m_pPlayerSprite->SETSCREENX(pPlayer->xTile);
	m_pPlayerSprite->SETSCREENY(pPlayer->yTile);

	// New enemies
	if (GetRandom(1, ENEMY_CHANCE) == 10)
	{
		int width = m_pGame->pWorld->width;
		int height = m_pGame->pWorld->height;
		int xPos = GetRandom(0, width);
		int yPos = GetRandom(0, height);
		DM_Enemy* pEnemy = new DM_Enemy((float)xPos, (float)yPos);
		m_pEnemies[m_iNumEnemies] = pEnemy;
		Sprite* pEnemySprite = m_pRenderer->CreateSprite(SPRITE_PATH "player.png");
		m_pEnemySprites[m_iNumEnemies] = pEnemySprite;
		m_iNumEnemies++;
	}
	// update all enemies
	for (int i = 0; i < m_iNumEnemies; i++)
	{
		DM_Enemy *pEnemy = m_pEnemies[i];
		Sprite* pEnemySprite = m_pEnemySprites[i];

		pEnemy->Tick(m_pGame);
		pEnemySprite->SETSCREENX(pEnemy->xTile);
		pEnemySprite->SETSCREENY(pEnemy->yTile);
		pEnemySprite->Process(deltaTime);
		// check if near player
		float dx = pEnemy->xTile - pPlayer->xTile;
		float dy = pEnemy->yTile - pPlayer->yTile;
		float dist = 1.0f;
		bool isAggro = pEnemy->m_personality == DM_Personality::AGGRESSIVE;
		bool withindist = dx > -dist && dx < dist && dy > -dist && dy < dist;
		bool within2dist = dx > -dist * 2 && dx < dist * 2 && dy > -dist * 2 && dy < dist * 2;
		pEnemySprite->SetScale(withindist ? 1.0f + GetRandomPercentage() / 3.0f : 1.0f);
		if (isAggro)
		{
			if (withindist)
			{
				// change tint to bright red
				pEnemySprite->SetRedTint(1.0f);
				pEnemySprite->SetGreenTint(0.0f);
				pEnemySprite->SetBlueTint(0.0f);
				// damage player
				pPlayer->health--;
				pPlayer->money--;
			}
			else if (within2dist)
			{
				// change tint to mid red
				pEnemySprite->SetRedTint(0.8f);
				pEnemySprite->SetGreenTint(0.5f);
				pEnemySprite->SetBlueTint(0.5f);
			}
			else
			{
				// change tint to dim red
				pEnemySprite->SetRedTint(0.6f);
				pEnemySprite->SetGreenTint(0.5f);
				pEnemySprite->SetBlueTint(0.5f);
			}
		}
		else // passive
		{
			if (withindist)
			{
				// change tint to bright aqua
				pEnemySprite->SetRedTint(0.0f);
				pEnemySprite->SetGreenTint(1.0f);
				pEnemySprite->SetBlueTint(1.0f);
				// take away money
				pPlayer->money--;
			}
			else
			{
				// change tint to dim aqua
				pEnemySprite->SetRedTint(0.5f);
				pEnemySprite->SetGreenTint(0.8f);
				pEnemySprite->SetBlueTint(0.8f);
			}
		}
	}
#if _DEBUG
#else
	// glint tiles every so often
	DM_World *pWorld = m_pGame->pWorld;
	for (int i = 0; i < pWorld->sizeA; i++)
		for (int j = 0; j < pWorld->sizeB; j++)
			for (int k = 0; k < pWorld->sizeC; k++)
			{
				bool doGlint = GetRandomPercentage() < 0.01f;
				m_pTileSprites[i][j][k]->SetAlpha(doGlint ? 0.8f : 0.99f);
			}
#endif
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
		if (m_pEnemySprites[i] != 0)
			m_pEnemySprites[i]->Draw(renderer);
	}
	m_pPlayerSprite->Draw(renderer);
}

void SceneMain::ProcessInput(const Uint8* state) {
	DM_Player* pPlayer = m_pGame->pPlayer;
	DM_World* pWorld = m_pGame->pWorld;
	float mvAmt = 0.05f;
	if (state[SDL_SCANCODE_W]) pPlayer->Move(0, -mvAmt); // Move up
	if (state[SDL_SCANCODE_A]) pPlayer->Move(-mvAmt, 0); // Move left
	if (state[SDL_SCANCODE_S]) pPlayer->Move(0, mvAmt); // Move down
	if (state[SDL_SCANCODE_D]) pPlayer->Move(mvAmt, 0); // Move right
	if (state[SDL_SCANCODE_X]) // Mine down
	{
		if (m_pfStateCooldowns[SDL_SCANCODE_X] > 0.3f seconds)
		{
			pPlayer->MineBelow(pWorld);
			m_pfStateCooldowns[SDL_SCANCODE_X] = 0 seconds;
		}
	}
	// Restart on keypress
	if (state[SDL_SCANCODE_R])
	{
		Reset();
	}
}

void SceneMain::Reset()
{
	m_pGame = new DM_Game;
	createWorldTileSprites();
	m_pEnemies = new DM_Enemy*[10];
	m_iNumEnemies = 0;
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
				sprite->SETSCREENX(j);
				sprite->SETSCREENY(i);
				sprite->SetScale(SCALE);
#if _DEBUG
				sprite->SetScale(SCALE * (1 - k / 50.0f)); // makes outline
#endif
				sprite->SetRedTint(tintR);
				sprite->SetGreenTint(tintG);
				sprite->SetBlueTint(tintB);
				m_pTileSprites[i][j][k] = sprite;
				n++;
			}
}
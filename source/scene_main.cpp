// COMP710 GP Framework 2022
// This include:
#include "scene_main.h"

// Local includes:
#include "animatedsprite.h"
#include "defs.h"
#include "renderer.h"
#include "sprite.h"

const int NSPRITES = 10;

SceneMain::SceneMain(int width, int height)
	: Scene(width, height)
	, m_pSprites(0)
	, m_pAnimSprites(0)
{
}
SceneMain::~SceneMain()
{
}
bool SceneMain::Initialise(Renderer &renderer)
{
	Renderer *m_pRenderer = &renderer;

	m_background = 0xdddddd;

	m_pSprites = new Sprite*[NSPRITES];
	m_pAnimSprites = new AnimatedSprite*[NSPRITES];
	for (int i = 0; i < NSPRITES; i++)
	{
		m_pSprites[i] = 0;
		m_pAnimSprites[i] = 0;
	}

	int n;

	// Animated sprites
	n = -1;
	// bomb
	n++;
	m_pAnimSprites[n] = m_pRenderer->CreateAnimatedSprite(SPRITE_PATH "tile_bomb.png");
	m_pAnimSprites[n]->SetupFrames(16, 16); // 16x16xN spritesheet
	m_pAnimSprites[n]->Animate();
	m_pAnimSprites[n]->SetLooping(true);
	m_pAnimSprites[n]->SetFrameDuration(0.2f);
	m_pAnimSprites[n]->SetX(300);
	m_pAnimSprites[n]->SetY(300);
	m_pAnimSprites[n]->SetScale(10);
	// diamond
	n++;
	m_pAnimSprites[n] = m_pRenderer->CreateAnimatedSprite(SPRITE_PATH "tile_diamond.png");
	m_pAnimSprites[n]->SetupFrames(16, 16); // 16x16xN spritesheet
	m_pAnimSprites[n]->Animate();
	m_pAnimSprites[n]->SetLooping(true);
	m_pAnimSprites[n]->SetFrameDuration(0.2f);
	m_pAnimSprites[n]->SetX(500);
	m_pAnimSprites[n]->SetY(350);
	m_pAnimSprites[n]->SetScale(10);

	// Plain sprites
	n = -1;
	// stone
	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "tile_stone.png");
	m_pSprites[n]->SetX(300);
	m_pSprites[n]->SetY(500);
	m_pSprites[n]->SetScale(10);

	return true;
}

void SceneMain::Process(float deltaTime)
{
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

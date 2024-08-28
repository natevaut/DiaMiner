// COMP710 GP Framework 2022
// This include:
#include "scene_aut.h"

// Local includes:
#include "defs.h"
#include "renderer.h"
#include "sprite.h"
#include <random>

SceneAUT::SceneAUT(int width, int height)
	: Scene(width, height)
	, m_pSprites(0)
	, m_timeTilComplete(0)
{
}
SceneAUT::~SceneAUT()
{
}

bool
SceneAUT::Initialise(Renderer& renderer)
{
	srand((int)time(0));
	Renderer* m_pRenderer = &renderer;
	// Put game objects here
	m_pSprites = new Sprite * [5];
	m_background = 0x000000;

	m_timeTilComplete = 0;

	int n = 0;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "aut.png");
	m_pSprites[n]->SetX(m_iWidth/2);
	m_pSprites[n]->SetY(m_iHeight/2);
	m_pSprites[n]->SetScale(-2);
	n++;

	return true;
}

void
SceneAUT::Process(float deltaTime)
{
	int n = 0;
	m_pSprites[n]->Process(deltaTime);
	
}

void
SceneAUT::Draw(Renderer& renderer)
{
	int n = 0;
	m_pSprites[n]->Draw(renderer);
}

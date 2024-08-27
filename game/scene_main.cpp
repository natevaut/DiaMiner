// COMP710 GP Framework 2022
// This include:
#include "scene_main.h"

// Local includes:
#include "defs.h"
#include "renderer.h"
#include "sprite.h"

SceneMain::SceneMain(int width, int height)
	: Scene(width, height)
{
}
SceneMain::~SceneMain()
{
}
bool SceneMain::Initialise(Renderer &renderer)
{
	Renderer *m_pRenderer = &renderer;

	m_background = 0x222222;

	m_pSprites = new Sprite *[10];
	for (int i = 0; i < 10; i++)
	{
		m_pSprites[i] = 0;
	}

	int n = -1;

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(100);
	m_pSprites[n]->SetY(100);

	return true;
}

void SceneMain::Process(float deltaTime)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneMain::Draw(Renderer &renderer)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}

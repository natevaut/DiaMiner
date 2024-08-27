// COMP710 GP Framework 2022
// This include:
#include "sceneballs.h"

// Local includes:
#include "defs.h"
#include "renderer.h"
#include "sprite.h"
#include <random>

SceneBalls::SceneBalls()
{
}

SceneBalls::~SceneBalls()
{
}

bool SceneBalls::Initialise(Renderer &renderer)
{
	srand((int)time(0));
	Renderer *m_pRenderer = &renderer;
	m_background = 0xDDDDDD;
	// Put game objects here
	m_pSprites = new Sprite *[1000];
	for (int i = 0; i < 1000; i++)
	{
		m_pSprites[i] = 0;
	}

	int n = -1;

	for (int i = 0; i < 1000; i++)
	{
		n++;
		m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "ball.png");
		m_pSprites[n]->SetX(rand() % 1000);
		m_pSprites[n]->SetY(rand() % 1000);
		m_pSprites[n]->SetRedTint((rand() % 100) / 100.0f);
		m_pSprites[n]->SetGreenTint((rand() % 100) / 100.0f);
		m_pSprites[n]->SetBlueTint((rand() % 100) / 100.0f);
		m_pSprites[n]->SetScale((rand() % 5 + 5) / 100.0f);
		m_pSprites[n]->SetAngle((rand() % 360) * 1.0f);
	}

	return true;
}

void SceneBalls::Process(float deltaTime)
{
	for (int i = 0; i < 1000; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneBalls::Draw(Renderer &renderer)
{
	for (int i = 0; i < 1000; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}

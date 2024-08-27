// COMP710 GP Framework 2022
// This include:
#include "scenecheckerboards.h"

// Local includes:
#include "defs.h"
#include "renderer.h"
#include "sprite.h"

SceneCheckerboards::SceneCheckerboards()
{
}

SceneCheckerboards::~SceneCheckerboards()
{
}
bool SceneCheckerboards::Initialise(Renderer &renderer)
{
	Renderer *m_pRenderer = &renderer;

	m_pSprites = new Sprite *[10];
	for (int i = 0; i < 10; i++)
	{
		m_pSprites[i] = 0;
	}

	int n = -1;

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(200);
	m_pSprites[n]->SetY(200);

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(200);
	m_pSprites[n]->SetY(800);
	m_pSprites[n]->SetRedTint(0.0f);
	m_pSprites[n]->SetGreenTint(0.0f);
	m_pSprites[n]->SetBlueTint(1.0f);

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(500);
	m_pSprites[n]->SetY(500);
	m_pSprites[n]->SetAngle(45);
	m_pSprites[n]->SetScale(1.2f);

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(800);
	m_pSprites[n]->SetY(200);
	m_pSprites[n]->SetRedTint(1.0f);
	m_pSprites[n]->SetGreenTint(0.0f);
	m_pSprites[n]->SetBlueTint(0.0f);

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "board8x8.png");
	m_pSprites[n]->SetX(800);
	m_pSprites[n]->SetY(800);
	m_pSprites[n]->SetRedTint(0.0f);
	m_pSprites[n]->SetGreenTint(1.0f);
	m_pSprites[n]->SetBlueTint(0.0f);

	return true;
}

void SceneCheckerboards::Process(float deltaTime)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneCheckerboards::Draw(Renderer &renderer)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}

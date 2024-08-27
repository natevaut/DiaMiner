// COMP710 GP Framework 2022
// This include:
#include "sceneaut.h"

// Local includes:
#include "defs.h"
#include "renderer.h"
#include "sprite.h"
#include <random>

int TIME_TIL_COMPLETE = 50;

SceneAUT::SceneAUT()
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

	m_timeTilComplete = 0;

	int n = 0;
	m_pSprites[n] = m_pRenderer->CreateSprite(SPRITE_PATH "aut.png");
	m_pSprites[n]->SetX(WIDTH);
	m_pSprites[n]->SetY(HEIGHT);
	m_pSprites[n]->SetScale(-2);
	n++;

	return true;
}

void
SceneAUT::Process(float deltaTime)
{
	m_timeTilComplete++;
	int n = 0;
	m_pSprites[n]->Process(deltaTime);
	
}

void
SceneAUT::Draw(Renderer& renderer)
{
	int n = 0;
	m_pSprites[n]->Draw(renderer);
}

bool SceneAUT::IsComplete() {
	return m_timeTilComplete > TIME_TIL_COMPLETE;
}
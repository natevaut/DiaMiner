// COMP710 GP Framework 2022
// This include:
#include "game.h"
// Library includes:
#include "defs.h"
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "scene_main.h"
#include "scene_aut.h"

#define SCENEID_AUT 0
#define SCENEID_MAIN 1
const int NSCENES = 2;

// Static Members:
Game *Game::sm_pInstance = 0;
Game &Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}
	return (*sm_pInstance);
}
void Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pRenderer(0)
	, m_bLooping(true)
	, m_fElapsedSeconds(0)
	, m_iLastTime(0)
	, m_fExecutionTime(0)
	, m_iFrameCount(0)
	, m_iFPS(0)
#if _DEBUG
	, m_iCurrentScene(SCENEID_MAIN)
#else
	, m_iCurrentScene(SCENEID_AUT)
#endif
	, m_pScenes(0)
	, m_pSprites(0)
{
}
Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;
}
void Game::Quit()
{
	m_bLooping = false;
}

bool Game::Initialise()
{
	int bbWidth = 1080;
	int bbHeight = 720;
	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}
	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();

	// Setup scenes

	m_pScenes = new Scene *[NSCENES + 1];
	Scene **pScenes = m_pScenes;

	pScenes[SCENEID_MAIN] = new SceneMain(bbWidth, bbHeight);
	pScenes[SCENEID_MAIN]->Initialise(*m_pRenderer);

	pScenes[SCENEID_AUT] = new SceneAUT(bbWidth, bbHeight);
	pScenes[SCENEID_AUT]->Initialise(*m_pRenderer);

	for (int i = 0; i <= NSCENES; i++)
	{
		m_scenes.push_back(pScenes[i]);
	}

	return true;
}
bool Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	// Process input
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			m_bLooping = false;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	m_pScenes[SCENEID_MAIN]->ProcessInput(state);

	if (m_bLooping)
	{

		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
		}
#endif // USE_LAG

		Draw(*m_pRenderer);
	}

	return m_bLooping;
}

void Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);

	// Switch splash scene after a timeout
	float splashTimeout = 2.0f;
	if (m_iCurrentScene == SCENEID_AUT && m_fElapsedSeconds > splashTimeout)
	{
		m_iCurrentScene = SCENEID_MAIN;
	}

	m_scenes[m_iCurrentScene]->Process(deltaTime);
}
void Game::Draw(Renderer &renderer)
{
	m_iFrameCount++;

	int bgColour = m_scenes[m_iCurrentScene]->GetBackground();
	renderer.SetClearColour(bgColour);
	renderer.Clear();

	m_scenes[m_iCurrentScene]->Draw(renderer);

	renderer.Present();
}
void Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;

	float moduloElapsed = m_fElapsedSeconds;
	while (moduloElapsed > 1.0f) {
		moduloElapsed -= 1.0f;
	}

	// Frame Counter:
	if (moduloElapsed < 0.1f)
	{
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}

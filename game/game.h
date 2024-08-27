#pragma once
#include <vector>
// COMP710 GP Framework 2022
#ifndef GAME_H
#define GAME_H
// Forward declarations:
class Renderer;
class Sprite;
class Scene;
class Game
{
	// Member methods:
public:
	static Game &GetInstance();
	static void DestroyInstance();
	bool Initialise();
	bool DoGameLoop();
	void Quit();

protected:
	void Process(float deltaTime);
	void Draw(Renderer &renderer);
	void ProcessFrameCounting(float deltaTime);

private:
	Game();
	~Game();
	Game(const Game &game);
	Game &operator=(const Game &game);

public:
protected:
	std::vector<Scene *> m_scenes;
	int m_iCurrentScene;
	Scene** m_pScenes;
	Sprite **m_pSprites;
	static Game *sm_pInstance;
	Renderer *m_pRenderer;
	__int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;
#ifdef USE_LAG
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG
	bool m_bLooping;

private:
};
#endif // GAME_H

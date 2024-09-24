// Nate Evans 21144881

#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include <SDL.h>

#include "scene.h"

// Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;
class DM_Game;
class DM_Enemy;

class SceneMain : public Scene
{
	// Member methods:
public:
	SceneMain(int width, int height);
	virtual ~SceneMain();
	virtual bool Initialise(Renderer &renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer &renderer);
	virtual void ProcessInput(const Uint8*state);

protected:
	void Reset(void);
private:
	SceneMain(const SceneMain&scene);
	SceneMain&operator=(const SceneMain&scene);

	void createWorldTileSprites();

	// Member data:
public:
	DM_Game* m_pGame;
protected:
	Sprite **m_pSprites;
	AnimatedSprite** m_pAnimSprites;
	Sprite* m_pPlayerSprite;
	DM_Enemy** m_pEnemies;
	Sprite** m_pEnemySprites;
private:
	float m_fElapsedSeconds;
	float* m_pfStateCooldowns;
	Renderer* m_pRenderer;
	AnimatedSprite**** m_pTileSprites;
	int m_iNumEnemies;
};

#endif //   SCENEMAIN_H

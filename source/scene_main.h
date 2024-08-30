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
private:
	SceneMain(const SceneMain&scene);
	SceneMain&operator=(const SceneMain&scene);

	void createWorldTileSprites(Renderer* pRenderer);

	// Member data:
public:
	DM_Game* m_pGame;
protected:
	Sprite **m_pSprites;
	AnimatedSprite** m_pAnimSprites;
private:
	Renderer* m_pRenderer;
};

#endif //   SCENEMAIN_H

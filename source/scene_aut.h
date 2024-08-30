// COMP710 GP Framework 2022

#ifndef  SCENEAUT_H
#define  SCENEAUT_H 

#include <SDL.h>
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneAUT : public Scene
{
	// Member methods:
public:
	SceneAUT(int width, int height);
	virtual ~SceneAUT();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
	virtual void ProcessInput(const Uint8* state);
protected:
private:
	SceneAUT(const SceneAUT& splashscene);
	SceneAUT& operator=(const SceneAUT& splashscene);

	// Member data:
public:


private:
protected:
	Sprite** m_pSprites;
	int m_timeTilComplete;

};

#endif //   SCENEAUT_H 

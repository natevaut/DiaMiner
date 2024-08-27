#pragma once

// COMP710 GP Framework 2022

#ifndef SCENECHECKERBOARDS_H
#define SCENECHECKERBOARDS_H
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneCheckerboards : public Scene
{
	// Member methods:
public:
	SceneCheckerboards();
	virtual ~SceneCheckerboards();
	virtual bool Initialise(Renderer &renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer &renderer);

protected:
private:
	SceneCheckerboards(const SceneCheckerboards &sceneCheckerboards);
	SceneCheckerboards &operator=(const SceneCheckerboards &sceneCheckerboards);

	// Member data:
public:
private:
protected:
	Sprite **m_pSprites;
};

#endif //   SCENECHECKERBOARDS_H

#pragma once

// COMP710 GP Framework 2022

#ifndef  SCENEBALLS_H
#define   SCENEBALLS_H
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
// Class declaration:
class SceneBalls : public Scene
{
	// Member methods:
public:
	SceneBalls();
	virtual ~SceneBalls();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer& renderer);
protected:
private:
	SceneBalls(const SceneBalls& sceneballs);
	SceneBalls& operator=(const SceneBalls& sceneballs);

	// Member data:
public:


private:
protected:
	Sprite** m_pSprites;

};

#endif //   SCENEBALLS_H

// Nate Evans 21144881

#ifndef SCENEMAIN_H
#define SCENEMAIN_H
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;
// Class declaration:
class SceneMain : public Scene
{
	// Member methods:
public:
	SceneMain(int width, int height);
	virtual ~SceneMain();
	virtual bool Initialise(Renderer &renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer &renderer);

protected:
private:
	SceneMain(const SceneMain&scene);
	SceneMain&operator=(const SceneMain&scene);

	// Member data:
public:
private:
protected:
	Sprite **m_pSprites;
	AnimatedSprite** m_pAnimSprites;
};

#endif //   SCENEMAIN_H

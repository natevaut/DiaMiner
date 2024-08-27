#pragma once
// COMP710 GP Framework 2022
#ifndef SCENE_H
#define SCENE_H

// Forward declarations:
class Renderer;

// Class declaration:
class Scene
{
	// Member methods:
public:
	Scene(int width, int height);
	virtual ~Scene();

	virtual bool Initialise(Renderer &renderer) = 0;
	virtual void Process(float deltaTime) = 0;
	virtual void Draw(Renderer &renderer) = 0;

	int GetBackground() {
		return m_background;
	}

protected:
	int m_background;
	int m_iWidth;
	int m_iHeight;

private:
	Scene(const Scene &scene);
	Scene &operator=(const Scene &scene);
};
#endif //   SCENE_H

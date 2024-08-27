#pragma once
// COMP710 GP Framework 2022
#ifndef RENDERER_H
#define RENDERER_H
// Library includes:
#include <SDL.h>
#include "animatedsprite.h"

// Forward Declarations:
class TextureManager;
class Shader;
class VertexArray;
class Sprite;
struct SDL_Window;

class Renderer
{
	// Member methods:
public:
	Renderer();
	~Renderer();
	bool Initialise(bool windowed, int width = 0, int height = 0);
	void Clear();
	void Present();
	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);
	void GetClearColour(unsigned char &r, unsigned char &g, unsigned char &b);
	int GetWidth() const;
	int GetHeight() const;
	Sprite *CreateSprite(const char *pcFilename);
	void DrawSprite(Sprite &sprite);
	AnimatedSprite *CreateAnimatedSprite(const char *pcFilename);
	void DrawAnimatedSprite(AnimatedSprite &sprite, int frame);

	void CreateStaticText(const char *pText, int pointsize);

protected:
	bool InitialiseOpenGL(int screenWidth, int screenHeight);
	void SetFullscreen(bool fullscreen);
	void LogSdlError();
	bool SetupSpriteShader();

private:
	Renderer(const Renderer &renderer);
	Renderer &operator=(const Renderer &renderer);
	// Member data:
public:
protected:
	SDL_Window *m_pWindow;
	TextureManager *m_pTextureManager;
	SDL_GLContext m_glContext;
	Shader *m_pSpriteShader;
	VertexArray *m_pSpriteVertexData;
	int m_iWidth;
	int m_iHeight;
	float m_fClearRed;
	float m_fClearGreen;
	float m_fClearBlue;

private:
};
#endif // RENDERER_H

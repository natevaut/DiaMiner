// COMP710 GP Framework 2022

// This include:
#include "scene.h"

// Local includes:
#include "renderer.h"
#include "defs.h"

// Library includes:
#include <cassert>
#include <fmod.hpp>

Scene::Scene(int bbWidth, int bbHeight)
{
	m_iWidth = bbWidth;
	m_iHeight = bbHeight;
	m_background = 0x000000;
}
Scene::~Scene()
{
}

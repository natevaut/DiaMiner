// COMP710 GP Framework 2022
// Library includes:
#include <SDL.h>
#include <Windows.h>
// Local includes:
#include "sprite.h"
#include "renderer.h"
#include "game.h"
#include "logmanager.h"

void GameLoop();

int main(int argc, char *argv[])
{
	Game &gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game initialise failed!");
		return 1;
	}

	// Setup

	while (gameInstance.DoGameLoop())
	{
		GameLoop();
		Sleep(10);
	}
	Game::DestroyInstance();
	LogManager::DestroyInstance();
	return 0;
}

void GameLoop()
{
}

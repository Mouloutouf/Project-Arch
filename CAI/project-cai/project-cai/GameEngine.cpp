#include "GameEngine.h"

GameEngine::GameEngine()
{
	gameWindow = GameWindow("The Arch Project Debug");
}

GameEngine::~GameEngine()
{
}

void GameEngine::Init()
{
	UserInit();

	if (currentScene != nullptr)
	{
		currentScene->Init();
	}
}

void GameEngine::UserInit()
{
	Scene gameScene = Scene(&gameWindow, "Game Scene");
	scenes.push_back(gameScene);

	currentScene = &gameScene;
}

void GameEngine::Run(float _elapsedTime)
{
	gameWindow.window->clear();

	currentScene->Update(_elapsedTime);
	currentScene->Render(gameWindow.window);

	gameWindow.window->display();
}

GameWindow* GameEngine::GetGameWindow()
{
	return &gameWindow;
}

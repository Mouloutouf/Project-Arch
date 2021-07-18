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
}

void GameEngine::UserInit()
{
	Scene gameScene = Scene(&gameWindow, "Game Scene");
	scenes.push_back(gameScene);

	currentScene = &gameScene;

	currentScene->Init();
}

void GameEngine::Run(float _elapsedTime)
{
	gameWindow.window->clear();

	currentScene->Update(_elapsedTime);

	gameWindow.window->display();
}

GameWindow* GameEngine::GetGameWindow()
{
	return &gameWindow;
}

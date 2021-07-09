#include "GameEngine.h"

GameEngine::GameEngine()
{
	gameWindow = new GameWindow("Best Shooter Game Ever");

	game = new Game(*(gameWindow->GetWindowDimensions()));
	gameObjects = game->gameObjects;
}

GameEngine::~GameEngine()
{
	delete gameWindow;

	delete game;
}

void GameEngine::Start()
{
	for (GameObject * gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void GameEngine::Update(float elapsedTime)
{
	for (GameObject * gameObject : gameObjects)
	{
		gameObject->Update(elapsedTime);
		gameObject->Render(gameWindow->window);
	}
}

void GameEngine::Run(float elapsedTime)
{
	gameWindow->window->clear();

	Update(elapsedTime);

	gameWindow->window->display();
}

GameWindow * GameEngine::GetWindow()
{
	return gameWindow;
}

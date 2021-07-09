#include "Game.h"

Game::Game(Vector2f windowDimensions)
{
	gameContent = new Content();
}

Game::~Game()
{
	for (GameObject * gameObject : gameObjects)
	{
		delete gameObject;
	}
}

#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"

#include "GameWindow.h"
#include "Game.h"

class GameWindow;
class Game;
class GameObject;

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	void Start();

	void Run(float elapsedTime);
	void Update(float elapsedTime);

	GameWindow * GetWindow();

protected:

	GameWindow * gameWindow;

	Game * game;
	vector<GameObject *> gameObjects;

	Spawner * enemySpawner;
	Background * background;
};

#endif // !GAME_ENGINE_H

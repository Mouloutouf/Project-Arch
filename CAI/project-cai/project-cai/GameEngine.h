#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameWindow.h"
#include "Scene.h"

class GameWindow;
class Scene;

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	void Init();
	void UserInit();

	void Run(float _elapsedTime);

	GameWindow* GetGameWindow();

protected:

	GameWindow gameWindow;

	Scene* currentScene;
	vector<Scene> scenes;
};

#endif // !GAME_ENGINE_H

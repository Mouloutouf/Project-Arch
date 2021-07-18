#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameEngine.h"

enum Tag { Default };

enum Layer { Default };

class Scene
{
public:

	Scene(); Scene(GameWindow* _gameWindow, string _name = "New Scene");

	GameObject* FindGameObject(string _name);

	GameObject* CreateGameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(), GameObject* _parent = nullptr, int _layer = 0, int _tags[] = {});
	void DestroyGameObject(GameObject* _gameObject);

	void Init();
	void UserInit();

	void Update(float _elapsedTime);

	string name;

	vector<GameObject> gameObjects;

protected:

	GameWindow* gameWindow;
};

#endif // !SCENE_H

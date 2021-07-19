#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameWindow.h"

#include "GameObject.h"

#include "SpriteRenderer.h"
#include "Collider.h"

class Scene
{
public:

	Scene(); Scene(GameWindow* _gameWindow, string _name = "New Scene");

	GameObject* FindGameObject(string _name);

	GameObject* CreateGameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(), 
		GameObject* _parent = nullptr, Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
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

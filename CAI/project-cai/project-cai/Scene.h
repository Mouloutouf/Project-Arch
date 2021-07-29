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
#include "Component.h"

#include "Display.h"

#include "SpriteRenderer.h"
#include "Collider.h"
#include "Camera.h"

class Scene
{
public:

	Scene(); Scene(GameWindow* _gameWindow, string _name = "New Scene");

	GameObject* FindGameObject(string _name);

	GameObject* CreateGameObject(string _name = "New Game Object", Transform2D _transform = Transform2D(), 
		GameObject* _parent = nullptr, Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default });
	void DestroyGameObject(GameObject* _gameObject);

	GameObject* FindWithTag(Tag _tag);

	template <typename T = Component> vector<T*> FindAllComponentsOfType()
	{
		vector<T*> cList;
		for (auto go : gameObjects)
		{
			T* _c = go.GetComponent<T>();
			if (_c != nullptr)
			{
				cList.push_back(_c);
			}
		}
		return cList;
	}

	void Init();
	inline void UserInit();

	void Update(float _elapsedTime);
	void Render(RenderWindow* _window);

	string name;

	vector<GameObject> gameObjects;

protected:

	GameWindow* gameWindow;

	Display currentDisplay;
	Camera* mainCamera;
};

#endif // !SCENE_H

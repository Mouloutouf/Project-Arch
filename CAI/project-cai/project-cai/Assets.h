#pragma once

#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Scene.h"

#include "GameObject.h"
#include "Component.h"

namespace alpha
{
	namespace core
	{
		class Scene;

		class Assets
		{
		public:

			static void AddAsset(GameObject& _gameObject);
			static void DeleteAsset(string _gameObjectName);

			static GameObject* LoadAsset(string _gameObjectName);
			static GameObject* InstantiateAsset(GameObject* _gameObject, Vector2f _position = Vector2f(0, 0), float _rotation = 0, GameObject* _parent = nullptr);

			static vector<GameObject> prefabs;

			static Scene* currentScene;
		};
	}
}

#endif // !ASSETS_H

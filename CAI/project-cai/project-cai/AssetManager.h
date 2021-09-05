#pragma once

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "Alpha.h"

///\

#include "GameObject.h"
#include "Display.h"

namespace alpha
{
	namespace core
	{
		class AssetManager
		{
		public:
			static void UserInit();

			static GameObject* LoadAsset(string _gameObjectName);
			static GameObject* InstantiateAsset(const GameObject& _gameObject, Vector2f _position = Vector2f(0, 0), float _rotation = 0, GameObject* _parent = nullptr);

			static Display* currentSceneDisplay;
		};
	}
}

#endif // !ASSET_MANAGER_H

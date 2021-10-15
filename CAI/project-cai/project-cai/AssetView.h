#pragma once

#ifndef ASSET_VIEW_H
#define ASSET_VIEW_H

#include "Alpha.h"
#include "Core.h"
#include "Game.h"

#include "AssetManager.h"
#include "SceneView.h"

///\

namespace alpha
{
	namespace core
	{
		extern const string ASSETS_FOLDER;

		class SceneView;

		class AssetView
		{
		public:

			AssetView();
			~AssetView();

			static GameObject* Prefab(GameObject* _gameObject);
			static void AddAsset(GameObject* _gameObject);
			static void DeleteAsset(string _gameObjectName);

			static vector<GameObject*> prefabs;

			static void AddTexture(string _spriteName);

			static SceneView* currentScene;

		private:

			static map<GameObject*, vector<GameObject*>> prefabsChildren;
		};
	}
}

#endif // !ASSET_VIEW_H

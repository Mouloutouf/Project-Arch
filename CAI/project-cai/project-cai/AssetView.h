#pragma once

#ifndef ASSET_VIEW_H
#define ASSET_VIEW_H

#include "Alpha.h"
#include "Core.h"

#include "AssetManager.h"
#include "SceneView.h"

///\

#include "GameObject.h"
#include "Component.h"

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

			static void AddAsset(GameObject* _gameObject);
			static void DeleteAsset(string _gameObjectName);

			static vector<GameObject*> prefabs;

			static SceneView* currentScene;
		};
	}
}

#endif // !ASSET_VIEW_H

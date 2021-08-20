#include "AssetView.h"

namespace alpha
{
	namespace core
	{
		vector<GameObject*> AssetView::prefabs;
		SceneView* AssetView::currentScene;

		void AssetManager::UserInit()
		{
			string extension = ".png";
			vector<string> tileSprites = { "Tile None", "Tile Field Big", "Tile Field Small", "Tile Water", "Tile Woods Big", "Building Storage" };

			for (int i = 0; i < tileSprites.size(); i++)
			{
				GameObject tileGo = GameObject(tileSprites[i]);
				tileGo.AddComponent(new SpriteRenderer(&tileGo, ASSETS_FOLDER + tileSprites[i] + extension, 24));
				AssetView::AddAsset(tileGo);
			}
		}

		GameObject* AssetManager::InstantiateAsset(GameObject* _gameObject, Vector2f _position, float _rotation, GameObject* _parent)
		{
			for (auto& g : AssetView::prefabs)
			{
				if (g == _gameObject) {
					auto go = AssetView::currentScene->InstantiateGameObject(_gameObject);
					go->transform.localPosition = _position;
					go->transform.localRotation = _rotation;
					go->parent = _parent;

					return go;
				}
			}
			auto _g = GameObject("New Game Object");
			auto _gptr = AssetView::currentScene->InstantiateGameObject(&_g);
			return _gptr;
		}

		AssetView::AssetView()
		{
		}

		AssetView::~AssetView()
		{
			for (auto& pg : prefabs)
				delete pg;
		}

		void AssetView::AddAsset(GameObject& _gameObject)
		{
			prefabs.push_back(&_gameObject);
		}

		void AssetView::DeleteAsset(string _gameObjectName)
		{
			for (int i = 0; i < prefabs.size(); i++) {
				if (prefabs[i]->name == _gameObjectName) {
					delete prefabs[i];
					prefabs.erase(prefabs.begin() + i);
				}
			}
		}

		GameObject* AssetManager::LoadAsset(string _gameObjectName)
		{
			for (auto& pg : AssetView::prefabs) {
				if (pg->name == _gameObjectName)
					return pg;
			} return nullptr;
		}
	}
}

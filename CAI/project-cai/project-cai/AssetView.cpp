#include "AssetView.h"

namespace alpha
{
	namespace core
	{
		vector<GameObject*> AssetView::prefabs;
		SceneView* AssetView::currentScene;

		void AssetManager::UserInit()
		{
			auto tilePrefab = new GameObject("Tile");
			AssetView::AddAsset(tilePrefab);
			tilePrefab->AddComponent(new SpriteRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Tile None" + ".png", 16));
		}

		GameObject* AssetManager::InstantiateAsset(GameObject* _prefab, Vector2f _position, float _rotation, GameObject* _parent)
		{
			bool usePrefab = false;
			GameObject objectToInstantiate;

			for (auto& p : AssetView::prefabs) {
				if (p == _prefab)
				{
					objectToInstantiate = *_prefab;
					objectToInstantiate.RemoveTag(Tag::Prefab);

					usePrefab = true;

					break;
				}
			}
			if (usePrefab == false) {
				objectToInstantiate = GameObject("New Game Object");
			}

			auto go = AssetView::currentScene->InstantiateGameObject(&objectToInstantiate);

			go->transform.localPosition = _position;
			go->transform.localRotation = _rotation;
			go->SetParent(_parent);

			return go;
		}

		AssetView::AssetView()
		{
		}

		AssetView::~AssetView()
		{
			for (auto& pg : prefabs)
				delete pg;
		}

		void AssetView::AddAsset(GameObject* _gameObject)
		{
			prefabs.push_back(_gameObject);
			_gameObject->AddTag(Tag::Prefab);
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

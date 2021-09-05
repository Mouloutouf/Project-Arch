#include "AssetView.h"

namespace alpha
{
	namespace core
	{
		vector<GameObject*> AssetView::prefabs;
		SceneView* AssetView::currentScene;

		Display* AssetManager::currentSceneDisplay;

		void AssetManager::UserInit()
		{
			auto tilePrefab = new GameObject("Tile");
			AssetView::AddAsset(tilePrefab);
			tilePrefab->AddComponent(new SpriteRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Tile None" + ".png", 16));
			tilePrefab->AddComponent(new TileObject(new Tile(), tilePrefab->GetComponent<SpriteRenderer>()));
			int ch = tilePrefab->AddChild(new GameObject("Text"));
			tilePrefab->GetChild(ch)->AddComponent(new TextRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), "", Color::White, 16));

			auto buildingPrefab = new GameObject("Building");
			AssetView::AddAsset(buildingPrefab);
			buildingPrefab->AddComponent(new SpriteRenderer(buildingPrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Building Prefabs" + ".png", 16));
			buildingPrefab->AddComponent(new BuildingObject(nullptr, buildingPrefab->GetComponent<SpriteRenderer>()));
		}

		GameObject* AssetManager::InstantiateAsset(const GameObject& _gameObject, Vector2f _position, float _rotation, GameObject* _parent)
		{
			GameObject* instance = new GameObject(_gameObject);
			instance->RemoveTag(Tag::Prefab);

			auto go = AssetView::currentScene->InstantiateGameObject(instance);

			go->transform.localPosition = _position;
			go->transform.localRotation = _rotation;
			go->SetParent(_parent);

			delete instance;

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

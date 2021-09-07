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
			auto tilePrefab = AssetView::Prefab(new GameObject("Tile"));
			tilePrefab->AddComponent(new SpriteRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Tile None" + ".png", 16));
			tilePrefab->AddComponent(new TileObject(new Tile(), tilePrefab->GetComponent<SpriteRenderer>()));
			auto tileChild = tilePrefab->CreateChild(AssetView::Prefab(new GameObject("Text")));
			tileChild->AddComponent(new TextRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), "", Color::White, 16));
			AssetView::AddAsset(tilePrefab);

			auto buildingPrefab = AssetView::Prefab(new GameObject("Building"));
			buildingPrefab->AddComponent(new SpriteRenderer(buildingPrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Building Prefabs" + ".png", 16));
			buildingPrefab->AddComponent(new BuildingObject(nullptr, buildingPrefab->GetComponent<SpriteRenderer>()));
			AssetView::AddAsset(buildingPrefab);
		}

		GameObject* AssetManager::InstantiateAsset(const GameObject& _gameObject, Vector2f _position, float _rotation, GameObject* _parent)
		{
			GameObject* instance = new GameObject(_gameObject);
			instance->RemoveTag(Tag::Prefab);
			for (auto& ch : *instance->GetChildren())
				ch->RemoveTag(Tag::Prefab);

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

		GameObject* AssetView::Prefab(GameObject* _gameObject)
		{
			_gameObject->AddTag(Tag::Prefab);
			return _gameObject;
		}

		void AssetView::AddAsset(GameObject* _gameObject)
		{
			prefabs.push_back(_gameObject);
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

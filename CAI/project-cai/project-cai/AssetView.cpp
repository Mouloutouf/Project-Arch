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

			auto tileChild = AssetView::Prefab(new GameObject("Text", tilePrefab));
			tileChild->AddComponent(new TextRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), "", Color::White, 16));

			AssetView::AddAsset(tilePrefab);

			///\

			auto buildingPrefab = AssetView::Prefab(new GameObject("Building"));
			buildingPrefab->AddComponent(new SpriteRenderer(buildingPrefab, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Building Prefabs" + ".png", 16));
			buildingPrefab->AddComponent(new BuildingObject(nullptr, buildingPrefab->GetComponent<SpriteRenderer>()));

			AssetView::AddAsset(buildingPrefab);

			///\

			auto tileDisplay = AssetView::Prefab(new GameObject("Tile Display"));

			auto areaSquare = AssetView::Prefab(new GameObject("Area Square", tileDisplay));
			areaSquare->AddComponent(new SpriteRenderer(areaSquare, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Area Square" + ".png", 570));

			auto resourceIcon = AssetView::Prefab(new GameObject("Resource Icon", tileDisplay));
			resourceIcon->AddComponent(new SpriteRenderer(resourceIcon, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Water Resource Icon" + ".png", 190));
			resourceIcon->transform.localScale = Vector2f(0.3f, 0.3f);
			resourceIcon->transform.localPosition = Vector2f(0.3f, 0.3f);

			auto excavationIcon = AssetView::Prefab(new GameObject("Excavation Icon", tileDisplay));
			excavationIcon->AddComponent(new SpriteRenderer(excavationIcon, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Excavation Icon" + ".png", 400));
			excavationIcon->transform.localScale = Vector2f(0.4f, 0.4f);
			excavationIcon->transform.localPosition = Vector2f(-0.25f, 0.25f);

			AssetView::AddAsset(tileDisplay);

			///\

			auto hoveredSquare = AssetView::Prefab(new GameObject("Hovered Square"));
			hoveredSquare->AddComponent(new SpriteRenderer(hoveredSquare, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Hovered Square" + ".png", 570));

			AssetView::AddAsset(hoveredSquare);

			///\

			auto selectedSquare = AssetView::Prefab(new GameObject("Selected Square"));
			selectedSquare->AddComponent(new SpriteRenderer(selectedSquare, AssetView::currentScene->GetCurrentDisplay(), ASSETS_FOLDER + "Selected Square" + ".png", 570));

			AssetView::AddAsset(selectedSquare);
		}

		GameObject* AssetManager::InstantiateAsset(const GameObject& _gameObject, GameObject* _parent, Vector2f _position, float _rotation)
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

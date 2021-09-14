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
			auto tileSr = tilePrefab->AddComponent(new SpriteRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Tile None" + ".png", 16));
			tileSr->SetLayer(Layers::ENVIRONMENT_LAYER);
			tilePrefab->AddComponent(new TileObject(new Tile(new Biome()), tilePrefab->GetComponent<SpriteRenderer>()));

			auto tileChild = AssetView::Prefab(new GameObject("Text", tilePrefab));
			tileChild->AddComponent(new TextRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), "", Color::White, 16));

			AssetView::AddAsset(tilePrefab);

			///\

			auto buildingPrefab = AssetView::Prefab(new GameObject("Building"));
			auto buildingSr = buildingPrefab->AddComponent(new SpriteRenderer(buildingPrefab, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Building Prefabs" + ".png", 16));
			buildingSr->SetLayer(Layers::ENVIRONMENT_LAYER);
			buildingPrefab->AddComponent(new BuildingObject(nullptr, buildingPrefab->GetComponent<SpriteRenderer>()));

			AssetView::AddAsset(buildingPrefab);

			///\

			auto tileDisplay = AssetView::Prefab(new GameObject("Tile Display"));

			auto areaSquare = AssetView::Prefab(new GameObject("Area Square", tileDisplay));
			auto areaSr = areaSquare->AddComponent(new SpriteRenderer(areaSquare, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Area Square" + ".png", 570));
			areaSr->SetLayer(Layers::UI_LAYER);
			//areaSquare->SetActive(false);

			auto resourceIcon = AssetView::Prefab(new GameObject("Resource Icon", tileDisplay));
			auto resourceSr = resourceIcon->AddComponent(new SpriteRenderer(resourceIcon, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Water Resource Icon" + ".png", 190));
			resourceSr->SetLayer(Layers::UI_LAYER);
			resourceIcon->transform.localScale = Vector2f(0.3f, 0.3f);
			resourceIcon->transform.localPosition = Vector2f(0.3f, 0.3f);
			//resourceIcon->SetActive(false);

			auto excavationIcon = AssetView::Prefab(new GameObject("Excavation Icon", tileDisplay));
			auto excavationSr = excavationIcon->AddComponent(new SpriteRenderer(excavationIcon, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Excavation Icon" + ".png", 400));
			excavationSr->SetLayer(Layers::UI_LAYER);
			excavationIcon->transform.localScale = Vector2f(0.4f, 0.4f);
			excavationIcon->transform.localPosition = Vector2f(-0.25f, 0.25f);
			//excavationIcon->SetActive(false);

			AssetView::AddAsset(tileDisplay);

			///\

			auto hoveredSquare = AssetView::Prefab(new GameObject("Hovered Square"));
			auto hoveredSr = hoveredSquare->AddComponent(new SpriteRenderer(hoveredSquare, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Hovered Square" + ".png", 570));
			hoveredSr->SetLayer(Layers::UI_LAYER);

			AssetView::AddAsset(hoveredSquare);

			///\

			auto selectedSquare = AssetView::Prefab(new GameObject("Selected Square"));
			auto selectedSr = selectedSquare->AddComponent(new SpriteRenderer(selectedSquare, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Selected Square" + ".png", 570));
			selectedSr->SetLayer(Layers::UI_LAYER);

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

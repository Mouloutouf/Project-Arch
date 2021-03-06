#include "AssetView.h"

namespace alpha
{
	namespace core
	{
		map<string, Texture> AssetManager::textures;

		vector<GameObject*> AssetView::prefabs;
		map<GameObject*, vector<GameObject*>> AssetView::prefabsChildren;

		SceneView* AssetView::currentScene;

		Display* AssetManager::currentSceneDisplay;

		void AssetManager::UserInit()
		{
			//AssetView::AddTexture("Tile None");

			auto tilePrefab = AssetView::Prefab(new GameObject("Tile"));
			auto tileSr = tilePrefab->AddComponent(new SpriteRenderer(tilePrefab, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Tile None" + ".png", 16));
			tileSr->SetLayer(Layers::ENVIRONMENT_LAYER);
			tilePrefab->AddComponent(new TileObject(new Tile(), tilePrefab->GetComponent<SpriteRenderer>()));

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
			areaSr->SetLayer(Layers::DETAILS_LAYER);
			areaSr->SetActive(false);

			auto excavationIcon = AssetView::Prefab(new GameObject("Excavation Icon", tileDisplay));
			auto excavationSr = excavationIcon->AddComponent(new SpriteRenderer(excavationIcon, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Excavation Icon" + ".png", 400));
			excavationSr->SetLayer(Layers::DETAILS_LAYER);
			excavationIcon->transform->localScale = Vector2f(0.4f, 0.4f);
			excavationIcon->transform->localPosition = Vector2f(-0.25f, 0.25f);
			excavationSr->SetActive(false);

			AssetView::AddAsset(tileDisplay);

			///\

			auto invalidTile = AssetView::Prefab(new GameObject("Invalid Tile"));
			auto invalidSr = invalidTile->AddComponent(new SpriteRenderer(invalidTile, AssetView::currentScene->GetCurrentDisplay(),
				ASSETS_FOLDER + "Invalid Tile" + ".png", 570));
			invalidSr->SetLayer(Layers::DETAILS_LAYER);
			invalidSr->SetActive(false);

			AssetView::AddAsset(invalidTile);

			///\

			auto resourceIcon = AssetView::Prefab(new GameObject("Resource Icon"));
			auto resourceSr = resourceIcon->AddComponent(new SpriteRenderer(resourceIcon, AssetView::currentScene->GetCurrentDisplay(),
				ASSETS_FOLDER + "Water Resource Icon" + ".png", 190));
			resourceSr->SetLayer(Layers::DETAILS_LAYER);
			resourceIcon->transform->localScale = Vector2f(0.3f, 0.3f);
			resourceIcon->transform->localPosition = Vector2f(0.3f, 0.3f);
			resourceSr->SetActive(false);

			AssetView::AddAsset(resourceIcon);

			///\

			auto hoveredSquare = AssetView::Prefab(new GameObject("Hovered Square"));
			auto hoveredSr = hoveredSquare->AddComponent(new SpriteRenderer(hoveredSquare, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Hovered Square" + ".png", 570));
			hoveredSr->SetLayer(Layers::DETAILS_LAYER);

			AssetView::AddAsset(hoveredSquare);

			///\

			auto selectedSquare = AssetView::Prefab(new GameObject("Selected Square"));
			auto selectedSr = selectedSquare->AddComponent(new SpriteRenderer(selectedSquare, AssetView::currentScene->GetCurrentDisplay(), 
				ASSETS_FOLDER + "Selected Square" + ".png", 570));
			selectedSr->SetLayer(Layers::DETAILS_LAYER);

			AssetView::AddAsset(selectedSquare);

			///\

			auto canvasPrefab = AssetView::Prefab(new GameObject("Canvas", nullptr, new UITransform((UITransform*)nullptr)));
			auto canvas = canvasPrefab->AddComponent(new Canvas(canvasPrefab, RenderSpace::ScreenSpace, AssetView::currentScene->GetCurrentDisplay()));

			auto topBar = AssetView::Prefab(new GameObject("Top Bar", canvasPrefab, new UITransform(canvasPrefab)));
			auto topBarUI = static_cast<UITransform*>(topBar->transform);
			topBarUI->SetAnchor(0, 1, true, true);
			topBarUI->SetSize(0.0f, 780, 0.0f, 0.0f);
			auto topBarUISr = topBar->AddComponent(new UISpriteRenderer(topBar, AssetView::currentScene->GetCurrentDisplay()));
			topBarUISr->SetLayer(Layers::UI_LAYER);
			topBarUISr->SetColor(Color::Blue);
		}

		GameObject* AssetManager::InstantiateAsset(const GameObject& _gameObject, GameObject* _parent, Vector2f _position, float _rotation)
		{
			GameObject* instance = new GameObject(_gameObject);
			instance->RemoveTag(Tag::Prefab);
			for (auto& ch : *instance->GetChildren())
				ch->RemoveTag(Tag::Prefab);

			auto go = AssetView::currentScene->InstantiateGameObject(instance);

			if (_position != Vector2f(0, 0)) go->transform->localPosition = _position;
			if (_rotation != 0.0f) go->transform->localRotation = _rotation;
			go->SetParent(_parent);

			delete instance;

			return go;
		}

		AssetView::AssetView()
		{
		}

		AssetView::~AssetView()
		{
			// Delete Prefabs
			for (auto& pg : prefabs)
				delete pg;

			// Delete Prefabs Children
			for (auto& pcL : prefabsChildren) {
				for (auto& pch : pcL.second)
					delete pch;
			}
		}

		GameObject* AssetView::Prefab(GameObject* _gameObject)
		{
			_gameObject->AddTag(Tag::Prefab);
			return _gameObject;
		}

		void AssetView::AddAsset(GameObject* _gameObject)
		{
			// Add
			prefabs.push_back(_gameObject);

			// Add Children
			// V2
			prefabsChildren.insert({ _gameObject, vector<GameObject*>() });
			for (auto& ch : *_gameObject->GetChildren()) {
				prefabsChildren[_gameObject].push_back(ch);
			}
		}

		void AssetView::DeleteAsset(string _gameObjectName)
		{
			// Find the Asset with Name
			for (int i = 0; i < prefabs.size(); i++) {
				if (prefabs[i]->name == _gameObjectName)
				{
					// Delete its Children
					// V2
					auto& pchList = prefabsChildren[prefabs[i]];
					for (int i = 0; i < pchList.size(); i++)
					{
						delete pchList[i];
						pchList.erase(pchList.begin() + i);
					}

					// Delete the Asset
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

		void AssetView::AddTexture(string _spriteName)
		{
			auto t = Texture();
			t.loadFromFile(ASSETS_FOLDER + _spriteName + ".png");
			AssetManager::textures.insert({ _spriteName, t });
		}
	}
}

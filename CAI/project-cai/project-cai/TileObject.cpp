#include "TileObject.h"

namespace alpha
{
	namespace game
	{
		TileObject::TileObject()
			: tile(new Tile()), biome(tile->getBiome())
		{
			biomeDisplay = gameObject->GetComponent<SpriteRenderer>();
		}
		TileObject::TileObject(Tile* _tile, SpriteRenderer* _spriteRenderer)
			: tile(_tile), biome(tile->getBiome()), biomeDisplay(_spriteRenderer)
		{
		}

		TileObject::TileObject(const TileObject& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject)
		{
			tile = new Tile(*that.tile);
			biome = tile->getBiome();

			biomeDisplay = gameObject->GetComponent<SpriteRenderer>();
		}

		TileObject::~TileObject()
		{
			delete tile;
		}

		TileObject* TileObject::Clone(GameObject* _gameObject)
		{
			return new TileObject(*this, _gameObject);
		}

		void TileObject::Init()
		{
		}

		void TileObject::Start()
		{
		}
		void TileObject::Update(float _elapsedTime)
		{
			if (tile->hasBuilding()) {
				tile->getBuilding()->Process(_elapsedTime);
			}
		}
		void TileObject::SetupTile(int x, int y)
		{
			biome = tile->getBiome();

			string biomeSprite = Utility::GetRandomElementFromContainer(biome->sprites);
			string biomeSpritePath = ASSETS_FOLDER + biomeSprite + ".png";
			biomeDisplay->SetSprite(biomeSpritePath);

			string indexName = " (" + to_string(x) + "," + to_string(y) + ")";
			gameObject->name = biomeSprite + indexName;

			tileDisplayPrefab = AssetManager::LoadAsset("Tile Display");

			for (auto& b : biome->canExploitBiomeBuildings)
			{
				auto resourceType = b.first;
				if (biome->resourceIcons.count(resourceType))
				{
					auto tileDisplay = AssetManager::InstantiateAsset(*tileDisplayPrefab, gameObject);
					resourceIcon = tileDisplay->GetChild("Resource Icon")->GetComponent<SpriteRenderer>();
					resourceIcon->SetSprite(Utility::spritePath(biome->resourceIcons[resourceType]));

					//tileDisplay->SetActive(false);
				}
			}
		}
	}
}
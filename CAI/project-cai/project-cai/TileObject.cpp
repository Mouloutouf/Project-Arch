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
		}
		void TileObject::SetupTile(int x, int y)
		{
			biome = tile->getBiome();

			string biomeSprite = Utility::GetRandomElementFromContainer(biome->sprites);
			string biomeSpritePath = Utility::spritePath(biomeSprite);
			biomeDisplay->SetSprite(biomeSpritePath);

			string indexName = " (" + to_string(x) + "," + to_string(y) + ")";
			gameObject->name = biomeSprite + indexName;

			tileDisplayPrefab = AssetManager::LoadAsset("Tile Display");
			tileDisplay = AssetManager::InstantiateAsset(*tileDisplayPrefab, gameObject);

			excavationIcon = tileDisplay->GetChild("Excavation Icon")->GetComponent<SpriteRenderer>();
			areaSquare = tileDisplay->GetChild("Area Square")->GetComponent<SpriteRenderer>();

			for (auto& br : biome->resourcesBuildingsCanExploit)
			{
				auto resources = br.second;
				for (int i = 0; i < resources.size(); i++)
				{
					if (biome->resourceIcons.count(resources[i]))
					{
						auto resourceIconPrefab = AssetManager::LoadAsset("Resource Icon");
						auto resourceIcon = AssetManager::InstantiateAsset(*resourceIconPrefab, tileDisplay);

						resourceIconsSpriteRenderers.insert({ resources[i], resourceIcon->GetComponent<SpriteRenderer>() });
						resourceIconsSpriteRenderers[resources[i]]->SetSprite(Utility::spritePath(biome->resourceIcons[resources[i]]));
					}
				}
			}
		}
	}
}
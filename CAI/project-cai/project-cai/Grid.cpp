#include "Grid.h"

namespace alpha
{
	namespace game
	{
		Grid::Grid()
		{
		}
		Grid::Grid(int _width, int _height, bool _useRandomSeed, string _seed)
			: width(_width), height(_height), useRandomSeed(_useRandomSeed), seed(_seed)
		{
		}
		Grid::Grid(const Grid& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), width(that.width), height(that.height), useRandomSeed(that.useRandomSeed), seed(that.seed),tiles(that.tiles)
		{
		}

		Grid::~Grid()
		{
		}

		void Grid::Init()
		{
			backgroundColor = Color(1, 9, 12);

			tilePrefab = AssetManager::LoadAsset("Tile");

			biomesFillValues.insert({ BiomeType::Desert, 2.0f });
			biomesFillValues.insert({ BiomeType::Field, 2.0f });
			biomesFillValues.insert({ BiomeType::Forest, 5.0f });

			biomesFillValues.insert({ BiomeType::Sea, 2.0f });
			biomesFillValues.insert({ BiomeType::Lake, 0.0f });
			biomesFillValues.insert({ BiomeType::Mountain, 1.0f });

			if (camera != nullptr) {
				camera->display->SetBackgroundColor(backgroundColor);
			}
		}

		Grid* Grid::Clone(GameObject* _gameObject)
		{
			return new Grid(*this, _gameObject);
		}

		void Grid::Start()
		{
			CalculateBiomes();

			GenerateRandomMap();
		}

		void Grid::Update(float _elapsedTime)
		{
		}

		TileObject* Grid::GetTile(int x, int y)
		{
			if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
			return tiles[index(x, y)];
		}

		void Grid::CalculateBiomes()
		{
			float allBiomesValues = 0;
			for (auto& bv : biomesFillValues) {
				allBiomesValues += bv.second;
			}
			float valuePercentage = 100.0f / allBiomesValues;

			float previousBiomeValue = 0;
			for (auto& bv : biomesFillValues) {
				if (bv.second == 0) continue;

				auto bvCopy = bv;
				bvCopy.second = (valuePercentage * bvCopy.second) + previousBiomeValue;
				previousBiomeValue = (float)bvCopy.second;

				biomesFillPercent.insert(bvCopy);
			}
			biomesFillPercent.rbegin()->second = 100.0f;
		}

		void Grid::GenerateRandomMap()
		{
			/*if (useRandomSeed)
				seed = to_string(_TIME);
			srand((unsigned int)hash<string>()(seed));*/

			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						CreateTile(x, y, BiomeType::None);
						continue;
					}
					if (x == 1 || x == width - 2 || y == 1 || y == height - 2) {
						CreateTile(x, y, BiomeType::Sea);
						continue;
					}

					int randomPercent = dist(mt);

					for (auto& bPercent : biomesFillPercent) {
						if (randomPercent < bPercent.second)
						{
							CreateTile(x, y, bPercent.first);
							break;
						}
					}
				}
			}
		}

		void Grid::CreateTile(int x, int y, BiomeType _b)
		{
			GameObject* tGo = AssetManager::InstantiateAsset(*tilePrefab, gameObject, Vector2f((float)x, (float)y));
			TileObject* tObject = tGo->GetComponent<TileObject>();

			tObject->tile->x = x;
			tObject->tile->y = y;

			tObject->tile->biomeType = _b;
			switch (tObject->tile->biomeType) {
				case BiomeType::None: break;
				case BiomeType::Forest: tObject->tile->setBiome(new ForestBiome()); break;
				case BiomeType::Field: tObject->tile->setBiome(new FieldBiome()); break;
				case BiomeType::Desert: tObject->tile->setBiome(new DesertBiome()); break;
				case BiomeType::Mountain: tObject->tile->setBiome(new MountainBiome()); break;
				case BiomeType::Sea: tObject->tile->setBiome(new SeaBiome()); break;
				case BiomeType::Lake: tObject->tile->setBiome(new LakeBiome()); break;
				default: break;
			}

			if (_b == BiomeType::None) {
				string biomeSprite = "Tile None";
				tGo->GetComponent<SpriteRenderer>()->SetSprite(Utility::spritePath(biomeSprite));
				string indexName = " (" + to_string(x) + "," + to_string(y) + ")";
				tGo->name = biomeSprite + indexName;
			}
			else {
				tObject->SetupTile(x, y);
			}

			//if (_b != BiomeType::None) {
			//	string containedResource = to_string(tObject->tile->getBiome()->RetrieveResourceProvision(RawResourceType::HERBS));
			//	//tGo->GetChild("Text")->GetComponent<TextRenderer>()->setString(containedResource);
			//}

			tiles.push_back(tObject);
		}
	}
}

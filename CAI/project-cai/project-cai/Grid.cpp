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
			tilePrefab = AssetManager::LoadAsset("Tile");

			biomesFillValues.insert({ BiomeType::Desert, 2 });
			biomesFillValues.insert({ BiomeType::Field, 2 });
			biomesFillValues.insert({ BiomeType::Forest, 6 });

			biomesFillValues.insert({ BiomeType::Sea, 4 });
			biomesFillValues.insert({ BiomeType::Lake, 0 });
			biomesFillValues.insert({ BiomeType::Mountain, 1 });
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
			int allBiomesValues = 0;
			for (auto& bv : biomesFillValues) {
				allBiomesValues += bv.second;
			}
			float valuePercentage = (float)(100 / allBiomesValues);

			float previousBiomeValue = 0;
			for (auto& bv : biomesFillValues) {
				if (bv.second == 0) continue;

				auto bvCopy = bv;
				bvCopy.second = (int)((valuePercentage * bvCopy.second) + previousBiomeValue);
				previousBiomeValue = (float)bvCopy.second;

				biomesFillPercent.insert(bvCopy);
			}
		}

		void Grid::GenerateRandomMap()
		{
			if (useRandomSeed)
				seed = to_string(_TIME);
			srand((unsigned int)hash<string>()(seed));

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++)
				{
					if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						CreateTile(x, y, BiomeType::None);
						continue;
					}
					if (x == 1 || x == width - 2 || y == 1 || y == height - 2) {
						CreateTile(x, y, BiomeType::Sea);
						continue;
					}

					int randomPercent = rand() % 100;
					cout << randomPercent << endl;

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
			GameObject* tGo = AssetManager::InstantiateAsset(*tilePrefab, Vector2f((float)x, (float)y), 0, gameObject);
			TileObject* tObject = tGo->GetComponent<TileObject>();

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

			string biomeSprite;
			if (_b != BiomeType::None) biomeSprite = Utility::GetRandomElementFromContainer(tObject->tile->getBiome()->sprites);
			else biomeSprite = "Tile None";
			string biomeSpritePath = ASSETS_FOLDER + biomeSprite + ".png";
			tGo->GetComponent<SpriteRenderer>()->SetSprite(biomeSpritePath);

			string indexName = " (" + to_string(x) + ", " + to_string(y) + ")";
			tGo->name = biomeSprite + indexName;

			tGo->GetChild("Text")->GetComponent<TextRenderer>()->setString(indexName);

			tiles.push_back(tObject);
		}
	}
}

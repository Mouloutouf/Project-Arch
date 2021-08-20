#include "Grid.h"

namespace alpha
{
	namespace game
	{
		Grid::Grid()
		{
		}
		Grid::Grid(GameObject* _gameObject, int _width, int _height, bool _useRandomSeed, string _seed)
			: ScriptBehaviour(_gameObject), width(_width), height(_height), useRandomSeed(_useRandomSeed), seed(_seed)
		{
		}
		Grid::Grid(const Grid& that)
			: ScriptBehaviour(that), width(that.width), height(that.height), useRandomSeed(that.useRandomSeed), seed(that.seed)
		{
			int size = that.width * that.height;
			tiles = new Tile[size];

			for (int x = 0; x < that.width; ++x) {
				for (int y = 0; y < that.height; ++y) {
					tiles[index(x, y)] = that.tiles[index(x, y)];
				}
			}

			tileObjects = new GameObject*[size];

			for (int x = 0; x < that.width; ++x) {
				for (int y = 0; y < that.height; ++y) {
					tileObjects[index(x, y)] = that.tileObjects[index(x, y)];
				}
			}
		}

		Grid& Grid::operator=(const Grid& that)
		{
			if (this != &that)
			{
				int size = that.width * that.height;
				tiles = new Tile[size];

				for (int x = 0; x < that.width; ++x) {
					for (int y = 0; y < that.height; ++y) {
						tiles[index(x, y)] = that.tiles[index(x, y)];
					}
				}

				tileObjects = new GameObject * [size];

				for (int x = 0; x < that.width; ++x) {
					for (int y = 0; y < that.height; ++y) {
						tileObjects[index(x, y)] = that.tileObjects[index(x, y)];
					}
				}
			}
			return *this;
		}

		Grid::~Grid()
		{
			delete[] tiles;
			delete[] tileObjects;
		}

		void Grid::Init()
		{
			tilePrefabs.insert({ Biome::Water, AssetManager::LoadAsset("Tile Water") });
			tilePrefabs.insert({ Biome::Mountain, AssetManager::LoadAsset("Building Storage") });
			tilePrefabs.insert({ Biome::Desert, AssetManager::LoadAsset("Tile Field Small") });
			tilePrefabs.insert({ Biome::Field, AssetManager::LoadAsset("Tile Field Big") });
			tilePrefabs.insert({ Biome::Forest, AssetManager::LoadAsset("Tile Woods Big") });
			tilePrefabs.insert({ Biome::None, AssetManager::LoadAsset("Tile None") });

			int size = width * height;
			tiles = new Tile[size];

			biomesFillPower[Biome::Desert] = 2;
			biomesFillPower[Biome::Field] = 2;
			biomesFillPower[Biome::Plain] = 0;
			biomesFillPower[Biome::Forest] = 2;
			biomesFillPower[Biome::Woods] = 0;

			biomesFillPower[Biome::Water] = 4;
			biomesFillPower[Biome::Lake] = 0;
			biomesFillPower[Biome::River] = 0;
			biomesFillPower[Biome::Mountain] = 1;
			biomesFillPower[Biome::Hill] = 0;

			biomesFillPower[Biome::None] = 4; // None cannot be less than 1
		}

		void Grid::Start()
		{
			int total = 0;
			for (auto& b : biomesFillPower) {
				total += b.second;
			}
			float bit = (float)(100 / total);

			float prev = 0;
			
			for (auto& b : biomesFillPower) {
				if (b.second == 0) continue;
				auto pb = b;
				pb.second = (int)((bit * pb.second) + prev);
				prev = (float)pb.second;
				biomesFillPercent.insert(pb);
			}

			GenerateMap();
		}

		void Grid::Update(float _elapsedTime)
		{
		}

		void Grid::GenerateMap()
		{
			RandomMap();

			CreateMap();
		}
		void Grid::RandomMap()
		{
			if (useRandomSeed) {
				seed = to_string(_TIME);
			}
			srand(hash<string>()(seed));

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++)
				{
					int r = rand() % 100;
					for (auto& b : biomesFillPercent) {
						if (r < b.second) {
							tiles[index(x, y)].biome = b.first;
							break;
						}
					}
				}
			}
		}
		void Grid::CreateMap()
		{
			int size = width * height;
			tileObjects = new GameObject*[size];

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++)
				{
					// Instantiate Prefab
					Tile& t = tiles[index(x, y)];
					GameObject* tGo = AssetManager::InstantiateAsset(tilePrefabs[t.biome], Vector2f((float)x, (float)y), 0, gameObject);
					tileObjects[index(x, y)] = tGo;
				}
			}
		}
	}
}

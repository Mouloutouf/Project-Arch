#include "Grid.h"

namespace alpha
{
	namespace game
	{
		Tile::Tile(Biome _biome) 
			: biome(_biome)
		{
		}

		Grid::Grid()
		{
		}
		Grid::Grid(GameObject* _gameObject, int _width, int _height, bool _useRandomSeed, string _seed)
			: ScriptBehaviour(_gameObject), width(_width), height(_height), useRandomSeed(_useRandomSeed), seed(_seed)
		{
		}
		Grid::Grid(const Grid& that, GameObject* _gameObject)
			: ScriptBehaviour(that, _gameObject), width(that.width), height(that.height), useRandomSeed(that.useRandomSeed), seed(that.seed)
		{
			int size = that.width * that.height;

			for (int x = 0; x < that.width; ++x) {
				for (int y = 0; y < that.height; ++y) {
					tiles.push_back(that.tiles[index(x, y)]);
				}
			}

			for (int x = 0; x < that.width; ++x) {
				for (int y = 0; y < that.height; ++y) {
					tileObjects.push_back(that.tileObjects[index(x, y)]);
				}
			}
		}

		Grid& Grid::operator=(const Grid& that)
		{
			if (this != &that)
			{
				int size = that.width * that.height;

				for (int x = 0; x < that.width; ++x) {
					for (int y = 0; y < that.height; ++y) {
						tiles.push_back(that.tiles[index(x, y)]);
					}
				}

				for (int x = 0; x < that.width; ++x) {
					for (int y = 0; y < that.height; ++y) {
						tileObjects.push_back(that.tileObjects[index(x, y)]);
					}
				}
			}
			return *this;
		}

		Grid::~Grid()
		{
			for (auto& tgo : tileObjects)
				delete tgo;
		}

		void Grid::Init()
		{
			tilePrefab = AssetManager::LoadAsset("Tile");

			tileSprites.insert({ Biome::Water, vector<string>({"Tile Sea 1", "Tile Sea 2", "Tile Sea 3"})});
			tileSprites.insert({ Biome::Mountain, vector<string>({"Tile Mountain 1", "Tile Mountain 2", "Tile Mountain 3"}) });
			tileSprites.insert({ Biome::Desert, vector<string>({"Tile Desert 1", "Tile Desert 2", "Tile Desert 3"}) });
			tileSprites.insert({ Biome::Field, vector<string>({"Tile Field 1", "Tile Field 2", "Tile Field 3", "Tile Field 4"})});
			tileSprites.insert({ Biome::Forest, vector<string>({"Tile Forest 1 AA", "Tile Forest 2 AA", "Tile Forest 3 AA", "Tile Forest 4 AA"}) });
			tileSprites.insert({ Biome::None, vector<string>({"Tile None"}) });

			int size = width * height;
			for (int i = 0; i < size; i++) {
				tiles.push_back(Tile(Biome::None));
			}

			biomesFillPower[Biome::Desert] = 2;
			biomesFillPower[Biome::Field] = 2;
			biomesFillPower[Biome::Forest] = 4;

			biomesFillPower[Biome::Water] = 4;
			biomesFillPower[Biome::Lake] = 0;
			biomesFillPower[Biome::Mountain] = 1;

			biomesFillPower[Biome::None] = 2; // None cannot be less than 1
		}

		Grid* Grid::Clone(GameObject* _gameObject)
		{
			return new Grid(*this, _gameObject);
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

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++)
				{
					// Instantiate Prefab
					Tile& t = tiles[index(x, y)];
					GameObject* tGo = AssetManager::InstantiateAsset(tilePrefab, Vector2f((float)x, (float)y), 0, gameObject);

					auto tileStr = Utility::GetRandomElementFromContainer(tileSprites[t.biome]);
					string tileSpriteStr = ASSETS_FOLDER + tileStr + ".png";
					tGo->GetComponent<SpriteRenderer>()->SetSprite(tileSpriteStr);

					tGo->name = tileStr + "(" + to_string(index(x, y)) + ")";

					tileObjects.push_back(tGo);
				}
			}
		}
	}
}

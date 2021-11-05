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

			randomTerritoryPercent = 70; // Amount of Sea (Territory)
			randomIslandPercent = 70; // Amount of Land (Island)

			biomesFillValues.insert({ BiomeType::Desert, 2.5f });
			biomesFillValues.insert({ BiomeType::Field, 2.5f });
			biomesFillValues.insert({ BiomeType::Forest, 4.0f });
			biomesFillValues.insert({ BiomeType::Mountain, 2.0f });
			biomesFillValues.insert({ BiomeType::Lake, 2.0f });

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
			//GenerateMap();
		}

		void Grid::Update(float _elapsedTime)
		{
		}

		TileObject* Grid::GetTile(int _x, int _y)
		{
			if (_x < 0 || _x >= width || _y < 0 || _y >= height) return nullptr;
			return tiles[index(_x, _y)];
		}

		void Grid::GenerateMap()
		{
			GenerateTerritory();

			GenerateIsland();

			CalculateBiomes();

			GenerateBiomes();

			CreateMap();
		}

		void Grid::GenerateTerritory()
		{
			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						territoryTiles[{x, y}] = 0;
						continue;
					}

					int randomPercent = dist(mt);
					territoryTiles[{x, y}] = randomPercent > randomTerritoryPercent ? 0 : 1;
				}
			}

			for (int i = 0; i < 2; i++)
			{
				territoryTiles = SmoothArea(territoryTiles);
			}
		}

		void Grid::GenerateIsland()
		{
			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			preTiles = vector<BiomeType>((size_t)width * height);

			for (auto& st : territoryTiles)
			{
				int sx = st.first.first, sy = st.first.second;

				if (st.second == 0) {
					preTiles[index(sx, sy)] = BiomeType::None;
					continue;
				}
				else {
					if (GetSurroundingTiles(sx, sy, territoryTiles) < 8) {
						islandTiles[{sx, sy}] = 0;
						continue;
					}

					int randomPercent = dist(mt);

					islandTiles[{sx, sy}] = randomPercent > randomIslandPercent ? 0 : 1;
				}
			}

			for (int i = 0; i < 4; i++)
			{
				islandTiles = SmoothArea(islandTiles);
			}
		}

		map<pair<int, int>, int> Grid::SmoothArea(map<pair<int, int>, int>& _inputArea)
		{
			map<pair<int, int>, int> outputArea = _inputArea;

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (_inputArea.count({ x, y }))
					{
						int surroundingTiles = GetSurroundingTiles(x, y, _inputArea);

						if (surroundingTiles > 4) {
							outputArea[{x, y}] = 1;
						}
						else if (surroundingTiles < 4) {
							outputArea[{x, y}] = 0;
						}
					}
				}
			}

			return outputArea;

			/*for (auto& at : _inputArea)
			{
				int ax = at.first.first, ay = at.first.second;

				int surroundingTiles = GetSurroundingTiles(ax, ay, _inputArea);

				if (surroundingTiles > 4) {
					at.second = 1;
				}
				else if (surroundingTiles < 4) {
					at.second = 0;
				}
			}*/
		}
		int Grid::GetSurroundingTiles(int _x, int _y, map<pair<int, int>, int>& _area)
		{
			int landCount = 0;

			for (int nx = _x - 1; nx <= _x + 1; nx++) {
				for (int ny = _y - 1; ny <= _y + 1; ny++)
				{
					if (_area.count({ nx, ny })) {
						if (nx == _x && ny == _y) continue;
						landCount += _area[{nx, ny}];
					}
				}
			}
			return landCount;
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

		void Grid::GenerateBiomes()
		{
			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			for (auto lt : islandTiles) {

				int lx = lt.first.first, ly = lt.first.second;

				if (lt.second == 0) {
					preTiles[index(lx, ly)] = BiomeType::Sea;
				}
				else {
					int randomPercent = dist(mt);

					for (auto& bPercent : biomesFillPercent) {
						if (randomPercent < bPercent.second)
						{
							preTiles[index(lx, ly)] = bPercent.first;
							break;
						}
					}
				}
			}

			for (int i = 0; i < 2; i++)
			{
				SmoothBiomes();
			}

			//CreateSeaAndLakeRegions();
		}

		void Grid::SmoothBiomes()
		{
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (preTiles[index(x, y)] != BiomeType::None && preTiles[index(x, y)] != BiomeType::Sea)
					{
						CheckBiome(x, y);
					}
				}
			}
		}
		void Grid::CheckBiome(int _x, int _y)
		{
			map<BiomeType, float> biomesStrengths;

			for (int nx = _x - 1; nx <= _x + 1; nx++) {
				for (int ny = _y - 1; ny <= _y + 1; ny++)
				{
					if (nx >= 0 && nx < width && ny >= 0 && ny < height)
					{
						if (preTiles[index(nx, ny)] == BiomeType::None || preTiles[index(nx, ny)] == BiomeType::Sea)
							continue;

						if (nx == _x && ny == _y) {
							biomesStrengths[preTiles[index(nx, ny)]] += 2.0f;
						}
						biomesStrengths[preTiles[index(nx, ny)]] += 1.0f;
					}
				}
			}

			for (auto& strength : biomesStrengths) {
				if (strength.second > biomesStrengths[preTiles[index(_x, _y)]]) {
					preTiles[index(_x, _y)] = strength.first;
				}
			}
		}

		void Grid::CreateSeaAndLakeRegions()
		{
			map<pair<int, int>, int> labels;

			map<int, int> equivalencies;

			int nextLabel = 1;

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					auto tileBiome = preTiles[index(x, y)];
					if (tileBiome != BiomeType::Sea && tileBiome != BiomeType::Lake) {
						labels.insert({ {x, y}, 0 });
					}
					else {
						auto leftTileBiome = preTiles[index(x - 1, y)];
						auto aboveTileBiome = preTiles[index(x, y - 1)];

						int leftLabel = labels[{x - 1, y}];
						int aboveLabel = labels[{x, y - 1}];

						if (leftTileBiome == BiomeType::Sea || leftTileBiome == BiomeType::Lake) {
							labels.insert({ {x, y}, leftLabel });

							if (aboveTileBiome == BiomeType::Sea || aboveTileBiome == BiomeType::Lake) {
								if (leftLabel != aboveLabel)
								{
									if (leftLabel > aboveLabel) {
										labels[{x, y}] = aboveLabel;
										equivalencies[leftLabel] = aboveLabel;
									}
									else {
										labels[{x, y}] = leftLabel;
										equivalencies[aboveLabel] = leftLabel;
									}
								}
							}
						}
						else if (aboveTileBiome == BiomeType::Sea || aboveTileBiome == BiomeType::Lake) {
							labels.insert({ {x, y}, aboveLabel });
						}
						else {
							labels.insert({ {x, y}, nextLabel });
							equivalencies.insert({ nextLabel, nextLabel });
							nextLabel++;
						}
					}
				}
			}
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					auto& label = labels[{x, y}];
					if (label != 0) {
						while (label != equivalencies[label]) {
							label = equivalencies[label];
						}
					}
				}
			}

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					auto& label = labels[{x, y}];
					if (label == 1) {
						preTiles[index(x, y)] = BiomeType::Sea;
					}
					if (label > 1) {
						preTiles[index(x, y)] = BiomeType::Lake;
					}
				}
			}
		}

		void Grid::CreateMap()
		{
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					CreateTile(x, y, preTiles[index(x, y)]);
				}
			}
		}

		void Grid::CreateTile(int _x, int _y, BiomeType _b)
		{
			GameObject* tGo = AssetManager::InstantiateAsset(*tilePrefab, gameObject, Vector2f((float)_x, (float)_y));
			TileObject* tObject = tGo->GetComponent<TileObject>();

			tObject->tile->x = _x;
			tObject->tile->y = _y;

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
				string indexName = " (" + to_string(_x) + "," + to_string(_y) + ")";
				tGo->name = biomeSprite + indexName;
			}
			else {
				tObject->SetupTile(_x, _y);
			}

			tiles.push_back(tObject);
		}
	}
}

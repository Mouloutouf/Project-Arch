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

			randomFillPercent = 42;

			biomesFillValues.insert({ BiomeType::Desert, 2.0f });
			biomesFillValues.insert({ BiomeType::Field, 2.0f });
			biomesFillValues.insert({ BiomeType::Forest, 5.0f });
			biomesFillValues.insert({ BiomeType::Mountain, 1.0f });
			biomesFillValues.insert({ BiomeType::Lake, 0.5f });

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
			GenerateMap();
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
			//GenerateSpace();

			GenerateIsland();

			CalculateBiomes();

			GenerateBiomes();

			CreateMap();
		}

		void Grid::GenerateSpace()
		{
			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						spaceTiles[{x, y}] = 0;
						continue;
					}

					int randomPercent = dist(mt);
					spaceTiles[{x, y}] = randomPercent > randomFillPercent ? 1 : 0;
				}
			}

			for (int i = 0; i < 4; i++)
			{
				SmoothArea(spaceTiles);
			}
		}

		void Grid::GenerateIsland()
		{
			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			preTiles = vector<BiomeType>((size_t)width * height);

			for (auto& st : spaceTiles)
			{
				int sx = st.first.first, int sy = st.first.second;

				if (st.second == 0) {
					preTiles[index(sx, sy)] = BiomeType::None;
					continue;
				}
				else {
					if (GetSurroundingTiles(sx, sy, spaceTiles) < 8) {
						baseTiles[{sx, sy}] = 0;
						continue;
					}

					int randomPercent = dist(mt);

					baseTiles[{sx, sy}] = randomPercent > randomFillPercent ? 1 : 0;
				}
			}

			for (int i = 0; i < 4; i++)
			{
				SmoothArea(baseTiles);
			}
		}

		void Grid::SmoothArea(map<pair<int, int>, int> _area)
		{
			for (auto& at : _area)
			{
				int ax = at.first.first, int ay = at.first.second;
				int surroundingTiles = GetSurroundingTiles(ax, ay, _area);

				if (surroundingTiles > 4) {
					at.second = 1;
				}
				else if (surroundingTiles < 4) {
					at.second = 0;
				}
			}
		}
		int Grid::GetSurroundingTiles(int _x, int _y, map<pair<int, int>, int> _area)
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

			for (int y = 1; y < height - 1; y++) {
				for (int x = 1; x < width - 1; x++)
				{
					if (baseTiles[index(x, y)] == 0) {
						preTiles[index(x, y)] = BiomeType::Sea;
					}
					else {
						int randomPercent = dist(mt);

						for (auto& bPercent : biomesFillPercent) {
							if (randomPercent < bPercent.second)
							{
								preTiles[index(x, y)] = bPercent.first;
								break;
							}
						}
					}
				}
			}

			CreateSeaAndLakeRegions();
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

		void Grid::GenerateRandomMap()
		{
			/*if (useRandomSeed)
				seed = to_string(_TIME);
			srand((unsigned int)hash<string>()(seed));*/

			random_device rd;
			mt19937 mt(rd());

			uniform_int_distribution dist(0, 99);

			preTiles = vector<BiomeType>((size_t)width * height);

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						preTiles[index(x, y)] = BiomeType::None;
						//CreateTile(x, y, BiomeType::None);
						continue;
					}
					if (x == 1 || x == width - 2 || y == 1 || y == height - 2) {
						preTiles[index(x, y)] = BiomeType::Sea;
						seaBorderTiles.insert({ {x, y}, BiomeType::Sea });
						//CreateTile(x, y, BiomeType::Sea);
						continue;
					}

					int randomPercent = dist(mt);

					for (auto& bPercent : biomesFillPercent) {
						if (randomPercent < bPercent.second)
						{
							preTiles[index(x, y)] = bPercent.first;
							//CreateTile(x, y, bPercent.first);
							break;
						}
					}
				}
			}

			// for x passes
				// for x, y in grid
				// 
				// Calculate all tiles strengths, by checking surrounding tiles -> O8 * size or O4 * size
				// Check all tiles to determine if they need to change or not (check the strength), and if they do, check the surrounding tiles -> O8 * lesser size
				// 
				// Check Tile
					// Check surrounding tiles / Calculate strength for each, depending on their own surrounding tiles -> O64
					// If not enough tiles
						// Turn tile into strongest tile biome out of all the surrounding tiles
				// Check if Tile is Sea and is inland
					// Turn tile into lake
						// Select the right sprite depending on the surrounding tiles -> O8

			if (width >= 5 && height >= 5)
			{
				CreateSeaAndLakeRegions();

				for (int i = 0; i < 4; i++)
				{
					NaturalizeMap();
				}
			}

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++)
				{
					CreateTile(x, y, preTiles[index(x, y)]);
				}
			}
		}

		void Grid::NaturalizeMap()
		{
			for (int y = 2; y < height - 2; y++) {
				for (int x = 2; x < width - 2; x++)
				{
					TurnTileWithStrength(x, y);
				}
			}

			CreateSeaAndLakeRegions();
		}

		void Grid::SetWaterRegions()
		{
			map<pair<int, int>, BiomeType> seaRegionTiles = map<pair<int, int>, BiomeType>(seaBorderTiles);

			for (int y = 2; y < height - 2; y++) {
				for (int x = 2; x < width - 2; x++)
				{
					if (preTiles[index(x, y)] == BiomeType::Sea || preTiles[index(x, y)] == BiomeType::Lake) {
						if (preTiles[index(x - 1, y)] == BiomeType::Sea || preTiles[index(x - 1, y)] == BiomeType::Lake) {
							seaRegionTiles.insert({ { x, y }, BiomeType::Sea });
							preTiles[index(x, y)] = BiomeType::Sea;
							continue;
						}
						if (preTiles[index(x, y - 1)] == BiomeType::Sea || preTiles[index(x, y - 1)] == BiomeType::Lake) {
							seaRegionTiles.insert({ { x, y }, BiomeType::Sea });
							preTiles[index(x, y)] = BiomeType::Sea;
							continue;
						}
						if (preTiles[index(x + 1, y)] == BiomeType::Sea || preTiles[index(x + 1, y)] == BiomeType::Lake) {
							seaRegionTiles.insert({ { x, y }, BiomeType::Sea });
							preTiles[index(x, y)] = BiomeType::Sea;
							continue;
						}
						if (preTiles[index(x, y + 1)] == BiomeType::Sea || preTiles[index(x, y + 1)] == BiomeType::Lake) {
							seaRegionTiles.insert({ { x, y }, BiomeType::Sea });
							preTiles[index(x, y)] = BiomeType::Sea;
							continue;
						}
						preTiles[index(x, y)] = BiomeType::Lake;
					}
				}
			}
		}

		void Grid::TurnTileWithStrength(int _x, int _y)
		{
			map<BiomeType, float> biomesStrengths;

			for (int nx = _x - 1; nx < _x + 1; nx++) {
				for (int ny = _y - 1; ny < _y + 1; ny++)
				{
					if (nx == _x && ny == _y) {
						biomesStrengths[preTiles[index(nx, ny)]] += 2.0f;
					}
					biomesStrengths[preTiles[index(nx, ny)]] += 1.0f;
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

			for (int y = height - 2; y > 0; y--) {
				for (int x = 1; x < width - 1; x++)
				{
					auto tileBiome = preTiles[index(x, y)];
					if (tileBiome != BiomeType::Sea && tileBiome != BiomeType::Lake) {
						labels.insert({ {x, y}, 0 });
					}
					else {
						auto leftTileBiome = preTiles[index(x - 1, y)];
						auto aboveTileBiome = preTiles[index(x, y + 1)];

						int leftLabel = labels[{x - 1, y}];
						int aboveLabel = labels[{x, y + 1}];

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
			for (int y = height - 2; y > 0; y--) {
				for (int x = 1; x < width - 1; x++)
				{
					auto& label = labels[{x, y}];
					if (label != 0) {
						while (label != equivalencies[label]) {
							label = equivalencies[label];
						}
					}
				}
			}

			for (int y = height - 2; y > 0; y--) {
				for (int x = 1; x < width - 1; x++)
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

#pragma once

#ifndef GRID_H
#define GRID_H

#include "Alpha.h"
#include "Core.h"

///\

#include "TileObject.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		class Grid : public ScriptBehaviour
		{
		public:

			Grid();
			Grid(int _width, int _height, bool _useRandomSeed = true, string _seed = to_string(_TIME));
			Grid(const Grid& that, GameObject* _gameObject);
			~Grid();

			Grid* Clone(GameObject* _gameObject) override;

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;

			int width = 2, height = 2;
			int index(int _x, int _y) const { return _x + width * _y; }

			TileObject* GetTile(int _x, int _y);

			GameObject* tilePrefab = nullptr;
			vector<TileObject*> tiles;

			Color backgroundColor;
			Camera* camera;

		private:

			void GenerateMap();

			void GenerateSpace();
			void GenerateIsland();
			void CalculateBiomes();
			void GenerateBiomes();
			void CreateMap();

			void SmoothArea(map<pair<int, int>, int> _area);
			int GetSurroundingTiles(int _x, int _y, map<pair<int, int>, int> _area);

			void CreateSeaAndLakeRegions();

			int randomSpacePercent;
			map<pair<int, int>, int> spaceTiles;

			int randomFillPercent;
			map<pair<int, int>, int> baseTiles;

			vector<BiomeType> preTiles;

			void GenerateRandomMap();
			void SetWaterRegions();
			void NaturalizeMap();
			void TurnTileWithStrength(int _x, int _y);
			
			map<pair<int, int>, BiomeType> seaBorderTiles;

			void CreateTile(int _x, int _y, BiomeType _b);

			map<BiomeType, float> biomesFillValues;
			map<BiomeType, float> biomesFillPercent;

			string seed;
			bool useRandomSeed = true;
		};
	}
}

#endif // !GRID_H

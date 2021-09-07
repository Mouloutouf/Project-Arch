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
			int index(int x, int y) const { return x + width * y; }

			TileObject* GetTile(int x, int y);

			GameObject* tilePrefab = nullptr;

			vector<TileObject*> tiles;

		private:

			void CalculateBiomes();

			void GenerateRandomMap();
			void CreateTile(int x, int y, BiomeType _b);

			map<BiomeType, float> biomesFillValues;
			map<BiomeType, float> biomesFillPercent;

			string seed;
			bool useRandomSeed = true;
		};
	}
}

#endif // !GRID_H

#pragma once

#ifndef GRID_H
#define GRID_H

#include <chrono>
#include "Alpha.h"

#include "ScriptBehaviour.h"

///\

namespace alpha
{
	using namespace core;

	namespace game
	{
#define _TIME chrono::system_clock::to_time_t(chrono::system_clock::now())

		enum class Biome { None, Forest, Woods, Plain, Field, Desert, Mountain, Hill, Water, Lake, River };

		struct Tile
		{
			Biome biome;
		};

		class Grid : public ScriptBehaviour
		{
		public:

			Grid();
			Grid(GameObject* _gameObject, int _width, int _height, bool _useRandomSeed = true, string _seed = to_string(_TIME));
			Grid(const Grid& that);
			Grid& operator=(const Grid& that);
			~Grid();

			void Init() override;

			void Start() override;
			void Update(float _elapsedTime) override;

			Tile* tiles;

			map<Biome, GameObject*> tilePrefabs;

			GameObject** tileObjects;

			int width, height;
			int index(int x, int y) const { return x + width * y; }

			map<Biome, int> biomesFillPower { {Biome::Desert, 0}, {Biome::Forest, 0}, {Biome::Field, 0}, {Biome::Hill, 0}, {Biome::Woods, 0},
												{Biome::Water, 0}, {Biome::Lake, 0}, {Biome::River, 0}, {Biome::Mountain, 0}, {Biome::Plain, 0},
												{Biome::None, 0}, };

		private:

			map<Biome, int> biomesFillPercent;

			string seed;
			bool useRandomSeed;

			void GenerateMap();

			void RandomMap();

			void CreateMap();
		};
	}
}

#endif // !GRID_H

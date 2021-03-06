#pragma once

#ifndef TILE_H
#define TILE_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Biomes.h"
#include "Buildings.h"

namespace alpha
{
	namespace game
	{
		class Tile
		{
		public:
			Tile();
			Tile(Biome* _biome);
			Tile(const Tile& that);
			~Tile();

			BiomeType biomeType = BiomeType::None;
			void setBiome(Biome* _biome) { if (biome != nullptr) delete biome; biome = _biome; }
			Biome* getBiome() { return biome; }

			void setBuilding(Building* _building) { if (building != nullptr) delete building; building = _building; }
			Building* getBuilding() { return building; }
			bool hasBuilding() { return building != nullptr; }

			int x, y;

		private:
			Biome* biome;
			Building* building = nullptr;
		};
	}
}

#endif // !TILE_H

#pragma once

#ifndef TILE_H
#define TILE_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Biomes.h"

namespace alpha
{
	namespace game
	{
		class Building;

		class Tile
		{
		public:
			Tile();
			Tile(Biome* _biome);
			~Tile();

			Biome* getBiome() { return biome; }
			Building* getBuilding() { return building; }

			bool hasBuilding() { return building != nullptr; }

		private:
			Biome* biome;
			Building* building = nullptr;
		};
	}
}

#endif // !TILE_H

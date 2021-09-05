#include "Tile.h"

namespace alpha
{
	namespace game
	{
		Tile::Tile()
			: biome(nullptr)
		{
		}
		Tile::Tile(Biome* _biome)
			: biome(_biome)
		{
		}

		Tile::~Tile()
		{
			if (biome != nullptr)
				delete biome;
			if (building != nullptr)
				delete building;
		}
	}
}

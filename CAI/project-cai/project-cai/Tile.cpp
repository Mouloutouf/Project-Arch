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
			: biome(_biome), biomeType(biome->biomeType)
		{
		}
		Tile::Tile(const Tile& that)
			: biomeType(that.biomeType)
		{
			biome = new Biome(*that.biome);
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

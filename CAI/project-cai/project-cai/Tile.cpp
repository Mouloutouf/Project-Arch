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
			delete biome;
			delete building;
		}
	}
}

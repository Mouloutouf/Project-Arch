#pragma once

#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Buildings.h"
#include "Tile.h"

namespace alpha
{
	namespace game
	{
		template<typename T = Building>
		class Builder
		{
		public:
			//virtual Building* Construct(Tile* _tile);
		};

		class Construction
		{
		public:
			static Building* ConstructBuilding(Tile* _tile, BuildingType _buildingType, vector<Tile*> _exploitedTiles = vector<Tile*>());
		};
	}
}

#endif // !CONSTRUCTION_H

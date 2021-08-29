#pragma once

#ifndef ENUMS_H
#define ENUMS_H

#include "Alpha.h"
#include "Core.h"

///\

namespace alpha
{
	namespace game
	{
		enum class BiomeType
		{
			None, Forest, Field, Desert, Mountain, Sea, Lake
		};

		enum class BuildingType
		{
			Farm, HuntCamp, Cookery, Shed, Storage, DroneBay, Prefabs, Pharmacy, OxygenGatherer, OxygenExcavator, WaterExtractor, WaterPurifier, ExcavationGrounds
		};
	}
}

#endif // !ENUMS_H

#include "Building.h"

namespace alpha
{
	namespace game
	{
		ArchBuilding::ArchBuilding()
		{
		}
		ArchBuilding::ArchBuilding(string _sprite, int _cstrCost, int _electrCost, int _oxygenCost, int _aoE, BiomeType _biome, BiomeType _adjacentBiome)
			: sprite(_sprite), areaOfEffect(_aoE), requiredAdjacentBiome(_adjacentBiome), requiredBiome(_biome)
		{
			constructionCosts.insert({ CoreResourceType::CONSTRUCTION, _cstrCost });
			constructionCosts.insert({ CoreResourceType::ELECTRONICS, _electrCost });
			constructionCosts.insert({ CoreResourceType::OXYGEN, _oxygenCost });
		}

		Building::Building()
		{
		}
		Building::Building(Tile* _positionTile)
			: positionTile(_positionTile)
		{
		}

		int Building::ResourceConsumption(__ResourceType _resourceType)
		{
			if (archBuilding.resourcesConsumption.count(_resourceType) == 0) return -1;
			return archBuilding.resourcesConsumption[_resourceType];
		}

		StoringBuilding::StoringBuilding()
		{
		}
		StoringBuilding::StoringBuilding(Tile* _positionTile)
			: Building(_positionTile)
		{
		}

		ProductionBuilding::ProductionBuilding()
		{
		}
		ProductionBuilding::ProductionBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: StoringBuilding(_positionTile), exploitedTiles(_exploitedTiles)
		{
		}

		int ProductionBuilding::ResourceProduction(__ResourceType _resourceType)
		{
			if (resourcesProduction.count(_resourceType) == 0) return -1;
			return resourcesProduction[_resourceType];
		}
	}
}
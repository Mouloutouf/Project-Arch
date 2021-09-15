#include "Building.h"

namespace alpha
{
	namespace game
	{
		ArchBuilding::ArchBuilding()
		{
		}
		ArchBuilding::ArchBuilding(BuildingType _buildingType, string _sprite, int _maxCrew,
			int _extraOxygen, int _extraRations,
			ebStatus _exploitedBiomeResourcesStatus, ebStatus _treesStatus,
			int _cstrCost, int _electrCost, int _oxygenCost,
			int _aoE, BiomeType _biome, __ResourceType _requiredResource)
			: buildingType(_buildingType), sprite(_sprite), maxCrewAssignees(_maxCrew), 
			exploitedBiomeResourcesStatus(_exploitedBiomeResourcesStatus), treesStatus(_treesStatus),
			areaOfEffect(_aoE), requiredBiome(_biome), requiredResource(_requiredResource)
		{
			extraResourcesConsumption.insert({ CoreResourceType::OXYGEN, _extraOxygen });
			extraResourcesConsumption.insert({ CoreResourceType::RATIONS, _extraRations });

			constructionCosts.insert({ CoreResourceType::CONSTRUCTION, _cstrCost });
			constructionCosts.insert({ CoreResourceType::ELECTRONICS, _electrCost });
			constructionCosts.insert({ CoreResourceType::OXYGEN, _oxygenCost });
		}

		Building::Building()
		{
			structureType = StructureType::Building;
		}
		Building::Building(Tile* _positionTile)
			: positionTile(_positionTile)
		{
			structureType = StructureType::Building;
		}

		void Building::SetHeldResources()
		{
			heldResources.insert({ CoreResourceType::CONSTRUCTION, archBuilding.constructionCosts[CoreResourceType::CONSTRUCTION] });
			heldResources.insert({ CoreResourceType::ELECTRONICS, archBuilding.constructionCosts[CoreResourceType::ELECTRONICS] });
		}

		int Building::ResourceConsumption(__ResourceType _resourceType)
		{
			if (archBuilding.extraResourcesConsumption.count(_resourceType) == 0) return -1;
			return archBuilding.extraResourcesConsumption[_resourceType];
		}

		StoringBuilding::StoringBuilding()
			: Building()
		{
		}
		StoringBuilding::StoringBuilding(Tile* _positionTile)
			: Building(_positionTile)
		{
		}

		ProductionBuilding::ProductionBuilding()
			: StoringBuilding()
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
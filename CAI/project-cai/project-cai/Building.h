#pragma once

#ifndef BUILDING_H
#define BUILDING_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Structure.h"
#include "Storage.h"
#include "Biomes.h"
#include "Crew.h"

namespace alpha
{
	namespace game
	{
		class Tile;

		enum class ebStatus { Preserve, Destroy };

		struct ArchBuilding
		{
			ArchBuilding();
			ArchBuilding(BuildingType _buildingType, string _sprite, int _maxCrew,
				int _extraOxygen, int _extraRations,
				ebStatus _exploitedBiomeResourcesStatus, ebStatus _treesStatus,
				int _cstrCost, int _electrCost = 0, int _oxygenCost = 0, 
				int _aoE = 0, BiomeType _biome = BiomeType::None, __ResourceType _requiredResource = 0);

			BuildingType buildingType;

			map<__ResourceType, int> constructionCosts;

			int areaOfEffect; /// 0 means 0-tile deep, meaning only the positionTile.

			BiomeType requiredBiome;
			__ResourceType requiredResource;

			/// Add parameters to the Constructor
			map<__ResourceType, int> extraResourcesConsumption;

			ebStatus exploitedBiomeResourcesStatus;
			ebStatus treesStatus;

			int maxCrewAssignees;

			string sprite;
		};

		class Building : public Structure
		{
		public:
			Building();
			Building(Tile* _positionTile);

			void SetHeldResources();

			int ResourceConsumption(__ResourceType _resourceType);

			virtual void Process(float _elapsedTime) = 0;

			ArchBuilding archBuilding;
			BuildingType buildingType() { return archBuilding.buildingType; }

			vector<CrewMember*> assignedCrewMembers;

		protected:
			Tile* positionTile;
		};

		class StoringBuilding : public Building
		{
		public:
			StoringBuilding();
			StoringBuilding(Tile* _positionTile);

		protected:
			Storage customStorage;
		};

		class ProductionBuilding : public StoringBuilding
		{
		public:
			ProductionBuilding();
			ProductionBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles = vector<Tile*>());

			int ResourceProduction(__ResourceType _resourceType);

		protected:
			vector<Tile*> exploitedTiles;

			map<__ResourceType, int> resourcesProduction;
		};
	}
}

#endif // !BUILDING_H

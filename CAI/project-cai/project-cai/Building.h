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

		enum class BiomeElementStatus { KeepIntactAll, Destroy, KeepIntactExploited };

		struct ArchBuilding
		{
			ArchBuilding();
			ArchBuilding(string _sprite, int _cstrCost, int _electrCost = 0, int _oxygenCost = 0, int _aoE = 0, 
				BiomeType _biome = BiomeType::None, BiomeType _adjacentBiome = BiomeType::None);

			map<__ResourceType, int> constructionCosts;

			int areaOfEffect; /// 0 means 0-tile deep, meaning only the positionTile.

			BiomeType requiredAdjacentBiome;
			BiomeType requiredBiome;

			/// Add parameters to the Constructor
			map<__ResourceType, int> resourcesConsumption;

			BiomeElementStatus resourcesStatus;
			BiomeElementStatus structuresStatus;

			int maxCrewAssignees;

			string sprite;
		};

		class Building : public Structure
		{
		public:
			Building();
			Building(Tile* _positionTile);

			int ResourceConsumption(__ResourceType _resourceType);

			virtual void Process(float _elapsedTime) = 0;

			ArchBuilding archBuilding;
			BuildingType buildingType;

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

#pragma once

#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Building.h"

namespace alpha
{
	namespace game
	{
		ArchBuilding OXYGEN_GATHERER_BUILDING = ArchBuilding("", 10, 5, 5, 2, BiomeType::Forest);
		ArchBuilding OXYGEN_EXCAVATOR_BUILDING = ArchBuilding("", 40, 15, 10, 0, BiomeType::Mountain);

		ArchBuilding WATER_EXTRACTOR_BUILDING = ArchBuilding("", 15, 10, 0, 1, BiomeType::None, BiomeType::Lake);
		ArchBuilding WATER_PURIFIER_BUILDING = ArchBuilding("", 40, 20, 0, 0, BiomeType::None, BiomeType::Sea);

		ArchBuilding FARM_BUILDING = ArchBuilding("Building Farm", 20, 5, 0, 2, BiomeType::Field);
		ArchBuilding HUNT_CAMP_BUILDING = ArchBuilding("", 15, 5, 0, 1, BiomeType::Forest);
		ArchBuilding COOKERY_BUILDING = ArchBuilding("", 20, 15, 5, 0);

		ArchBuilding SHED_BUILDING = ArchBuilding("Building Shed", 10, 5, 5, 0);
		ArchBuilding STORAGE_BUILDING = ArchBuilding("Building Storage", 25, 10, 10, 0);

		ArchBuilding PREFABS_BUILDING = ArchBuilding("Building Prefabs", 15, 10, 20, 0);
		ArchBuilding PHARMACY_BUILDING = ArchBuilding("Building Pharmacy", 25, 10, 5, 0);
		ArchBuilding DRONE_BAY_BUILDING = ArchBuilding("Building Drone Bay", 40, 20, 10, 0);

		ArchBuilding EXCAVATION_GROUNDS_BUILDING = ArchBuilding("", 5, 0, 0, 0);

#pragma region Oxygen
		class OxygenGathererBuilding : public ProductionBuilding
		{
		public:
			OxygenGathererBuilding();
			OxygenGathererBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};

		class OxygenExcavatorBuilding : public ProductionBuilding
		{
		public:
			OxygenExcavatorBuilding();
			OxygenExcavatorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};
#pragma endregion


#pragma region Water
		class WaterExtractorBuilding : public ProductionBuilding
		{
		public:
			WaterExtractorBuilding();
			WaterExtractorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};

		class WaterPurifierBuilding : public ProductionBuilding
		{
		public:
			WaterPurifierBuilding();
			WaterPurifierBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};
#pragma endregion


#pragma region Food
		class FarmBuilding : public ProductionBuilding
		{
		public:
			FarmBuilding();
			FarmBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};

		class HuntCampBuilding : public ProductionBuilding
		{
		public:
			HuntCampBuilding();
			HuntCampBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);
		};

		class CookeryBuilding : public StoringBuilding
		{
		public:
			CookeryBuilding();
			CookeryBuilding(Tile* _positionTile);
		};
#pragma endregion


#pragma region Storage
		class ShedBuilding : public StoringBuilding
		{
		public:
			ShedBuilding();
			ShedBuilding(Tile* _positionTile);
		};

		class StorageBuilding : public StoringBuilding
		{
		public:
			StorageBuilding();
			StorageBuilding(Tile* _positionTile);
		};
#pragma endregion


#pragma region Crew
		class PrefabsBuilding : public Building
		{
		public:
			PrefabsBuilding();
			PrefabsBuilding(Tile* _positionTile);
		};

		class PharmacyBuilding : public StoringBuilding
		{
		public:
			PharmacyBuilding();
			PharmacyBuilding(Tile* _positionTile);
		};

		class DroneBayBuilding : public Building
		{
		public:
			DroneBayBuilding();
			DroneBayBuilding(Tile* _positionTile);
		};
#pragma endregion


#pragma region Excavation
		class ExcavationGroundsBuilding : public StoringBuilding
		{
		public:
			ExcavationGroundsBuilding();
			ExcavationGroundsBuilding(Tile* _positionTile);
		};
#pragma endregion
	}
}

#endif // !BUILDINGS_H

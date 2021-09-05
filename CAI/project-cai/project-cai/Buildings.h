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
		static ArchBuilding OXYGEN_GATHERER_BUILDING = ArchBuilding("Building Oxygen Gatherer", 10, 5, 5, 2, BiomeType::Forest);
		static ArchBuilding OXYGEN_EXCAVATOR_BUILDING = ArchBuilding("Building Oxygen Excavator", 40, 15, 10, 0, BiomeType::Mountain);
		
		static ArchBuilding WATER_EXTRACTOR_BUILDING = ArchBuilding("Building Water Extractor", 15, 10, 0, 1, BiomeType::None, BiomeType::Lake);
		static ArchBuilding WATER_PURIFIER_BUILDING = ArchBuilding("Building Water Purifier", 40, 20, 0, 0, BiomeType::None, BiomeType::Sea);
		
		static ArchBuilding FARM_BUILDING = ArchBuilding("Building Farm", 20, 5, 0, 2, BiomeType::Field);
		static ArchBuilding HUNT_CAMP_BUILDING = ArchBuilding("Building Hunt Camp", 15, 5, 0, 1, BiomeType::Forest);
		static ArchBuilding COOKERY_BUILDING = ArchBuilding("Building Cookery", 20, 15, 5, 0);
		
		static ArchBuilding SHED_BUILDING = ArchBuilding("Building Shed", 10, 5, 5, 0);
		static ArchBuilding STORAGE_BUILDING = ArchBuilding("Building Storage", 25, 10, 10, 0);
		
		static ArchBuilding PREFABS_BUILDING = ArchBuilding("Building Prefabs", 15, 10, 20, 0);
		static ArchBuilding PHARMACY_BUILDING = ArchBuilding("Building Pharmacy", 25, 10, 5, 0);
		static ArchBuilding DRONE_BAY_BUILDING = ArchBuilding("Building Drone Bay", 40, 20, 10, 0);
		
		static ArchBuilding EXCAVATION_GROUNDS_BUILDING = ArchBuilding("", 5, 0, 0, 0);
		
		static map<BuildingType, ArchBuilding> ARCH_BUILDINGS
		{
			{ BuildingType::DroneBay, DRONE_BAY_BUILDING },
			{ BuildingType::Pharmacy, PHARMACY_BUILDING },
			{ BuildingType::Prefabs, PREFABS_BUILDING },
			{ BuildingType::Shed, SHED_BUILDING },
			{ BuildingType::Storage, STORAGE_BUILDING },
			{ BuildingType::Farm, FARM_BUILDING },
			{ BuildingType::HuntCamp, HUNT_CAMP_BUILDING },
			{ BuildingType::Cookery, COOKERY_BUILDING },
			{ BuildingType::OxygenGatherer, OXYGEN_GATHERER_BUILDING },
			{ BuildingType::OxygenExcavator, OXYGEN_EXCAVATOR_BUILDING },
			{ BuildingType::WaterExtractor, WATER_EXTRACTOR_BUILDING },
			{ BuildingType::WaterPurifier, WATER_PURIFIER_BUILDING }
		};

#pragma region Oxygen
		class OxygenGathererBuilding : public ProductionBuilding
		{
		public:
			OxygenGathererBuilding();
			OxygenGathererBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};

		class OxygenExcavatorBuilding : public ProductionBuilding
		{
		public:
			OxygenExcavatorBuilding();
			OxygenExcavatorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};
#pragma endregion


#pragma region Water
		class WaterExtractorBuilding : public ProductionBuilding
		{
		public:
			WaterExtractorBuilding();
			WaterExtractorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};

		class WaterPurifierBuilding : public ProductionBuilding
		{
		public:
			WaterPurifierBuilding();
			WaterPurifierBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};
#pragma endregion


#pragma region Food
		class FarmBuilding : public ProductionBuilding
		{
		public:
			FarmBuilding();
			FarmBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};

		class HuntCampBuilding : public ProductionBuilding
		{
		public:
			HuntCampBuilding();
			HuntCampBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles);

			void Process(float _elapsedTime) override;
		};

		class CookeryBuilding : public StoringBuilding
		{
		public:
			CookeryBuilding();
			CookeryBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};
#pragma endregion


#pragma region Storage
		class ShedBuilding : public StoringBuilding
		{
		public:
			ShedBuilding();
			ShedBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};

		class StorageBuilding : public StoringBuilding
		{
		public:
			StorageBuilding();
			StorageBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};
#pragma endregion


#pragma region Crew
		class PrefabsBuilding : public Building
		{
		public:
			PrefabsBuilding();
			PrefabsBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};

		class PharmacyBuilding : public StoringBuilding
		{
		public:
			PharmacyBuilding();
			PharmacyBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};

		class DroneBayBuilding : public Building
		{
		public:
			DroneBayBuilding();
			DroneBayBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};
#pragma endregion


#pragma region Excavation
		class ExcavationGroundsBuilding : public StoringBuilding
		{
		public:
			ExcavationGroundsBuilding();
			ExcavationGroundsBuilding(Tile* _positionTile);

			void Process(float _elapsedTime) override;
		};
#pragma endregion
	}
}

#endif // !BUILDINGS_H

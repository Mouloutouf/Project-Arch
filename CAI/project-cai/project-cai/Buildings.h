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
		static ArchBuilding OXYGEN_GATHERER_BUILDING = ArchBuilding(BuildingType::OxygenGatherer, "Building Oxygen Gatherer", 2, 
			0, 10,						// Consumption
			ebStatus::Preserve, ebStatus::Preserve, // Resource Status, Trees Status
			10, 5, 5,					// Costs
			2, BiomeType::Forest, CoreResourceType::OXYGEN);	// Exploitation
		static ArchBuilding OXYGEN_EXCAVATOR_BUILDING = ArchBuilding(BuildingType::OxygenExcavator, "Building Oxygen Excavator", 2,
			0, 20,						// Consumption
			ebStatus::Preserve, ebStatus::Destroy, // Resource Status, Trees Status
			40, 15, 10, 				// Costs
			0, BiomeType::Mountain, CoreResourceType::OXYGEN);	// Exploitation
		
		static ArchBuilding WATER_EXTRACTOR_BUILDING = ArchBuilding(BuildingType::WaterExtractor, "Building Water Extractor", 2,
			10, 10,									// Consumption
			ebStatus::Destroy, ebStatus::Destroy,	// Resource Status, Trees Status
			15, 10, 0, 								// Costs
			/// WARNING   v   replace Sea with Lake /!\ /
			2, BiomeType::Sea, RawResourceType::WATER);		// Exploitation
		static ArchBuilding WATER_PURIFIER_BUILDING = ArchBuilding(BuildingType::WaterPurifier, "Building Water Purifier", 2,
			20, 20,									// Consumption
			ebStatus::Destroy, ebStatus::Destroy,	// Resource Status, Trees Status
			40, 20, 0, 								// Costs
			1, BiomeType::Sea, RawResourceType::WATER);		// Exploitation
		
		static ArchBuilding FARM_BUILDING = ArchBuilding(BuildingType::Farm, "Building Farm", 2,
			15, 0,					// Consumption
			ebStatus::Preserve, ebStatus::Destroy, // Resource Status, Trees Status
			20, 5, 0, 				// Costs
			2, BiomeType::Field, RawResourceType::CROPS);	// Exploitation
		static ArchBuilding HUNT_CAMP_BUILDING = ArchBuilding(BuildingType::HuntCamp, "Building Hunt Camp", 2,
			15, 0,					// Consumption
			ebStatus::Preserve, ebStatus::Preserve, // Resource Status, Trees Status
			15, 5, 0, 				// Costs
			1, BiomeType::Forest, RawResourceType::MEAT);	// Exploitation
		static ArchBuilding COOKERY_BUILDING = ArchBuilding(BuildingType::Cookery, "Building Cookery", 2,
			25, 0,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			20, 15, 5);		// Costs
		
		static ArchBuilding SHED_BUILDING = ArchBuilding(BuildingType::Shed, "Building Shed", 0,
			0, 0,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			10, 5, 5);		// Costs
		static ArchBuilding STORAGE_BUILDING = ArchBuilding(BuildingType::Storage, "Building Storage", 0,
			0, 0,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			25, 10, 10);	// Costs
		
		static ArchBuilding PREFABS_BUILDING = ArchBuilding(BuildingType::Prefabs, "Building Prefabs", 4,
			10, 10,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			15, 10, 20);	// Costs
		static ArchBuilding PHARMACY_BUILDING = ArchBuilding(BuildingType::Pharmacy, "Building Pharmacy", 3,
			15, 15,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			25, 10, 5);		// Costs
		static ArchBuilding DRONE_BAY_BUILDING = ArchBuilding(BuildingType::DroneBay, "Building Drone Bay", 3,
			25, 5,			// Consumption
			ebStatus::Destroy, ebStatus::Destroy, // Resource Status, Trees Status
			40, 20, 10);	// Costs
		
		static ArchBuilding EXCAVATION_GROUNDS_BUILDING = ArchBuilding(BuildingType::ExcavationGrounds, "", 4,
			40, 40,		// Consumption
			ebStatus::Preserve, ebStatus::Preserve, // Resource Status, Trees Status
			5, 0, 0);	// Costs
		
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

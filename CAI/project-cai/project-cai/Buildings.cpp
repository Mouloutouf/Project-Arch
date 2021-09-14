#include "Buildings.h"

namespace alpha
{
	namespace game
	{
#pragma region Oxygen
		OxygenGathererBuilding::OxygenGathererBuilding()
		{
			buildingType = BuildingType::OxygenGatherer;

			archBuilding = OXYGEN_GATHERER_BUILDING;
		}
		OxygenGathererBuilding::OxygenGathererBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: OxygenGathererBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void OxygenGathererBuilding::Process(float _elapsedTime)
		{
		}

		OxygenExcavatorBuilding::OxygenExcavatorBuilding()
		{
			buildingType = BuildingType::OxygenExcavator;

			archBuilding = OXYGEN_EXCAVATOR_BUILDING;
		}
		OxygenExcavatorBuilding::OxygenExcavatorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: OxygenExcavatorBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void OxygenExcavatorBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion


#pragma region Water
		WaterExtractorBuilding::WaterExtractorBuilding()
		{
			buildingType = BuildingType::WaterExtractor;

			archBuilding = WATER_EXTRACTOR_BUILDING;
		}
		WaterExtractorBuilding::WaterExtractorBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: WaterExtractorBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void WaterExtractorBuilding::Process(float _elapsedTime)
		{
		}

		WaterPurifierBuilding::WaterPurifierBuilding()
		{
			buildingType = BuildingType::WaterPurifier;

			archBuilding = WATER_PURIFIER_BUILDING;
		}
		WaterPurifierBuilding::WaterPurifierBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: WaterPurifierBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void WaterPurifierBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion


#pragma region Food
		FarmBuilding::FarmBuilding()
		{
			buildingType = BuildingType::Farm;

			archBuilding = FARM_BUILDING;
		}
		FarmBuilding::FarmBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: FarmBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void FarmBuilding::Process(float _elapsedTime)
		{
		}

		HuntCampBuilding::HuntCampBuilding()
		{
			buildingType = BuildingType::HuntCamp;

			archBuilding = HUNT_CAMP_BUILDING;
		}
		HuntCampBuilding::HuntCampBuilding(Tile* _positionTile, vector<Tile*> _exploitedTiles)
			: HuntCampBuilding()
		{
			positionTile = _positionTile;
			exploitedTiles = _exploitedTiles;
		}
		void HuntCampBuilding::Process(float _elapsedTime)
		{
		}

		CookeryBuilding::CookeryBuilding()
		{
			buildingType = BuildingType::Cookery;

			archBuilding = COOKERY_BUILDING;
		}
		CookeryBuilding::CookeryBuilding(Tile* _positionTile)
			: CookeryBuilding()
		{
			positionTile = _positionTile;
		}
		void CookeryBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion


#pragma region Storage
		ShedBuilding::ShedBuilding()
		{
			buildingType = BuildingType::Shed;

			archBuilding = SHED_BUILDING;
		}
		ShedBuilding::ShedBuilding(Tile* _positionTile)
			: ShedBuilding()
		{
			positionTile = _positionTile;
		}
		void ShedBuilding::Process(float _elapsedTime)
		{
		}

		StorageBuilding::StorageBuilding()
		{
			buildingType = BuildingType::Storage;

			archBuilding = STORAGE_BUILDING;
		}
		StorageBuilding::StorageBuilding(Tile* _positionTile)
			: StorageBuilding()
		{
			positionTile = _positionTile;
		}
		void StorageBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion


#pragma region Crew
		PrefabsBuilding::PrefabsBuilding()
		{
			buildingType = BuildingType::Prefabs;

			archBuilding = PREFABS_BUILDING;
		}
		PrefabsBuilding::PrefabsBuilding(Tile* _positionTile)
			: PrefabsBuilding()
		{
			positionTile = _positionTile;
		}
		void PrefabsBuilding::Process(float _elapsedTime)
		{
		}

		PharmacyBuilding::PharmacyBuilding()
		{
			buildingType = BuildingType::Pharmacy;

			archBuilding = PHARMACY_BUILDING;
		}
		PharmacyBuilding::PharmacyBuilding(Tile* _positionTile)
			: PharmacyBuilding()
		{
			positionTile = _positionTile;
		}
		void PharmacyBuilding::Process(float _elapsedTime)
		{
		}

		DroneBayBuilding::DroneBayBuilding()
		{
			buildingType = BuildingType::DroneBay;

			archBuilding = DRONE_BAY_BUILDING;
		}
		DroneBayBuilding::DroneBayBuilding(Tile* _positionTile)
			: DroneBayBuilding()
		{
			positionTile = _positionTile;
		}
		void DroneBayBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion


#pragma region Excavation
		ExcavationGroundsBuilding::ExcavationGroundsBuilding()
		{
			buildingType = BuildingType::ExcavationGrounds;

			archBuilding = EXCAVATION_GROUNDS_BUILDING;
		}
		ExcavationGroundsBuilding::ExcavationGroundsBuilding(Tile* _positionTile)
			: ExcavationGroundsBuilding()
		{
			positionTile = _positionTile;
		}
		void ExcavationGroundsBuilding::Process(float _elapsedTime)
		{
		}
#pragma endregion
	}
}
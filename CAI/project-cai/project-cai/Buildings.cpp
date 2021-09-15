#include "Buildings.h"

namespace alpha
{
	namespace game
	{
#pragma region Oxygen
		OxygenGathererBuilding::OxygenGathererBuilding()
			: ProductionBuilding()
		{
			archBuilding = OXYGEN_GATHERER_BUILDING;

			SetHeldResources();
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
			: ProductionBuilding()
		{
			archBuilding = OXYGEN_EXCAVATOR_BUILDING;

			SetHeldResources();
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
			: ProductionBuilding()
		{
			archBuilding = WATER_EXTRACTOR_BUILDING;

			SetHeldResources();
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
			: ProductionBuilding()
		{
			archBuilding = WATER_PURIFIER_BUILDING;

			SetHeldResources();
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
			: ProductionBuilding()
		{
			archBuilding = FARM_BUILDING;

			SetHeldResources();
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
			: ProductionBuilding()
		{
			archBuilding = HUNT_CAMP_BUILDING;

			SetHeldResources();
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
			: StoringBuilding()
		{
			archBuilding = COOKERY_BUILDING;

			SetHeldResources();
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
			: StoringBuilding()
		{
			archBuilding = SHED_BUILDING;

			SetHeldResources();
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
			: StoringBuilding()
		{
			archBuilding = STORAGE_BUILDING;

			SetHeldResources();
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
			: Building()
		{
			archBuilding = PREFABS_BUILDING;

			SetHeldResources();
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
			: StoringBuilding()
		{
			archBuilding = PHARMACY_BUILDING;

			SetHeldResources();
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
			: Building()
		{
			archBuilding = DRONE_BAY_BUILDING;

			SetHeldResources();
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
			: StoringBuilding()
		{
			archBuilding = EXCAVATION_GROUNDS_BUILDING;

			SetHeldResources();
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

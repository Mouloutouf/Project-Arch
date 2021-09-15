#include "Construction.h"

namespace alpha
{
	namespace game
	{
		Building* Construction::ConstructBuilding(Tile* _tile, BuildingType _buildingType, vector<Tile*> _exploitedTiles)
		{
			Building* b = nullptr;

			switch (_buildingType)
			{
				case BuildingType::Farm: b = new FarmBuilding(_tile, _exploitedTiles); break;
				case BuildingType::HuntCamp: b = new HuntCampBuilding(_tile, _exploitedTiles); break;
				case BuildingType::Cookery: b = new CookeryBuilding(_tile); break;

				case BuildingType::Shed: b = new ShedBuilding(_tile); break;
				case BuildingType::Storage: b = new StorageBuilding(_tile); break;

				case BuildingType::DroneBay: b = new DroneBayBuilding(_tile); break;
				case BuildingType::Prefabs: b = new PrefabsBuilding(_tile); break;
				case BuildingType::Pharmacy: b = new PharmacyBuilding(_tile); break;

				case BuildingType::OxygenGatherer: b = new OxygenGathererBuilding(_tile, _exploitedTiles); break;
				case BuildingType::OxygenExcavator: b = new OxygenExcavatorBuilding(_tile, _exploitedTiles); break;

				case BuildingType::WaterExtractor: b = new WaterExtractorBuilding(_tile, _exploitedTiles); break;
				case BuildingType::WaterPurifier: b = new WaterPurifierBuilding(_tile, _exploitedTiles); break;

				case BuildingType::ExcavationGrounds: b = new ExcavationGroundsBuilding(_tile); break;

				default: break;
			}

			_tile->setBuilding(b);

			return b;
		}
	}
}

#include "Construction.h"

namespace alpha
{
	namespace game
	{
		map<BuildingType, Builder<Building>> Construction::builders = map<BuildingType, Builder<Building>>
		{
			{ BuildingType::OxygenGatherer, OxygenGathererBuilder() },
			{ BuildingType::OxygenExcavator, OxygenExcavatorBuilder() },

			{ BuildingType::WaterExtractor, WaterExtractorBuilder() },
			{ BuildingType::WaterPurifier, WaterPurifierBuilder() },

			{ BuildingType::Farm, FarmBuilder() },
			{ BuildingType::HuntCamp, HuntCampBuilder() },
			{ BuildingType::Cookery, CookeryBuilder() },

			{ BuildingType::Shed, ShedBuilder() },
			{ BuildingType::Storage, StorageBuilder() },

			{ BuildingType::Prefabs, PrefabsBuilder() },
			{ BuildingType::Pharmacy, PharmacyBuilder() },
			{ BuildingType::DroneBay, DroneBayBuilder() },

			{ BuildingType::ExcavationGrounds, ExcavationGroundsBuilder() },
		};

		Building* Construction::ConstructBuilding(Tile* _tile, BuildingType _buildingType)
		{
			builders[_buildingType].Construct(_tile);
		}

		template<typename T>
		Building* Builder<T>::Construct(Tile* _tile)
		{
			if (_tile->hasBuilding()) return;

			auto btp = GetArchBuilding();

			for (auto& cc : btp.constructionCosts) {
				// Check for global storage to check if resources match the cost
			}
			if (btp.requiredBiome != BiomeType::None) {
				if (btp.areaOfEffect > 0) {
					// Algortihm to check surrounding tiles
				}
				else if (_tile->getBiome()->biomeType != btp.requiredBiome) return;
			}
			if (btp.requiredAdjacentBiome != BiomeType::None) {
				// Algortihm to check surrounding tiles
			}

			if (btp.resourcesStatus == BiomeElementStatus::Destroy) {
				_tile->getBiome()->DestroyResources();
			}
			if (btp.structuresStatus == BiomeElementStatus::Destroy) {
				if (_tile->getBiome()->hasStructures()) return;
			}

			auto newBuilding = new T(_tile);
			return newBuilding;
		}

		ExcavationGroundsBuilding* ExcavationGroundsBuilder::Construct(Tile* _tile)
		{
			if (_tile->getBiome()->hasStructures() || _tile->hasBuilding())
			{
				auto newBuilding = new ExcavationGroundsBuilding(_tile);
				return newBuilding;
			}
		}
	}
}

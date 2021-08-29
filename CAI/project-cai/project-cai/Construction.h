#pragma once

#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Buildings.h"

namespace alpha
{
	namespace game
	{
		template<typename T = Building>
		class Builder
		{
		public:
			virtual ArchBuilding& GetArchBuilding();
			virtual Building* Construct(Tile* _tile);
		};

		class Construction
		{
		public:
			static Building* ConstructBuilding(Tile* _tile, BuildingType _buildingType);

		private:
			static map<BuildingType, Builder<Building>> builders;
		};

#pragma region Oxygen
		class OxygenGathererBuilder : public Builder<OxygenGathererBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return OXYGEN_GATHERER_BUILDING; }
		};
		class OxygenExcavatorBuilder : public Builder<OxygenExcavatorBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return OXYGEN_EXCAVATOR_BUILDING; }
		};
#pragma endregion


#pragma region Water
		class WaterExtractorBuilder : public Builder<WaterExtractorBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return WATER_EXTRACTOR_BUILDING; }
		};
		class WaterPurifierBuilder : public Builder<WaterPurifierBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return WATER_PURIFIER_BUILDING; }
		};
#pragma endregion


#pragma region Food
		class FarmBuilder : public Builder<FarmBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return FARM_BUILDING; }
		};
		class HuntCampBuilder : public Builder<HuntCampBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return HUNT_CAMP_BUILDING; }
		};
		class CookeryBuilder : public Builder<CookeryBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return COOKERY_BUILDING; }
		};
#pragma endregion


#pragma region Storage
		class ShedBuilder : public Builder<ShedBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return SHED_BUILDING; }
		};
		class StorageBuilder : public Builder<StorageBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return STORAGE_BUILDING; }
		};
#pragma endregion


#pragma region Crew
		class PrefabsBuilder : public Builder<PrefabsBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return PREFABS_BUILDING; }
		};
		class PharmacyBuilder : public Builder<PharmacyBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return PHARMACY_BUILDING; }
		};
		class DroneBayBuilder : public Builder<DroneBayBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return DRONE_BAY_BUILDING; }
		};
#pragma endregion


#pragma region Excavation
		class ExcavationGroundsBuilder : public Builder<ExcavationGroundsBuilding>
		{
		public:
			ArchBuilding& GetArchBuilding() override { return OXYGEN_GATHERER_BUILDING; }
			ExcavationGroundsBuilding* Construct(Tile* _tile) override;
		};
#pragma endregion
	}
}

#endif // !CONSTRUCTION_H

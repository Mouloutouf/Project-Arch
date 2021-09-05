#include "Biomes.h"

namespace alpha
{
	namespace game
	{
#pragma region Field
		FieldBiome::FieldBiome()
		{
			biomeType = BiomeType::Field;

			sprites = vector<string>({ "Tile Field 1", "Tile Field 2", "Tile Field 3", "Tile Field 4" });

			allowBuild = true;
			terrain = NORMAL_TERRAIN;

			buildingsForResourceExploitation.insert({ RawResourceType::CROPS, BuildingType::Farm });
			buildingsForResourceExploitation.insert({ RawResourceType::HERBS, BuildingType::Farm });

			resourcesProvisions.insert({ RawResourceType::CROPS, Resource(RawResourceType::CROPS) });
			resourcesProvisions.insert({ RawResourceType::HERBS, Resource(RawResourceType::HERBS) });

			GenerateFieldBiome();
		}
		FieldBiome::FieldBiome(int _cropResources, int _herbResources, Structure* _shipStructure)
			: FieldBiome()
		{
			resourcesProvisions[RawResourceType::CROPS].SetQuantity(_cropResources);
			resourcesProvisions[RawResourceType::HERBS].SetQuantity(_herbResources);

			structures.push_back(_shipStructure);
		}
		void FieldBiome::GenerateFieldBiome()
		{
			GenerateResources(RawResourceType::CROPS, 40, 60);
			GenerateResources(RawResourceType::HERBS, 10, 20);

			structures.push_back(Structure::CreateShipStructure());
		}
#pragma endregion

#pragma region Desert
		DesertBiome::DesertBiome()
		{
			biomeType = BiomeType::Desert;

			sprites = vector<string>({ "Tile Desert 1", "Tile Desert 2", "Tile Desert 3" });

			allowBuild = true;
			terrain = NORMAL_TERRAIN;

			GenerateDesertBiome();
		}
		DesertBiome::DesertBiome(Structure* _shipStructure)
			: DesertBiome()
		{
			structures.push_back(_shipStructure);
		}
		void DesertBiome::GenerateDesertBiome()
		{
			structures.push_back(Structure::CreateShipStructure());
		}
#pragma endregion

#pragma region Mountain
		MountainBiome::MountainBiome()
		{
			biomeType = BiomeType::Mountain;

			sprites = vector<string>({ "Tile Mountain 1", "Tile Mountain 2", "Tile Mountain 3" });

			allowBuild = true;
			terrain = HARD_TERRAIN;

			buildingsForResourceExploitation.insert({ CoreResourceType::OXYGEN, BuildingType::OxygenExcavator });

			resourcesProvisions.insert({ CoreResourceType::OXYGEN, Resource(CoreResourceType::OXYGEN) });

			GenerateMountainBiome();
		}
		MountainBiome::MountainBiome(int _oxygenResources, Structure* _shipStructure)
			: MountainBiome()
		{
			resourcesProvisions[CoreResourceType::OXYGEN].SetQuantity(_oxygenResources);

			structures.push_back(_shipStructure);
		}
		void MountainBiome::GenerateMountainBiome()
		{
			GenerateResources(CoreResourceType::OXYGEN, 160, 280);

			structures.push_back(Structure::CreateShipStructure());
		}
#pragma endregion

#pragma region Lake
		LakeBiome::LakeBiome()
		{
			biomeType = BiomeType::Lake;

			sprites = vector<string>({ "" });

			allowBuild = false;

			buildingsForResourceExploitation.insert({ RawResourceType::WATER, BuildingType::WaterExtractor });

			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER) });

			GenerateLakeBiome();
		}
		LakeBiome::LakeBiome(int _waterResources)
			: LakeBiome()
		{
			resourcesProvisions[RawResourceType::WATER].SetQuantity(_waterResources);
		}
		void LakeBiome::GenerateLakeBiome()
		{
			GenerateResources(RawResourceType::WATER, 40, 70);
		}
#pragma endregion

#pragma region Forest
		ForestBiome::ForestBiome()
		{
			biomeType = BiomeType::Forest;

			forestSprites.insert({ "AA", vector<string>({ "Tile Forest 1 AA", "Tile Forest 2 AA", "Tile Forest 3 AA", "Tile Forest 4 AA" }) });
			forestSprites.insert({ "AD", vector<string>({ "Tile Forest 1 AD", "Tile Forest 2 AD", "Tile Forest 3 AD", "Tile Forest 4 AD" }) });
			forestSprites.insert({ "OD", vector<string>({ "Tile Forest 1 OD", "Tile Forest 2 OD", "Tile Forest 3 OD", "Tile Forest 4 OD" }) });
			forestSprites.insert({ "OO", vector<string>({ "Tile Forest 1 OO", "Tile Forest 2 OO", "Tile Forest 3 OO", "Tile Forest 4 OO" }) });

			allowBuild = true;
			terrain = NORMAL_TERRAIN;

			buildingsForResourceExploitation.insert({ CoreResourceType::OXYGEN, BuildingType::OxygenGatherer });
			buildingsForResourceExploitation.insert({ RawResourceType::MEAT, BuildingType::HuntCamp });
			buildingsForResourceExploitation.insert({ RawResourceType::HERBS, BuildingType::HuntCamp });

			resourcesProvisions.insert({ CoreResourceType::OXYGEN, Resource(CoreResourceType::OXYGEN) });
			resourcesProvisions.insert({ RawResourceType::MEAT, Resource(RawResourceType::MEAT) });
			resourcesProvisions.insert({ RawResourceType::HERBS, Resource(RawResourceType::HERBS) });

			GenerateForestBiome();
		}
		ForestBiome::ForestBiome(int _oxygenResources, int _meatResources, int _herbResources, Structure* _shipStructure)
			: ForestBiome()
		{
			resourcesProvisions[CoreResourceType::OXYGEN].SetQuantity(_oxygenResources);
			resourcesProvisions[RawResourceType::MEAT].SetQuantity(_meatResources);
			resourcesProvisions[RawResourceType::HERBS].SetQuantity(_herbResources);

			structures.push_back(_shipStructure);
			structures.push_back(Structure::CreateForestStructure());
		}
		void ForestBiome::GenerateForestBiome()
		{
			GenerateForestResources();
			sprites = vector<string>(forestSprites[forestType]);
			GenerateResources(RawResourceType::HERBS, 15, 30);

			structures.push_back(Structure::CreateShipStructure());
			structures.push_back(Structure::CreateForestStructure());
		}
		void ForestBiome::GenerateForestResources()
		{
			int minMat = 60, maxMat = 280;
			int materials = Utility::GetRandomNumberInRange(minMat, maxMat);

			int percentages[] = { 0, 25, 75, 100 };
			string types[] = { "AA", "AD", "OD", "OO"};

			int i = Utility::GetRandomNumberInRange(0, 3);

			int oxygenMat = materials * (float)(percentages[i] / 100.0f);
			int animalMat = materials * (float)((100 - percentages[i]) / 100.0f);

			resourcesProvisions[CoreResourceType::OXYGEN].SetQuantity(oxygenMat);
			resourcesProvisions[RawResourceType::MEAT].SetQuantity(animalMat);

			forestType = types[i];
		}
#pragma endregion

#pragma region Sea
		SeaBiome::SeaBiome()
		{
			biomeType = BiomeType::Sea;

			sprites = vector<string>({ "Tile Sea 1", "Tile Sea 2", "Tile Sea 3" });

			allowBuild = false;

			buildingsForResourceExploitation.insert({ RawResourceType::WATER, BuildingType::WaterPurifier });

			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER) });
		}
		SeaBiome::SeaBiome(int _waterResources)
			: SeaBiome()
		{
			resourcesProvisions[RawResourceType::WATER].SetQuantity(_waterResources);
		}
		void SeaBiome::GenerateSeaBiome()
		{
			GenerateResources(RawResourceType::WATER, 80, 120);
		}
#pragma endregion
	}
}

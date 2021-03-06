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

			resourcesBuildingsCanExploit.insert({ BuildingType::Farm, vector<__ResourceType>{ RawResourceType::CROPS, RawResourceType::HERBS } });

			resourceIcons.insert({ RawResourceType::CROPS, "Crops Resource Icon" });

			exploitationResources.insert({ RawResourceType::CROPS, Resource(RawResourceType::CROPS) });
			exploitationResources.insert({ RawResourceType::HERBS, Resource(RawResourceType::HERBS) });

			GenerateFieldBiome();
		}
		FieldBiome::FieldBiome(int _cropResources, int _herbResources, Structure _shipStructure)
			: FieldBiome()
		{
			exploitationResources[RawResourceType::CROPS].SetQuantity(_cropResources);
			exploitationResources[RawResourceType::HERBS].SetQuantity(_herbResources);

			structures.insert({ StructureType::ShipParts, _shipStructure });
		}

		void FieldBiome::GenerateFieldBiome()
		{
			GenerateResources(RawResourceType::CROPS, 40, 60);
			GenerateResources(RawResourceType::HERBS, 10, 20);

			//structures.insert({ StructureType::ShipParts, Structure::CreateShipStructure() });
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
		DesertBiome::DesertBiome(Structure _shipStructure)
			: DesertBiome()
		{
			structures.insert({ StructureType::ShipParts, _shipStructure });
		}

		void DesertBiome::GenerateDesertBiome()
		{
			//structures.insert({ StructureType::ShipParts, Structure::CreateShipStructure() });
		}
#pragma endregion

#pragma region Mountain
		MountainBiome::MountainBiome()
		{
			biomeType = BiomeType::Mountain;

			sprites = vector<string>({ "Tile Mountain 1", "Tile Mountain 2", "Tile Mountain 3" });

			allowBuild = true;
			terrain = HARD_TERRAIN;

			resourcesBuildingsCanExploit.insert({ BuildingType::OxygenExcavator, vector<__ResourceType>{ CoreResourceType::OXYGEN } });

			resourceIcons.insert({ CoreResourceType::OXYGEN, "Oxygen Resource Icon" });

			exploitationResources.insert({ CoreResourceType::OXYGEN, Resource(CoreResourceType::OXYGEN) });

			GenerateMountainBiome();
		}
		MountainBiome::MountainBiome(int _oxygenResources, Structure _shipStructure)
			: MountainBiome()
		{
			exploitationResources[CoreResourceType::OXYGEN].SetQuantity(_oxygenResources);

			structures.insert({ StructureType::ShipParts, _shipStructure });
		}

		void MountainBiome::GenerateMountainBiome()
		{
			GenerateResources(CoreResourceType::OXYGEN, 160, 280);

			//structures.insert({ StructureType::ShipParts, Structure::CreateShipStructure() });
		}
#pragma endregion

#pragma region Lake
		LakeBiome::LakeBiome()
		{
			biomeType = BiomeType::Lake;

			sprites = vector<string>({ "Tile Lake Center 1", "Tile Lake Center 2" });

			allowBuild = false;

			resourcesBuildingsCanExploit.insert({ BuildingType::WaterExtractor, vector<__ResourceType>{ RawResourceType::WATER } });

			resourceIcons.insert({ RawResourceType::WATER, "Water Resource Icon" });

			exploitationResources.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER) });

			GenerateLakeBiome();
		}
		LakeBiome::LakeBiome(int _waterResources)
			: LakeBiome()
		{
			exploitationResources[RawResourceType::WATER].SetQuantity(_waterResources);
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

			resourcesBuildingsCanExploit.insert({ BuildingType::OxygenGatherer, vector<__ResourceType>{ CoreResourceType::OXYGEN } });
			resourcesBuildingsCanExploit.insert({ BuildingType::HuntCamp, vector<__ResourceType>{ RawResourceType::MEAT, RawResourceType::HERBS } });

			resourceIcons.insert({ CoreResourceType::OXYGEN, "Oxygen Resource Icon" });
			resourceIcons.insert({ RawResourceType::MEAT, "Meat Resource Icon" });

			exploitationResources.insert({ CoreResourceType::OXYGEN, Resource(CoreResourceType::OXYGEN) });
			exploitationResources.insert({ RawResourceType::MEAT, Resource(RawResourceType::MEAT) });
			exploitationResources.insert({ RawResourceType::HERBS, Resource(RawResourceType::HERBS) });

			GenerateForestBiome();
		}
		ForestBiome::ForestBiome(int _oxygenResources, int _meatResources, int _herbResources, Structure _shipStructure)
			: ForestBiome()
		{
			exploitationResources[CoreResourceType::OXYGEN].SetQuantity(_oxygenResources);
			exploitationResources[RawResourceType::MEAT].SetQuantity(_meatResources);
			exploitationResources[RawResourceType::HERBS].SetQuantity(_herbResources);

			structures.insert({ StructureType::ShipParts, _shipStructure });
			structures.insert({ StructureType::Trees, Structure::CreateForestStructure() });
		}

		void ForestBiome::GenerateForestBiome()
		{
			GenerateForestResources();
			sprites = vector<string>(forestSprites[forestType]);
			GenerateResources(RawResourceType::HERBS, 15, 30);

			//structures.insert({ StructureType::ShipParts, Structure::CreateShipStructure() });
			structures.insert({ StructureType::Trees, Structure::CreateForestStructure() });
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

			exploitationResources[CoreResourceType::OXYGEN].SetQuantity(oxygenMat);
			exploitationResources[RawResourceType::MEAT].SetQuantity(animalMat);

			forestType = types[i];
		}
#pragma endregion

#pragma region Sea
		SeaBiome::SeaBiome()
		{
			biomeType = BiomeType::Sea;

			sprites = vector<string>({ "Tile Sea 1", "Tile Sea 2", "Tile Sea 3" });

			allowBuild = false;

			resourcesBuildingsCanExploit.insert({ BuildingType::WaterPurifier, vector<__ResourceType>{ RawResourceType::WATER } });

			resourceIcons.insert({ RawResourceType::WATER, "Water Resource Icon" });

			exploitationResources.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER) });

			GenerateSeaBiome();
		}
		SeaBiome::SeaBiome(int _waterResources)
			: SeaBiome()
		{
			exploitationResources[RawResourceType::WATER].SetQuantity(_waterResources);
		}

		void SeaBiome::GenerateSeaBiome()
		{
			GenerateResources(RawResourceType::WATER, 80, 120);
		}
#pragma endregion
	}
}

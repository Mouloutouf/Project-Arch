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
		}
		FieldBiome::FieldBiome(int _cropResources, int _herbResources, Structure* _shipStructure)
			: FieldBiome()
		{
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::CROPS, _cropResources) });
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::HERBS, _herbResources) });

			structures.push_back(_shipStructure);
		}
#pragma endregion

#pragma region Desert
		DesertBiome::DesertBiome()
		{
			biomeType = BiomeType::Desert;

			sprites = vector<string>({ "Tile Desert 1", "Tile Desert 2", "Tile Desert 3" });

			allowBuild = true;
			terrain = NORMAL_TERRAIN;
		}
		DesertBiome::DesertBiome(Structure* _shipStructure)
			: DesertBiome()
		{
			structures.push_back(_shipStructure);
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
		}
		MountainBiome::MountainBiome(int _oxygenResources, Structure* _shipStructure)
			: MountainBiome()
		{
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(CoreResourceType::OXYGEN, _oxygenResources) });

			structures.push_back(_shipStructure);
		}
#pragma endregion

#pragma region Lake
		LakeBiome::LakeBiome()
		{
			biomeType = BiomeType::Lake;

			sprites = vector<string>({ "" });

			allowBuild = false;

			buildingsForResourceExploitation.insert({ RawResourceType::WATER, BuildingType::WaterExtractor });
		}
		LakeBiome::LakeBiome(int _waterResources)
			: LakeBiome()
		{
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER, _waterResources) });
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
		}
		ForestBiome::ForestBiome(int _oxygenResources, int _meatResources, int _herbResources, Structure* _shipStructure)
			: ForestBiome()
		{
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(CoreResourceType::OXYGEN, _oxygenResources) });
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::MEAT, _meatResources) });
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::HERBS, _herbResources) });

			structures.push_back(_shipStructure);
			GenerateForestStructure();
		}
		void ForestBiome::GenerateForestStructure()
		{
			int minCstrMat = 5, maxCstrMat = 25;
			int cstrMat = Utility::GetRandomNumberInRange(minCstrMat, maxCstrMat);
			structures.push_back(new Structure(vector<Resource>{Resource(CoreResourceType::CONSTRUCTION, cstrMat)}));
		}
#pragma endregion

#pragma region Sea
		SeaBiome::SeaBiome()
		{
			biomeType = BiomeType::Sea;

			sprites = vector<string>({ "Tile Sea 1", "Tile Sea 2", "Tile Sea 3" });

			allowBuild = false;

			buildingsForResourceExploitation.insert({ RawResourceType::WATER, BuildingType::WaterPurifier });
		}
		SeaBiome::SeaBiome(int _waterResources)
			: SeaBiome()
		{
			resourcesProvisions.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER, _waterResources) });
		}
#pragma endregion
	}
}

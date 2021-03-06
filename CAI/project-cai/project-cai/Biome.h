#pragma once

#ifndef BIOME_H
#define BIOME_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Enums.h"
#include "Resource.h"
#include "Structure.h"

namespace alpha
{
	namespace game
	{
		struct Terrain
		{
			float constructionSpeed;
			float excavationSpeed;
			int buildCost;
		};

		const Terrain NORMAL_TERRAIN = Terrain{ 1, 1, 1 };
		const Terrain HARD_TERRAIN = Terrain{ 0.5f, 0.5f, 2 };

		class Biome
		{
		public:
			Biome();
			Biome(vector<Resource> _heldResources, vector<Structure> _structures);
			~Biome();

			int ExploitResource(__ResourceType _resourceType);
			void SetResource(__ResourceType _resourceType, unsigned int _amount);
			void DestroyResource(__ResourceType _resourceType);
			void DestroyResources();

			bool HasStructures();
			void AddStructure(Structure _structure);
			void RemoveStructure(StructureType _structureType);
			void RemoveAllStructures();

			void GenerateResources(__ResourceType _resourceType, int min, int max);

			BiomeType biomeType = BiomeType::None;

			vector<string> sprites;
			vector<string> spritesWithStructures;

			map<BuildingType, vector<__ResourceType>> resourcesBuildingsCanExploit;
			map<__ResourceType, string> resourceIcons;

			bool allowBuild = true;
			Terrain terrain = NORMAL_TERRAIN;

			map<__ResourceType, Resource> exploitationResources;

			map<StructureType, Structure> structures;
		};
	}
}

#endif // !BIOME_H

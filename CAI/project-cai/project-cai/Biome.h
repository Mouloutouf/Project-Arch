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
			Biome(vector<Resource> _heldResources, vector<Structure*> _structures);
			~Biome();

			int RetrieveResourceProvision(__ResourceType _resourceType);
			void SetResource(__ResourceType _resourceType, unsigned int _amount);
			void DestroyResource(__ResourceType _resourceType);
			void DestroyResources();

			bool hasStructures() { return structures.size() == 0; }
			void AddStructure(Structure* _structure);
			void RemoveStructure(Structure* _structure);
			void RemoveAllStructures();

			BiomeType biomeType = BiomeType::None;

		protected:
			vector<string> sprites;
			vector<string> spritesWithStructures;

			bool allowBuild = true;
			Terrain terrain = NORMAL_TERRAIN;

			map<__ResourceType, BuildingType> buildingsForResourceExploitation;

			map<__ResourceType, Resource> resourcesProvisions;

			vector<Structure*> structures;
		};
	}
}

#endif // !BIOME_H

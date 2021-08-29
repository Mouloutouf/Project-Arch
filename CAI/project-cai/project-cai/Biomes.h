#pragma once

#ifndef BIOMES_H
#define BIOMES_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Biome.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		class FieldBiome : public Biome
		{
		public:
			FieldBiome();
			FieldBiome(int _cropResources, int _herbResources, Structure* _shipStructure);
		};

		class DesertBiome : public Biome
		{
		public:
			DesertBiome();
			DesertBiome(Structure* _shipStructure);
		};

		class MountainBiome : public Biome
		{
		public:
			MountainBiome();
			MountainBiome(int _oxygenResources, Structure* _shipStructure);
		};

		class LakeBiome : public Biome
		{
		public:
			LakeBiome();
			LakeBiome(int _waterResources);
		};

		class ForestBiome : public Biome
		{
		public:
			ForestBiome();
			ForestBiome(int _oxygenResources, int _meatResources, int _herbResources, Structure* _shipStructure);

			void GenerateForestStructure();

		private:
			map<string, vector<string>> forestSprites;
		};

		class SeaBiome : public Biome
		{
		public:
			SeaBiome();
			SeaBiome(int _waterResources);
		};
	}
}

#endif // !BIOMES_H

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
			FieldBiome(int _cropResources, int _herbResources, Structure _shipStructure);

			void GenerateFieldBiome();
		};

		class DesertBiome : public Biome
		{
		public:
			DesertBiome();
			DesertBiome(Structure _shipStructure);

			void GenerateDesertBiome();
		};

		class MountainBiome : public Biome
		{
		public:
			MountainBiome();
			MountainBiome(int _oxygenResources, Structure _shipStructure);

			void GenerateMountainBiome();
		};

		class LakeBiome : public Biome
		{
		public:
			LakeBiome();
			LakeBiome(int _waterResources);

			void GenerateLakeBiome();
		};

		class ForestBiome : public Biome
		{
		public:
			ForestBiome();
			ForestBiome(int _oxygenResources, int _meatResources, int _herbResources, Structure _shipStructure);

			void GenerateForestBiome();
			void GenerateForestResources();

		private:
			string forestType;
			map<string, vector<string>> forestSprites;
		};

		class SeaBiome : public Biome
		{
		public:
			SeaBiome();
			SeaBiome(int _waterResources);

			void GenerateSeaBiome();
		};
	}
}

#endif // !BIOMES_H

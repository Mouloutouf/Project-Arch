#pragma once

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Resource.h"

namespace alpha
{
	using namespace core;

	namespace game
	{
		enum class StructureType { Trees, ShipParts, Building };

		class Structure
		{
		public:
			Structure();
			Structure(StructureType _structureType, vector<Resource> _heldResources);

			void ExtractResourcesFromStructure();
			void DestroyStructure();

			static Structure CreateShipStructure();
			static Structure CreateShipStructure(int _constructionResources, int _electronicsResources);

			static Structure CreateForestStructure();
			static Structure CreateForestStructure(int _constructionResources);

			StructureType structureType;

		protected:
			map<__ResourceType, Resource> heldResources;
		};
	}
}

#endif // !STRUCTURE_H

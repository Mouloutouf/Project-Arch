#pragma once

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Resource.h"

namespace alpha
{
	namespace game
	{
		class Structure
		{
		public:
			Structure();
			Structure(vector<Resource> _heldResources);

			void ExtractResourcesFromStructure();
			void DestroyStructure();

		private:
			map<__ResourceType, Resource> heldResources;
		};
	}
}

#endif // !STRUCTURE_H

#include "Structure.h"

namespace alpha
{
	namespace game
	{
		Structure::Structure()
		{
		}
		Structure::Structure(vector<Resource> _heldResources)
		{
			for (auto& r : _heldResources) {
				if (heldResources.count(r.getResourceType()) > 0) continue;
				heldResources.insert({ r.getResourceType(), r });
			}
		}
		void Structure::ExtractResourcesFromStructure()
		{
		}
		void Structure::DestroyStructure()
		{
		}
	}
}

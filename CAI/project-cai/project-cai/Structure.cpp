#include "Structure.h"

namespace alpha
{
	namespace game
	{
		Structure::Structure()
			: structureType(StructureType::ShipParts)
		{
		}
		Structure::Structure(StructureType _structureType, vector<Resource> _heldResources)
			: structureType(_structureType)
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

		Structure Structure::CreateShipStructure()
		{
			int minMat = 480, maxMat = 1640;
			int materials = Utility::GetRandomNumberInRange(minMat, maxMat);

			int minPercentage = 10, maxPercentage = 40;
			int percentage = Utility::GetRandomNumberInRange(minPercentage, maxPercentage);

			int electrMat = materials * (float)(percentage / 100.0f);
			int cstrMat = materials * (float)((100 - percentage) / 100.0f);

			return Structure::CreateShipStructure(cstrMat, electrMat);
		}
		Structure Structure::CreateShipStructure(int _constructionResources, int _electronicsResources)
		{
			return Structure(StructureType::ShipParts,
				vector<Resource>{Resource(CoreResourceType::CONSTRUCTION, _constructionResources), Resource(CoreResourceType::ELECTRONICS, _electronicsResources)});
		}

		Structure Structure::CreateForestStructure()
		{
			int minCstrMat = 5, maxCstrMat = 25;
			int cstrMat = Utility::GetRandomNumberInRange(minCstrMat, maxCstrMat);

			return Structure::CreateForestStructure(cstrMat);
		}
		Structure Structure::CreateForestStructure(int _constructionResources)
		{
			return Structure(StructureType::Trees,
				vector<Resource>{Resource(CoreResourceType::CONSTRUCTION, _constructionResources)});
		}
	}
}

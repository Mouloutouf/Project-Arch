#include "Biome.h"

namespace alpha
{
	namespace game
	{
		Biome::Biome()
		{
		}
		Biome::Biome(vector<Resource> _heldResources, vector<Structure*> _structures)
			: structures(_structures)
		{
			for (auto& r : _heldResources) {
				if (resourcesProvisions.count(r.getResourceType()) > 0) continue;
				resourcesProvisions.insert({ r.getResourceType(), r });
			}
		}
		Biome::Biome(const Biome& that)
		{
		}

		Biome::~Biome()
		{
			for (auto& s : structures)
				delete s;
		}

		void Biome::GenerateResources(__ResourceType _resourceType, int min, int max)
		{
			int qty = Utility::GetRandomNumberInRange(min, max);
			resourcesProvisions[_resourceType].SetQuantity(qty);
		}

		int Biome::RetrieveResourceProvision(__ResourceType _resourceType)
		{
			if (resourcesProvisions.count(_resourceType) == 0) return 0;
			return resourcesProvisions[_resourceType].GetQuantity();
		}
		void Biome::SetResource(__ResourceType _resourceType, unsigned int _amount)
		{
			if (resourcesProvisions.count(_resourceType) == 0) return;
			resourcesProvisions[_resourceType].SetQuantity(_amount);
		}
		void Biome::DestroyResource(__ResourceType _resourceType)
		{
			if (resourcesProvisions.count(_resourceType) == 0) return;
			resourcesProvisions.erase(_resourceType);
		}
		void Biome::DestroyResources()
		{
			for (auto& hr : resourcesProvisions) {
				resourcesProvisions.erase(hr.first);
			}
		}

		void Biome::AddStructure(Structure* _structure)
		{
			structures.push_back(_structure);
		}
		void Biome::RemoveStructure(Structure* _structure)
		{
			for (int i = 0; i < structures.size(); i++) {
				if (structures[i] == _structure)
					structures.erase(structures.begin() + i);
			}
		}
		void Biome::RemoveAllStructures()
		{
			structures.clear();
		}
	}
}

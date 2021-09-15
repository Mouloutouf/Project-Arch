#include "Biome.h"

namespace alpha
{
	namespace game
	{
		Biome::Biome()
		{
		}
		Biome::Biome(vector<Resource> _heldResources, vector<Structure> _structures)
		{
			for (auto& r : _heldResources) {
				if (exploitationResources.count(r.getResourceType()) > 0) continue;
				exploitationResources.insert({ r.getResourceType(), r });
			}
			for (auto& s : _structures) {
				if (structures.count(s.structureType) > 0) continue;
				structures.insert({ s.structureType, s });
			}
		}

		Biome::~Biome()
		{
		}

		void Biome::GenerateResources(__ResourceType _resourceType, int min, int max)
		{
			int qty = Utility::GetRandomNumberInRange(min, max);
			exploitationResources[_resourceType].SetQuantity(qty);
		}

		int Biome::ExploitResource(__ResourceType _resourceType)
		{
			if (exploitationResources.count(_resourceType) == 0) return 0;
			return exploitationResources[_resourceType].GetQuantity();
		}
		void Biome::SetResource(__ResourceType _resourceType, unsigned int _amount)
		{
			if (exploitationResources.count(_resourceType) == 0) return;
			exploitationResources[_resourceType].SetQuantity(_amount);
		}
		void Biome::DestroyResource(__ResourceType _resourceType)
		{
			if (exploitationResources.count(_resourceType) == 0) return;
			exploitationResources.erase(_resourceType);
		}
		void Biome::DestroyResources()
		{
			exploitationResources.clear();
		}

		bool Biome::HasStructures() { return structures.size() > 0; }

		void Biome::AddStructure(Structure _structure)
		{
			if (structures.count(_structure.structureType) > 0) return;
			structures.insert({ _structure.structureType, _structure });
		}
		void Biome::RemoveStructure(StructureType _structureType)
		{
			if (structures.count(_structureType) == 0) return;
			structures.erase(_structureType);
		}
		void Biome::RemoveAllStructures()
		{
			structures.clear();
		}
	}
}

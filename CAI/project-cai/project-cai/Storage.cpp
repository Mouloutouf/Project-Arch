#include "Storage.h"

namespace alpha
{
	namespace game
	{
		Storage::Storage()
		{
		}

		void Storage::SetResource(__ResourceType _resourceType, unsigned int _quantity)
		{
			if (resources.count(_resourceType) == 0) return;
			resources[_resourceType].SetQuantity(_quantity);
		}
		void Storage::AddToResource(__ResourceType _resourceType, unsigned int _amount)
		{
			if (resources.count(_resourceType) == 0) return;
			resources[_resourceType].AddQuantity(_amount);
		}
		void Storage::RemoveFromResource(__ResourceType _resourceType, unsigned int _amount)
		{
			if (resources.count(_resourceType) == 0) return;
			resources[_resourceType].RemoveQuantity(_amount);
		}

		void Storage::TransferResource(Storage* from, Storage* to, __ResourceType _resourceType, unsigned int _amount)
		{
			if (from->resources.count(_resourceType) == 0 || to->resources.count(_resourceType) == 0) return;
			from->RemoveFromResource(_resourceType, _amount);
			to->AddToResource(_resourceType, _amount);
		}

		GlobalStorage::GlobalStorage()
		{
			resources.insert({ CoreResourceType::CONSTRUCTION, Resource(CoreResourceType::CONSTRUCTION, 0) });
			resources.insert({ CoreResourceType::ELECTRONICS, Resource(CoreResourceType::ELECTRONICS, 0) });
			resources.insert({ CoreResourceType::OXYGEN, Resource(CoreResourceType::OXYGEN, 0) });
			resources.insert({ CoreResourceType::RATIONS, Resource(CoreResourceType::RATIONS, 0) });
		}

		LocalStorage::LocalStorage()
		{
			resources.insert({ RawResourceType::CROPS, Resource(RawResourceType::CROPS, 0) });
			resources.insert({ RawResourceType::MEAT, Resource(RawResourceType::MEAT, 0) });
			resources.insert({ RawResourceType::HERBS, Resource(RawResourceType::HERBS, 0) });
			resources.insert({ RawResourceType::WATER, Resource(RawResourceType::WATER, 0) });
		}
	}
}

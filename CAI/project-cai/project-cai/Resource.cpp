#include "Resource.h"

namespace alpha
{
	namespace game
	{
		Resource::Resource()
		{
		}
		Resource::Resource(__ResourceType _resourceType)
			: resourceType(_resourceType)
		{
		}
		Resource::Resource(__ResourceType _resourceType, unsigned int _quantity)
			: resourceType(_resourceType), quantity(_quantity)
		{
		}

		void Resource::SetQuantity(unsigned int _value) { quantity = _value; }

		int Resource::GetQuantity() { return quantity; }

		void Resource::AddQuantity(unsigned int _plus) { quantity += _plus; }
		void Resource::RemoveQuantity(unsigned int _minus) { quantity -= _minus; }
	}
}

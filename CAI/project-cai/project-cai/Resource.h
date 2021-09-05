#pragma once

#ifndef RESOURCE_H
#define RESOURCE_H

#include "Alpha.h"
#include "Core.h"

///\

namespace alpha
{
	namespace game
	{
#define __ResourceType int

		class ResourceType {
		public:
			static const __ResourceType NONE = 0;
		};
		class CoreResourceType : public ResourceType {
		public:
			static const __ResourceType OXYGEN = 1;
			static const __ResourceType RATIONS = 2;
			static const __ResourceType CONSTRUCTION = 3;
			static const __ResourceType ELECTRONICS = 4;
		};
		class RawResourceType : public ResourceType {
		public:
			static const __ResourceType CROPS = 11;
			static const __ResourceType MEAT = 12;
			static const __ResourceType HERBS = 13;
			static const __ResourceType WATER = 14;
		};

		enum class ResourceCategory { Core, Raw };

		class Resource
		{
		public:
			Resource();
			Resource(__ResourceType _resourceType);
			Resource(__ResourceType _resourceType, unsigned int _quantity);

			void SetQuantity(unsigned int _value);
			int GetQuantity();

			void AddQuantity(unsigned int _plus);
			void RemoveQuantity(unsigned int _minus);

			__ResourceType getResourceType() { return resourceType; }

		private:
			ResourceCategory category = ResourceCategory::Core; // NEEDS TO CHANGE
			__ResourceType resourceType = ResourceType::NONE;

			unsigned int quantity = 0;
		};
	}
}

#endif // !RESOURCE_H

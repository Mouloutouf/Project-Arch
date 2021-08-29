#pragma once

#ifndef STORAGE_H
#define STORAGE_H

#include "Alpha.h"
#include "Core.h"

///\

#include "Resource.h"

namespace alpha
{
	namespace game
	{
		class Storage
		{
		public:
			Storage();

			void SetResource(__ResourceType _resourceType, unsigned int _quantity);

			void AddToResource(__ResourceType _resourceType, unsigned int _amount);
			void RemoveFromResource(__ResourceType _resourceType, unsigned int _amount);

			static void TransferResource(Storage* from, Storage* to, __ResourceType _resourceType, unsigned int _amount);

		protected:
			map<__ResourceType, Resource> resources;
		};

		class GlobalStorage : public Storage
		{
		public:
			GlobalStorage();
		};

		class LocalStorage : public Storage
		{
		public:
			LocalStorage();
		};
	}
}

#endif // !STORAGE_H

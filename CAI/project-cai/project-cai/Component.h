#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "Alpha.h"

///\

namespace alpha
{
	namespace core
	{
		class GameObject;

		class Component
		{
		public:

			Component();
			Component(GameObject* _gameObject);
			Component(const Component& that);
			~Component();

			virtual Component* Clone();

			virtual void Init();

			virtual void Start();
			virtual void Update(float _elapsedTime);

			GameObject* gameObject;
		};
	}
}

#endif // !COMPONENT_H

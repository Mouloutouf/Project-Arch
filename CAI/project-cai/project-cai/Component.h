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
			Component(const Component& that, GameObject* _gameObject);
			~Component();

			virtual Component* Clone(GameObject* _gameObject);

			virtual void Init();

			virtual void Start();
			virtual void Update(float _elapsedTime);
			virtual void EventUpdate(Event& _event, float _elapsedTime);

			virtual void SetActive(bool _value);
			bool IsActive();

			GameObject* gameObject;

		protected:

			bool active = true;
		};
	}
}

#endif // !COMPONENT_H

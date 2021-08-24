#include "Component.h"

namespace alpha
{
	namespace core
	{
		Component::Component()
		{
		}
		Component::Component(GameObject* _gameObject)
			: gameObject(_gameObject)
		{
		}
		Component::Component(const Component& that, GameObject* _gameObject)
			: gameObject(_gameObject)
		{
		}

		Component::~Component()
		{
		}

		Component* Component::Clone(GameObject* _gameObject)
		{
			return new Component(*this, _gameObject);
		}

		void Component::Init()
		{
		}

		void Component::Start()
		{
		}

		void Component::Update(float _elapsedTime)
		{
		}
		void Component::EventUpdate(Event& _event, float _elapsedTime)
		{
		}
	}
}

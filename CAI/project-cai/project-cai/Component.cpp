#include "Component.h"

Component::Component()
{
}
Component::Component(GameObject* _gameObject)
	: gameObject(_gameObject)
{
}
Component::Component(const Component& that)
	: gameObject(that.gameObject)
{
}

Component::~Component()
{
}

Component* Component::Clone()
{
	return new Component(*this);
}

void Component::Update(float _elapsedTime)
{
}

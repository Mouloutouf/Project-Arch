#include "Component.h"

Component::Component()
{
}
Component::Component(GameObject* _gameObject)
: gameObject(_gameObject)
{
}

Component::~Component()
{
}

void Component::Update(float _elapsedTime)
{
}

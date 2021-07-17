#include "Component.h"

Component::Component()
{
}
Component::Component(GameObject* _gameObject, string _name = nullptr)
: gameObject(_gameObject), name(_name)
{
}

Component::~Component()
{
}

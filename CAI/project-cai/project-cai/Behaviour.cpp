#include "Behaviour.h"

Behaviour::Behaviour()
{
}

Behaviour::Behaviour(GameObject * parentGameObject)
{
	gameObject = parentGameObject;
}

Behaviour::~Behaviour()
{
}

void Behaviour::Start()
{
}

void Behaviour::Update(float elapsedTime)
{
}

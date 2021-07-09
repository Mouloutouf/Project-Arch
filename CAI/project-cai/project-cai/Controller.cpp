#include "Controller.h"

Controller::Controller(GameObject * parentGameObject, float speed) 
: Behaviour::Behaviour(parentGameObject)
{
	moveSpeed = speed;
}

Controller::~Controller()
{
	Behaviour::~Behaviour();
}

void Controller::Start()
{
	Behaviour::Start();
}

void Controller::Update(float elapsedTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		gameObject->position.y += -1 * moveSpeed * elapsedTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		gameObject->position.y += 1 * moveSpeed * elapsedTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		gameObject->position.x += -1 * moveSpeed * elapsedTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		gameObject->position.x += 1 * moveSpeed * elapsedTime;
	}
}

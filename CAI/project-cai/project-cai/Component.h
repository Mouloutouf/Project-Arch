#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject;

class Component
{
public:

	Component(); Component(GameObject* _gameObject);
	~Component();

	virtual void Update(float _elapsedTime);

	GameObject* gameObject;
};

#endif // !COMPONENT_H

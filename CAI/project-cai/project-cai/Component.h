#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameEngine.h"

class Component
{
public:

	Component(); Component(GameObject* _gameObject);
	~Component();

	virtual void Update(float _elapsedTime);
	virtual void Draw(RenderWindow* _window);

	GameObject* gameObject;
	//string name;
};

#endif // !COMPONENT_H

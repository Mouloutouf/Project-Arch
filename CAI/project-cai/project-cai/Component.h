#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"

class Component
{
public:

	Component();
	Component(GameObject* _gameObject, string _name = nullptr);
	~Component();

	GameObject* gameObject;
	string name;
};

#endif // !COMPONENT_H

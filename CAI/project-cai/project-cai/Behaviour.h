#pragma once

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"

class GameObject;

class Behaviour
{
public:

	Behaviour();
	Behaviour(GameObject * parentGameObject);
	~Behaviour();

	virtual void Start();

	virtual void Update(float elapsedTime);

protected:

	GameObject * gameObject;
};

#endif // !BEHAVIOUR_H

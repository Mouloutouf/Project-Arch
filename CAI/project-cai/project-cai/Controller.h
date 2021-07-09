#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Behaviour.h"

class GameObject;

class Controller : public Behaviour
{
public:

	Controller(GameObject * parentGameObject, float speed);
	~Controller();

	void Start() override;

	void Update(float elapsedTime) override;

protected:

	float moveSpeed;
};

#endif // !CONTROLLER_H

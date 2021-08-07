#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "GameObject.h"
#include "Component.h"

struct Display;

class Camera : public Component
{
public:

	Camera();
	Camera(GameObject* _gameObject, Display* _display, Vector2f _resolution, float _size);
	Camera(const Camera& that);
	~Camera();

	Camera* Clone() override;

	void Update(float _elapsedTime) override;

	void Input();

	float size;
	Display* display;

	int ppu() { return (int)(displayResolution.y / (size * 2)); }
private:

	Vector2f displayResolution;
};

#endif // !CAMERA_H

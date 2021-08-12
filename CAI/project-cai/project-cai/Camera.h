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

	void Input(float _elapsedTime, RenderWindow& _window);
	void E_Input(float _elapsedTime, Event& _event, RenderWindow& _window);

	void setSize(float _value); float getSize();
	Display* display;

	int ppu() { return (int)(displayResolution.y / (size * 2)); }

private:

	float speed = 0.4f;
	float scrollSpeed = 7;
	bool isDrag;
	Vector2f capturedMousePos;
	float moveSpeed = 0.4f;
	Vector2f Clamp(Vector2f _vec, float _radius) {
		float dist = Distance(Vector2f(0, 0), _vec);
		if (dist > _radius) {
			Vector2f newVec = (_vec * _radius) / dist;
			return newVec;
		}
		return _vec;
	}
	float Distance(Vector2f _v1, Vector2f _v2) {
		return sqrtf(powf(_v1.x - _v2.x, 2) + powf(_v1.y - _v2.y, 2));
	}

	float size;

	Vector2f displayResolution;
};

#endif // !CAMERA_H

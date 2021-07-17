#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Component.h"

using namespace std;
using namespace sf;

class SpriteRenderer;

struct Bounds
{
	Bounds();
	Bounds(Vector2f _size);
	~Bounds();

	Vector2f center;
	Vector2f size;

	Vector2f extents = size / Vector2f(2, 2);

	Vector2f min = Vector2f(center.x - extents.x, center.y - extents.y);
	Vector2f max = Vector2f(center.x + extents.x, center.y + extents.y);
};

class Collider : public Component
{
public:

	Collider();
	Collider(Vector2f _size);
	Collider(Bounds _bounds);
	~Collider();

	Bounds bounds;

protected:

	int& layer = gameObject->layer;
};
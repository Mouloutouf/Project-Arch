#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

struct Transform3D
{
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
};

struct Transform2D
{
	Vector2f position;
	float rotation;
	Vector2f scale;
};

class Element
{
public:

	Element();
	~Element();

	Transform2D* GetTransform();

	Element* GetParent();
	Element* GetFirstChild();
	vector<Element*> GetChildren();

private:

	string tag;
	Transform2D transform;

	Element* parent;
	vector<Element*> children;
};
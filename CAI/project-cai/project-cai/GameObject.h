#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

#include "Component.h"

struct Transform2D
{
	Transform2D();
	Transform2D(GameObject* _gameObject);
	~Transform2D();

	GameObject* gameObject;

	Vector2f position;
	float rotation;
	Vector2f scale;

	Vector2f localPosition;
	float localRotation;
	Vector2f localScale;

	Vector2f GetLocalPosition();
};

class GameObject
{
public:

	/// Constructors
	GameObject();
	GameObject(Transform2D _transform, GameObject* _parent = nullptr, string _name = "New Game Object", int _layer = 0, int _tags[] = {}, ...);
	virtual ~GameObject();

	/// Methods
	template <typename T> Component* GetComponent();
	template <typename T> Component* GetComponent(string _name);
	template <typename T> vector<Component*> GetComponents();

	vector<Component>* GetAllComponents();

	void AddComponent(Component _component);
	void RemoveComponent(Component* _component);

	GameObject* GetChild(int _index);
	GameObject* GetChild(string _name);

	/// Variables
	Transform2D transform;

	GameObject* parent;
	vector<GameObject*> children;

	string name;

	int layer;
	vector<int> tags;

protected:

	vector<Component> components;
};

#endif // !GAME_OBJECT_H

#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <typeinfo>

using namespace std;
using namespace sf;

#include "Component.h"

enum class Tag { Default, Main_Camera };

enum class Layer { Default };

struct Transform2D
{
	Transform2D();
	~Transform2D();

	GameObject* gameObject;

	Vector2f position();
	float rotation();
	Vector2f scale();

	Vector2f localPosition;
	float localRotation;
	Vector2f localScale = Vector2f(1, 1);
};

class GameObject
{
public:

	/// Constructors
	GameObject(Transform2D _transform = Transform2D(), GameObject* _parent = nullptr, string _name = "New Game Object", 
		Layer _layer = Layer::Default, vector<Tag> _tags = { Tag::Default }, 
		...);
	~GameObject();

	/// Methods
	template <typename T = Component> T* GetComponent()
	{
		for (auto c : components)
		{
			if (typeid(*c) == typeid(T))
			{
				return dynamic_cast<T*>(c);
			}
		}
		return nullptr;
	}
	template <typename T = Component> vector<T*> GetComponents()
	{
		vector<T*> _components;
		for (auto c : components)
		{
			if (typeid(*c) == typeid(T))
			{
				_components.push_back(dynamic_cast<T*>(c));
			}
		}
		return _components;
	}

	vector<Component*>* GetComponentsList();

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);

	GameObject* GetChild(int _index); GameObject* GetChild(string _name);

	void Update(float _elapsedTime);

	/// Variables
	Transform2D transform;

	GameObject* parent;
	vector<GameObject*> children;

	string name;

	Layer layer;
	vector<Tag> tags;

protected:

	vector<Component*> components;
};

#endif // !GAME_OBJECT_H
